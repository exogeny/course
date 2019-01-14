#include <cstdio>
#include <iostream>
#include "glinc.h"
#include "FreeImage.h"

#ifndef WIN32
#include <memory.h>
#endif

#define MENU_STEP_0 0x00
#define MENU_STEP_1 0x01
#define MENU_STEP_2 0x02
#define MENU_STEP_3 0x03
#define MENU_STEP_4 0x04
#define MENU_STEP_5 0x05

#define MENU_FILTER 0x11
#define MENU_LIGHT  0x12
#define MENU_ONOFF  0x13
#define MENU_SAVE   0x14
#define MENU_QUIT   0x15

int const MAX_STEPS    = 5;
int const MAX_TEXTURES = 3;

float const SPEED_STEP = 0.05f;
float const Z_STEP = 0.05f;

void * g_font = GLUT_BITMAP_8_BY_13;

GLuint g_display_id[MAX_STEPS + 1];
GLuint g_texture_id[MAX_TEXTURES];

float g_xrot = 30.0f;
float g_yrot = 30.0f;
float g_xspeed = 0.0f; // X Rotation Speed
float g_yspeed = 0.0f; // Y Rotation Speed
float g_z = -6.0f;     // Depth Into The Screen

int g_window_width = 512;
int g_window_height = 512;

float g_light_ambient[]   = { 0.0f, 0.0f , 0.0f, 1.0f };
float g_light_diffuse[]   = { 1.0f, 1.0f,  1.0f, 1.0f };
float g_light_position[]  = { 0.0f, 0.0f,  4.0f, 1.0f };
float g_light_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f };

float g_material_ambient[]  = {0.75f, 0.75f, 0.75f, 1.0f};
float g_material_diffuse[]  = { 1.0f, 0.57f, 0.04f, 1.0f};
float g_material_specular[] = { 0.0f,  0.0f,  0.0f, 0.0f};
float g_material_emission[] = { 0.0f,  0.0f,  0.0f, 0.0f};
float g_material_specular_power = 100.0f;

float g_color_background[] = {0.0f, 0.0f, 0.0f, 1.0f};
float g_color_foreground[] = {1.0f - g_color_background[0], 1.0f - g_color_background[1], 1.0f - g_color_background[2], 1.0f};

float g_cube_v[][3] = {
    {-1.0f, -1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f}};

unsigned int g_filter = 2; // Which Filter To Use
unsigned int g_step = 5;
bool g_light = true; // Lighting ON/OFF
bool g_lp = false;   // L Pressed?
bool g_fp = false;   // F Pressed?
bool g_fullscreen = false;

bool g_mouse_left  = false;
bool g_mouse_right = false;
float g_mouse_x = 0.0f;
float g_mouse_y = 0.0f;

int snapshotIndex = 0;

inline void setPixelTransfer(float scale, float bias)
{
    glPixelTransferf(GL_RED_SCALE, scale);
    glPixelTransferf(GL_GREEN_SCALE, scale);
    glPixelTransferf(GL_BLUE_SCALE, scale);
    glPixelTransferf(GL_RED_BIAS, bias);
    glPixelTransferf(GL_GREEN_BIAS, bias);
    glPixelTransferf(GL_BLUE_BIAS, bias);
}

bool saveFrameBuffer(char const *filename)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    FIBITMAP *dib = FreeImage_Allocate(viewport[2], viewport[3], 24);
    if (!dib)
        return false;

    bool status(false);
    BYTE *bits = FreeImage_GetBits(dib);
    if (bits)
    {
        glPixelStorei(GL_PACK_ALIGNMENT, 4); // Force 4-byte alignment
        setPixelTransfer(1.0f, 0.0f);
        glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_BGR, GL_UNSIGNED_BYTE, bits);

        if (FreeImage_Save(FIF_PNG, dib, filename))
            status = true;
    }

    FreeImage_Unload(dib);
    return status;
}

void setMaterial()
{
    GLenum face = GL_FRONT_AND_BACK;
    glMaterialfv(face, GL_AMBIENT, g_material_ambient);
    glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
    glMaterialfv(face, GL_SPECULAR, g_material_specular);
    glMaterialfv(face, GL_EMISSION, g_material_emission);
    glMaterialf(face, GL_SHININESS, g_material_specular_power);
}

FIBITMAP *loadImage(char const *filename, int flag = 0)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    if (fif == FIF_UNKNOWN)
        return false;

    return FreeImage_Load(fif, filename, flag);
}

