#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "FreeImage.h"

int const MAX_TEXTURES = 3;

float const SPEED_STEP = 0.05f;
float const Z_STEP = 0.05f;

GLuint g_texture_id[MAX_TEXTURES];

float g_xrot = 30.0f;
float g_yrot = 30.0f;
float g_xspeed = 1.0f; // X Rotation Speed
float g_yspeed = 1.0f; // Y Rotation Speed
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
float g_color_foreground[] = {1.0f - g_color_background[0], 1.0f - g_color_background[1], 1.0f - g_color_background[2], 1.0f};

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
bool g_light = true; // Lighting ON/OFF ( NEW )
bool g_lp = false;   // L Pressed? ( NEW )
bool g_fp = false;   // F Pressed? ( NEW )
bool g_fullscreen = false;

inline void set_pixel_transfer(float scale, float bias)
{
  glPixelTransferf(GL_RED_SCALE, scale);
  glPixelTransferf(GL_GREEN_SCALE, scale);
  glPixelTransferf(GL_BLUE_SCALE, scale);
  glPixelTransferf(GL_RED_BIAS, bias);
  glPixelTransferf(GL_GREEN_BIAS, bias);
  glPixelTransferf(GL_BLUE_BIAS, bias);
}

bool save_framebuffer(char const *filename)
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
    set_pixel_transfer(1.0f, 0.0f);
    glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_BGR, GL_UNSIGNED_BYTE, bits);

    if (FreeImage_Save(FIF_PNG, dib, filename))
      status = true;
  }

  FreeImage_Unload(dib);

  return status;
}

void set_material()
{
  GLenum face = GL_FRONT_AND_BACK;
  glMaterialfv(face, GL_AMBIENT, g_material_ambient);
  glMaterialfv(face, GL_DIFFUSE, g_material_diffuse);
  glMaterialfv(face, GL_SPECULAR, g_material_specular);
  glMaterialfv(face, GL_EMISSION, g_material_emission);
  glMaterialf(face, GL_SHININESS, g_material_specular_power);
}

FIBITMAP *load_image(char const *filename, int flag = 0)
{
  FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);

  if (fif == FIF_UNKNOWN)
    fif = FreeImage_GetFIFFromFilename(filename);
  if (fif == FIF_UNKNOWN)
    return false;

  return FreeImage_Load(fif, filename, flag);
}

bool load_textures()
{
  FIBITMAP *tdib = load_image("Data/Crate.bmp");
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

bool init()
{
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    return false;
    printf("Error: %s\n", glewGetErrorString(err));
  }

  if (!load_textures())
  {
    return false;
  }

  glEnable(GL_TEXTURE_2D);                                                                                  // Enable Texture Mapping
  glShadeModel(GL_SMOOTH);                                                                                  // Enable Smooth Shading
  glClearColor(g_color_background[0], g_color_background[1], g_color_background[2], g_color_background[3]); // Black Background
  glClearDepth(1.0f);                                                                                       // Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);                                                                                  // Enables Depth Testing
  glDepthFunc(GL_LEQUAL);                                                                                   // The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);                                                        // Really Nice Perspective Calculations

  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

  //glLightfv(GL_LIGHT1, GL_AMBIENT, g_light_ambient);        // Setup The Ambient Light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light_diffuse); // Setup The Diffuse Light
  glLightfv(GL_LIGHT1, GL_SPECULAR, g_light_diffuse);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
  glLightfv(GL_LIGHT1, GL_POSITION, g_light_position); // Position The Light
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, g_light_direction);
  glEnable(GL_LIGHT1); // Enable Light One

  set_material();

  return true; // Initialization Went OK
}

void resize(int width, int height)
{
  if (height == 0) // Prevent A Divide By Zero By
  {
    height = 1; // Making Height Equal One
  }

  glViewport(0, 0, width, height); // Reset The Current Viewport

  glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
  glLoadIdentity();            // Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window
  gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
  //glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
  glLoadIdentity();           // Reset The Modelview Matrix
}

void draw_vertices()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glPointSize(3.5f);
  glColor4fv(g_color_foreground);
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
}

void draw_wire_frame()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glColor4fv(g_color_foreground);
  glBegin(GL_LINES);
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
  glEnd();
}

void draw_triangles()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glColor4fv(g_color_foreground);
  glBegin(GL_LINES);
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
}

void draw_faces()
{
  g_material_diffuse[0] = 137.0f / 255.0f;
  g_material_diffuse[1] = 85.0f / 255.0f;
  g_material_diffuse[2] = 40.0f / 255.0f;
  set_material();
  glColor4fv(g_material_diffuse);
  glDisable(GL_TEXTURE_2D); // Enable Texture Mapping
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
}

void draw_full()
{
  g_material_diffuse[0] = 1.0f;
  g_material_diffuse[1] = 1.0f;
  g_material_diffuse[2] = 1.0f;
  set_material();
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  glBindTexture(GL_TEXTURE_2D, g_texture_id[g_filter]);

  glEnable(GL_TEXTURE_2D);
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
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
  //glLoadIdentity();                                    // Reset The View
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, g_z);

  glRotatef(g_xrot, 1.0f, 0.0f, 0.0f);
  glRotatef(g_yrot, 0.0f, 1.0f, 0.0f);

  if (g_light)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  switch (g_step)
  {
  case 1:
    draw_vertices();
    break;

  case 2:
    draw_wire_frame();
    break;

  case 3:
    draw_triangles();
    break;

  case 4:
    draw_faces();
    break;

  case 5:
    draw_full();
    break;
  }

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
    save_framebuffer("snapshot.png");
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

void special_keys(int key, int x, int y)
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

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);                                     // Erm Just Write It =)
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Display Mode
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(g_window_width, g_window_height); // If glutFullScreen wasn't called this is the window size
  glutCreateWindow("CG Course: Lesson 1");             // Window Title (argv[0] for current directory as title)
  if (!init())
    exit(-1);
    
  const GLubyte *name	         = glGetString(GL_VENDOR);
  const GLubyte *render        = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *gluVersion    = gluGetString(GLU_VERSION); 
  printf("OpenGL Vendor:   %s\n", name);
  printf("Render:          %s\n", render);
  printf("OOpenGL Version: %s\n", version);
  printf("OGLU GLUVersion: %s\n", gluVersion);

  glutDisplayFunc(display); // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keys);
  glutIdleFunc(display);
  glutMainLoop(); // Initialize The Main Loop

  return 0;
}