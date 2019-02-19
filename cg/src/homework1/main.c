#include <stdio.h>
#include "glinc.h"
#include "FreeImage.h"

#include "matrix.h"
#include "trackball.h"

#ifndef WIN32
#include <memory.h>
#endif

enum
{
  MENU_STEP_0,
  MENU_STEP_1,
  MENU_STEP_2,
  MENU_STEP_3,
  MENU_STEP_4,
  MENU_STEP_5,
  MENU_FILTER,
  MENU_LIGHT,
  MENU_ROTATE,
  MENU_SAVE,
  MENU_QUIT
};

#define MAX_STEPS 5
#define MAX_TEXTURES 3

#define SPEED_STEP 0.05f
#define Z_STEP 0.05f

void *g_font = GLUT_BITMAP_8_BY_13;

GLuint g_display_id[MAX_STEPS + 1];
GLuint g_texture_id[MAX_TEXTURES];

float g_xrot = 30.0f;
float g_yrot = 30.0f;
float g_xspeed = 0.0f; // X Rotation Speed
float g_yspeed = 0.0f; // Y Rotation Speed
float g_z = -6.0f;     // Depth Into The Screen

int g_window_width = 512;
int g_window_height = 512;

float g_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
float g_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
float g_light_position[] = {0.0f, 0.0f, 4.0f, 1.0f};
float g_light_direction[] = {0.0f, 0.0f, -1.0f, 1.0f};

float g_material_ambient[] = {0.75f, 0.75f, 0.75f, 1.0f};
float g_material_diffuse[] = {1.0f, 0.57f, 0.04f, 1.0f};
float g_material_specular[] = {0.0f, 0.0f, 0.0f, 0.0f};
float g_material_emission[] = {0.0f, 0.0f, 0.0f, 0.0f};
float g_material_specular_power = 100.0f;

float g_color_background[] = {0.0f, 0.0f, 0.0f, 1.0f};
float g_color_foreground[] = {1.0f, 1.0f, 1.0f, 1.0f};

float g_cube_v[][3] = {
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f}};

unsigned int g_filter = 2; // Which Filter To Use
unsigned int g_step = 5;
int g_light = TRUE; // Lighting ON/OFF
int g_lp = FALSE;    // L Pressed?
int g_fp = FALSE;    // F Pressed?
int g_fullscreen = FALSE;

trackball_t gTrack;
matrix_t gRom;
int g_mouse_left = FALSE;
int g_mouse_right = FALSE;
float g_mouse_x = 0.0f;
float g_mouse_y = 0.0f;

GLint gViewport[4];

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

int saveFrameBuffer(char const *filename)
{
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  FIBITMAP *dib = FreeImage_Allocate(viewport[2], viewport[3], 24, 0, 0, 0);
  if (!dib)
    return FALSE;

  int status = FALSE;
  BYTE *bits = FreeImage_GetBits(dib);
  if (bits)
  {
    glPixelStorei(GL_PACK_ALIGNMENT, 4); // Force 4-byte alignment
    setPixelTransfer(1.0f, 0.0f);
    glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_BGR, GL_UNSIGNED_BYTE, bits);

    if (FreeImage_Save(FIF_PNG, dib, filename, 0))
      status = TRUE;
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

FIBITMAP *loadImage(char const *filename, int flag)
{
  FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

  if (fif == FIF_UNKNOWN)
    fif = FreeImage_GetFIFFromFilename(filename);
  if (fif == FIF_UNKNOWN)
    return FALSE;

  return FreeImage_Load(fif, filename, flag);
}

int loadTexture()
{
  FIBITMAP *tdib = loadImage("data/homework1/Crate.png", 0);
  if (!tdib)
    return FALSE;

  int status = FALSE;
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
    status = TRUE; // Set The Status To TRUE

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
      glNormal3f(0.0f, 0.0f, 1.0f);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[0]);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[1]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[2]);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[3]);

      // Back Face
      glNormal3f(0.0f, 0.0f, -1.0f);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[4]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[5]);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[6]);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[7]);

      // Top Face
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[5]);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[3]);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[2]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[6]);

      // Bottom Face
      glNormal3f(0.0f, -1.0f, 0.0f);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[4]);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[7]);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[1]);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[0]);

      // Right face
      glNormal3f(1.0f, 0.0f, 0.0f);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[7]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[6]);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[2]);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[1]);

      // Left Face
      glNormal3f(-1.0f, 0.0f, 0.0f);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3fv(g_cube_v[4]);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3fv(g_cube_v[0]);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3fv(g_cube_v[3]);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3fv(g_cube_v[5]);
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

int init()
{
  if (!loadTexture())
    return FALSE;

  init_track(&gTrack);
  identity_matrix(&gRom);

  glEnable(GL_TEXTURE_2D); // Enable Texture Mapping
  glShadeModel(GL_SMOOTH); // Enable Smooth Shading
  glClearColor(g_color_background[0], g_color_background[1],
               g_color_background[2], g_color_background[3]); // Black Background
  glClearDepth(1.0f);                                          // Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);                                    // Enables Depth Testing
  glDepthFunc(GL_LEQUAL);                                      // The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light_diffuse); // Setup The Diffuse Light
  glLightfv(GL_LIGHT1, GL_SPECULAR, g_light_diffuse);

  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);

  glLightfv(GL_LIGHT1, GL_POSITION, g_light_position); // Position The Light
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);

  glEnable(GL_LIGHT1); // Enable Light One

  initLists();
  setMaterial();
  return TRUE; // Initialization Went OK
}