bool loadTexture()
{
    FIBITMAP *tdib = loadImage("data/homework1/Crate.png");
    if (!tdib)
        return false;

    bool status(false);
    unsigned int bpp = FreeImage_GetBPP(tdib);

    FIBITMAP *dib = tdib;
    if (bpp != 24)
        dib = FreeImage_ConvertTo24Bits(tdib);

    BYTE *bits = FreeImage_GetBits(dib);
    unsigned int width = FreeImage_GetWidth(dib);
    unsigned int height = FreeImage_GetHeight(dib);

    GLenum format = FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR ? GL_BGR : GL_RGB;

    RGBQUAD *pal = FreeImage_GetPalette(dib);

    if (bits != 0 && width > 0 && height > 0)
    {
        status = true; // Set The Status To TRUE

        glGenTextures(3, g_texture_id); // Create Three Textures

        // Create Nearest Filtered Texture
        glBindTexture(GL_TEXTURE_2D, g_texture_id[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, bits);

        // Create Linear Filtered Texture
        glBindTexture(GL_TEXTURE_2D, g_texture_id[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, bits);

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, g_texture_id[2]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, bits);
    }

    if (bpp != 24)
        FreeImage_Unload(dib);

    FreeImage_Unload(tdib);

    return status; // Return The Status
}

void initVerticesList()
{
    glNewList(g_display_id[1], GL_COMPILE);
    glBegin(GL_POINTS);
        glVertex3fv(g_cube_v[0]);
        glVertex3fv(g_cube_v[1]);
        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[3]);
        glVertex3fv(g_cube_v[4]);
        glVertex3fv(g_cube_v[5]);
        glVertex3fv(g_cube_v[6]);
        glVertex3fv(g_cube_v[7]);
    glEnd();
    glEndList();
}

void initCommonPoint()
{
    glVertex3fv(g_cube_v[0]);
    glVertex3fv(g_cube_v[1]);

    glVertex3fv(g_cube_v[1]);
    glVertex3fv(g_cube_v[2]);

    glVertex3fv(g_cube_v[2]);
    glVertex3fv(g_cube_v[3]);

    glVertex3fv(g_cube_v[3]);
    glVertex3fv(g_cube_v[0]);

    glVertex3fv(g_cube_v[4]);
    glVertex3fv(g_cube_v[5]);

    glVertex3fv(g_cube_v[5]);
    glVertex3fv(g_cube_v[6]);

    glVertex3fv(g_cube_v[6]);
    glVertex3fv(g_cube_v[7]);

    glVertex3fv(g_cube_v[7]);
    glVertex3fv(g_cube_v[4]);

    glVertex3fv(g_cube_v[0]);
    glVertex3fv(g_cube_v[4]);

    glVertex3fv(g_cube_v[1]);
    glVertex3fv(g_cube_v[7]);

    glVertex3fv(g_cube_v[2]);
    glVertex3fv(g_cube_v[6]);

    glVertex3fv(g_cube_v[3]);
    glVertex3fv(g_cube_v[5]);
}

void initWireFrameList()
{
    glNewList(g_display_id[2], GL_COMPILE);
    glBegin(GL_LINES);
        initCommonPoint();
    glEnd();
    glEndList();
}

void initTrianglesList()
{
    glNewList(g_display_id[3], GL_COMPILE);
    glBegin(GL_LINES);
        initCommonPoint();

        glVertex3fv(g_cube_v[0]);
        glVertex3fv(g_cube_v[2]);

        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[7]);

        glVertex3fv(g_cube_v[7]);
        glVertex3fv(g_cube_v[5]);

        glVertex3fv(g_cube_v[5]);
        glVertex3fv(g_cube_v[0]);

        glVertex3fv(g_cube_v[0]);
        glVertex3fv(g_cube_v[7]);

        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[5]);
    glEnd();
    glEndList();
}

void initFaceList()
{
    glNewList(g_display_id[4], GL_COMPILE);
    glBegin(GL_QUADS);
        // Front Face
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3fv(g_cube_v[0]);
        glVertex3fv(g_cube_v[1]);
        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[3]);

        // Back Face
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3fv(g_cube_v[4]);
        glVertex3fv(g_cube_v[5]);
        glVertex3fv(g_cube_v[6]);
        glVertex3fv(g_cube_v[7]);

        // Top Face
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3fv(g_cube_v[5]);
        glVertex3fv(g_cube_v[3]);
        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[6]);

        // Bottom Face
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3fv(g_cube_v[4]);
        glVertex3fv(g_cube_v[7]);
        glVertex3fv(g_cube_v[1]);
        glVertex3fv(g_cube_v[0]);

        // Right face
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(g_cube_v[7]);
        glVertex3fv(g_cube_v[6]);
        glVertex3fv(g_cube_v[2]);
        glVertex3fv(g_cube_v[1]);

        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3fv(g_cube_v[4]);
        glVertex3fv(g_cube_v[0]);
        glVertex3fv(g_cube_v[3]);
        glVertex3fv(g_cube_v[5]);
    glEnd();
    glEndList();
}

void initFullList()
{
    glNewList(g_display_id[5], GL_COMPILE);
    glBegin(GL_QUADS);
        // Front Face
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[0]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[1]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[2]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[3]);
        // Back Face
        glNormal3f( 0.0f, 0.0f,-1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[4]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[5]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[6]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[7]);
        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[5]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[3]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[2]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[6]);
        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[4]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[7]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[1]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[0]);
        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[7]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[6]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[2]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[1]);
        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(g_cube_v[4]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(g_cube_v[0]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(g_cube_v[3]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(g_cube_v[5]);
    glEnd();
    glEndList();
}

void initLists()
{
    for (int i = 0; i <= MAX_STEPS; i++)
        g_display_id[i] = i;

    initVerticesList();
    initWireFrameList();
    initTrianglesList();
    initFaceList();
    initFullList();
}

bool init()
{
    if (!loadTexture())
        return false;

    glEnable(GL_TEXTURE_2D);                                    // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                                    // Enable Smooth Shading
    glClearColor(g_color_background[0], g_color_background[1], 
                 g_color_background[2], g_color_background[3]); // Black Background
    glClearDepth(1.0f);                                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                                    // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                     // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

    glLightfv(GL_LIGHT1, GL_DIFFUSE,  g_light_diffuse);      // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_SPECULAR, g_light_diffuse);

    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,  30.0f);

    glLightfv(GL_LIGHT1, GL_POSITION, g_light_position); // Position The Light
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);

    glEnable(GL_LIGHT1); // Enable Light One

    initLists();
    setMaterial();
    return true; // Initialization Went OK
}

void reshapeCallback(int width, int height)
{
    if (height == 0) // Prevent A Divide By Zero By
    {
        height = 1; // Making Height Equal One
    }

    glViewport(0, 0, width, height);                        // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                                   // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Reset The Modelview Matrix
}

void draw()
{
    glDisable(GL_TEXTURE_2D);
    if (g_step == 0)
    {
        glPointSize(3.5f);
        glColor4fv(g_color_foreground);
    }
    else if (g_step <= 2)
    {
        glColor4fv(g_color_foreground);
    }
    else if (g_step == 3)
    {
        setMaterial();
        g_material_diffuse[0] = 137.0f / 255.0f;
        g_material_diffuse[1] =  85.0f / 255.0f;
        g_material_diffuse[2] =  40.0f / 255.0f;
        glColor4fv(g_material_diffuse);
    }
    else
    {
        setMaterial();
        g_material_diffuse[0] = 1.0f;
        g_material_diffuse[1] = 1.0f;
        g_material_diffuse[2] = 1.0f;
        glColor4fv(g_material_diffuse);
        glBindTexture(GL_TEXTURE_2D, g_texture_id[g_filter]);
        glEnable(GL_TEXTURE_2D);
    }

    if (g_step > 0 && g_step <= 5)
        glCallList(g_display_id[g_step]);
}

void drawString(const char * str, int x, int y, float color[4], void * font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);  // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);   // need to disable texture

    glColor4fv(color);
    glRasterPos2i(x, y);

    while (*str)
    {
        glutBitmapCharacter(font, *str++);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glPopAttrib();
}

void showInfo()
{
    glPushMatrix();                 // save current model-view matrix
    glLoadIdentity();               // reset model-view matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);    // switch to projection matrix
    glPushMatrix();                 // save current projection matrix
    glLoadIdentity();               // reset projection matrix
    gluOrtho2D(0, 400, 0, 300);     // set to orthogonal projection

    static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    char buffer[40];

    sprintf(buffer, "Light: %s\0", (g_light ? "on" : "off"));
    drawString(buffer, 1, 286, color, g_font);

    sprintf(buffer, "Running: %s\0", ((g_xspeed == 0.0f && g_yspeed == 0.0f) ? "off" : "on"));
    drawString(buffer, 1, 272, color, g_font);

    sprintf(buffer, "Filter Mode: %u\0", g_filter);
    drawString(buffer, 1, 258, color, g_font);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}