void reshape(int width, int height)
{
  if (height == 0) // Prevent A Divide By Zero By
  {
    height = 1; // Making Height Equal One
  }

  glViewport(0, 0, width, height); // Reset The Current Viewport
  glGetIntegerv(GL_VIEWPORT, gViewport);

  glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
  glLoadIdentity();             // Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window
  gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
  glLoadIdentity();            // Reset The Modelview Matrix
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
    g_material_diffuse[1] = 85.0f / 255.0f;
    g_material_diffuse[2] = 40.0f / 255.0f;
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

void drawString(const char *str, int x, int y, float color[4], void *font)
{
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);                          // need to disable lighting for proper text color
  glDisable(GL_TEXTURE_2D);                        // need to disable texture

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
  glPushMatrix();    // save current model-view matrix
  glLoadIdentity(); // reset model-view matrix

  // set to 2D orthogonal projection
  glMatrixMode(GL_PROJECTION); // switch to projection matrix
  glPushMatrix();               // save current projection matrix
  glLoadIdentity();             // reset projection matrix
  gluOrtho2D(0, 400, 0, 300);  // set to orthogonal projection

  static float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  char buffer[40];

  sprintf(buffer, "Light: %s\0", (g_light ? "on" : "off"));
  drawString(buffer, 1, 286, color, g_font);

  sprintf(buffer, "Running: %s\0", ((g_xspeed == 0.0f && g_yspeed == 0.0f) ? "off" : "on"));
  drawString(buffer, 1, 272, color, g_font);

  sprintf(buffer, "Filter Mode: %u\0", g_filter);
  drawString(buffer, 1, 258, color, g_font);

  // restore projection matrix
  glPopMatrix(); // restore to previous projection matrix

  // restore modelview matrix
  glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
  glPopMatrix();              // restore to previous modelview matrix
}

void display()
{
  // Clear The Screen And The Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, g_z);

  glMultMatrixf(gRom.elem);

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

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
    break;

  case 'f':
    g_fp = TRUE;
    g_filter = (g_filter + 1) % MAX_TEXTURES;
    break;

  case 'l':
    g_lp = TRUE;
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
    g_light = FALSE;
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

void special(int key, int x, int y)
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

void menuHandler(int mid)
{
  switch (mid)
  {
  case MENU_FILTER:
    g_fp = TRUE;
    g_filter = (g_filter + 1) % MAX_TEXTURES;
    break;

  case MENU_LIGHT:
    g_lp = TRUE;
    g_light = !g_light;
    break;

  case MENU_ROTATE:
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

  case MENU_STEP_0:
  case MENU_STEP_1:
  case MENU_STEP_2:
  case MENU_STEP_3:
  case MENU_STEP_4:
  case MENU_STEP_5:
      g_step = mid - MENU_STEP_0;
    break;

  default:
    break;
  }
}

void initMenu()
{
  int subMenu = glutCreateMenu(menuHandler);
  glutAddMenuEntry("none",     MENU_STEP_0);
  glutAddMenuEntry("1st step", MENU_STEP_1);
  glutAddMenuEntry("2nd step", MENU_STEP_2);
  glutAddMenuEntry("3th step", MENU_STEP_3);
  glutAddMenuEntry("4th step", MENU_STEP_4);
  glutAddMenuEntry("5th step", MENU_STEP_5);

  glutCreateMenu(menuHandler);
  glutAddMenuEntry("Filter", MENU_FILTER);
  glutAddMenuEntry("Light", MENU_LIGHT);
  glutAddMenuEntry("Start/Pause", MENU_ROTATE);
  glutAddSubMenu("Steps", subMenu);
  glutAddMenuEntry("Save", MENU_SAVE);
  glutAddMenuEntry("Quit", MENU_QUIT);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y)
{
  if (g_xspeed == 0.0f && g_yspeed == 0.0f)
  {
    if (button == GLUT_LEFT_BUTTON)
    {
      if (state == GLUT_DOWN)
      {
        start_track(&gTrack, (float)(2.0 * (x - gViewport[0]) / gViewport[2] - 1),
                             (float)(2.0 * (gViewport[3] - y - 1 - gViewport[1]) / gViewport[3] - 1));
        g_mouse_left = TRUE;
      }
      else if (state == GLUT_UP)
      {
        g_mouse_left = FALSE;
      }
    }

    g_mouse_x = x;
    g_mouse_y = y;
  }
}

void motion(int x, int y)
{
  if (g_mouse_left)
  {
    g_mouse_x = x;
    g_mouse_y = y;

    update_track(&gTrack, (float)(2.0 *(x - gViewport[0]) / gViewport[2] - 1),
                          (float)(2.0 *(gViewport[3] - y - 1 - gViewport[1]) / gViewport[3] - 1));
    build_rot_matrix(&gTrack, &gRom);
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(g_window_width, g_window_height);
  glutCreateWindow("Texture 2D");

  if (!init())
    exit(-1);
  initMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutIdleFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMainLoop();

  return 0;
}