void displayCallback()
{
    // Clear The Screen And The Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, g_z);

    glRotatef(g_xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(g_yrot, 0.0f, 1.0f, 0.0f);

    draw();
    showInfo();

    if (g_light && g_step >= 3)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    glPopMatrix();

    g_xrot += g_xspeed;
    g_yrot += g_yspeed;

    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'f':
        g_fp = true;
        g_filter = (g_filter + 1) % MAX_TEXTURES;
        break;

    case 'l':
        g_lp = true;
        g_light = !g_light;
        break;

    case 'r':
        g_xrot = 30.0f;
        g_yrot = 30.0f;
        g_xspeed = 1.0f;
        g_yspeed = 1.0f;
        break;

    case 's':
        g_xrot = 30.0f;
        g_yrot = 30.0f;
        g_xspeed = 0.0f;
        g_yspeed = 0.0f;
        g_light = false;
        break;

    case 'o':
        char filename[256];
        memset(filename, 0, 256);
        sprintf(filename, "snapshot_%d.png", snapshotIndex++);
        saveFrameBuffer(filename);
        break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        g_step = key - '0';
        break;

    default:
        break;
    }
}

void specialKeyCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        g_xspeed -= SPEED_STEP;
        break;

    case GLUT_KEY_DOWN:
        g_xspeed += SPEED_STEP;
        break;

    case GLUT_KEY_LEFT:
        g_yspeed -= SPEED_STEP;
        break;

    case GLUT_KEY_RIGHT:
        g_yspeed += SPEED_STEP;
        break;

    case GLUT_KEY_PAGE_UP:
        g_z -= Z_STEP;
        break;

    case GLUT_KEY_PAGE_DOWN:
        g_z += Z_STEP;
        break;

    case GLUT_KEY_F1:
        g_fullscreen = !g_fullscreen;
        if (g_fullscreen)
        {
            g_window_width = glutGet(GLUT_WINDOW_WIDTH);
            g_window_height = glutGet(GLUT_WINDOW_HEIGHT);
            glutFullScreen();
        }
        else
            glutReshapeWindow(g_window_width, g_window_height);
        break;
    }
}

void subMenuFunc(int mid)
{
    g_step = mid;
}

void mainMenuFunc(int mid)
{
    switch (mid)
    {
    case MENU_FILTER:
        g_fp = true;
        g_filter = (g_filter + 1) % MAX_TEXTURES;
        break;

    case MENU_LIGHT:
        g_lp = true;
        g_light = !g_light;
        break;

    case MENU_ONOFF:
        g_xrot = 30.0f;
        g_yrot = 30.0f;
        if (g_xspeed == 0.0f && g_yspeed == 0.0f)
        {
            g_xspeed = 1.0f;
            g_yspeed = 1.0f;
        }
        else
        {
            g_xspeed = 0.0f;
            g_yspeed = 0.0f;
        }
        break;

    case MENU_SAVE:
        char filename[256];
        memset(filename, 0, 256);
        sprintf(filename, "snapshot_%d.png", snapshotIndex++);
        saveFrameBuffer(filename);
        break;

    case MENU_QUIT:
        exit(0);

    default:
        break;
    }
}

void attachMenu()
{
    int subMenu = glutCreateMenu(subMenuFunc);
    glutAddMenuEntry("none", MENU_STEP_0);
    glutAddMenuEntry("1st step", MENU_STEP_1);
    glutAddMenuEntry("2nd step", MENU_STEP_2);
    glutAddMenuEntry("3th step", MENU_STEP_3);
    glutAddMenuEntry("4th step", MENU_STEP_4);
    glutAddMenuEntry("5th step", MENU_STEP_5);

    glutCreateMenu(mainMenuFunc);
    glutAddMenuEntry("Filter", MENU_FILTER);
    glutAddMenuEntry("Light", MENU_LIGHT);
    glutAddMenuEntry("Start/Pause", MENU_ONOFF);
    glutAddSubMenu("Steps", subMenu);
    glutAddMenuEntry("Save", MENU_SAVE);
    glutAddMenuEntry("Quit", MENU_QUIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseCallback(int button, int state, int x, int y)
{
    if (g_xspeed == 0.0f && g_yspeed == 0.0f)
    {
        g_mouse_x = x;
        g_mouse_y = y;

        if(button == GLUT_LEFT_BUTTON)
        {
            if(state == GLUT_DOWN)
            {
                g_mouse_left = true;
            }
            else if(state == GLUT_UP)
            {
                g_mouse_left = false;
            }
        }
    }
}

void mouseMotionCallback(int x, int y)
{
    if(g_mouse_left)
    {
        g_yrot += (x - g_mouse_x);
        g_xrot += (y - g_mouse_y);
        g_mouse_x = x;
        g_mouse_y = y;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(g_window_width, g_window_height);
    glutCreateWindow( "Texture 2D" );

    if (!init()) exit(-1);
    attachMenu();
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyCallback);
    glutIdleFunc(displayCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotionCallback);
    glutMainLoop();

    return 0;
}