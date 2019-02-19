#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include "FreeImage.h"
#include "nvidia_logo.h"
#include "shadow.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int gWindowWidth = 800;
static int gWindowHeight = 640;

enum
{
  DL_NONE,
  DL_TEAPOT,
  DL_SPHERE,
  DL_CUT_OUT,
  DL_CUT_OUT_VOLUME,
};

enum { M_NO_SHADOWS, M_SHADOWS };

static GLfloat lightPosition[4];
static GLfloat lightDiffuse[] =  { 1.00f, 1.00f, 1.00f, 1.00f };
static GLfloat lightAmbient0[] = { 0.00f, 0.00f, 0.00f, 1.00f };
static GLfloat lightAmbient1[] = { 0.92f, 0.92f, 0.92f, 1.00f };

static GLfloat matrix[4][4];
static GLfloat projVolume[5][3];
static GLfloat cutoutOrigin[] = { 3.0f, 2.7f, 2.0f };
static GLfloat shadowMat[4][4];
static GLfloat cutoutX[3], cutoutY[3];
static GLfloat uGroundPlane[4], /* Plane below the true ground plane. */
               aGroundPlane[4]; /* Plane at the actual ground plane. */

/* Three vertices just below the ground plane. */
static GLfloat sbg[3] = { 0.0f, -1.5f, 0.0f };
static GLfloat tbg[3] = { 0.0f, -1.5f, 1.0f };
static GLfloat rbg[3] = { 1.0f, -1.5f, 0.0f };

/* Three vertices on the ground plane. */
static GLfloat sg[3] = { 0.0f, -1.0f, 0.0f };
static GLfloat tg[3] = { 0.0f, -1.0f, 1.0f };
static GLfloat rg[3] = { 1.0f, -1.0f, 0.0f };

GLint gViewport[4];

int displayMode = M_SHADOWS;

int logoAngle  = 240;
int lightAngle = 100, lightHeight = 5;
int moving = 0, beginx, beginy;
int lightMoving = 0, lightBeginx, lightBeginy;

static char *circle[] = {
  "....xxxx........",
  "..xxxxxxxx......",
  ".xxxxxxxxxx.....",
  ".xxx....xxx.....",
  "xxx......xxx....",
  "xxx......xxx....",
  "xxx......xxx....",
  "xxx......xxx....",
  ".xxx....xxx.....",
  ".xxxxxxxxxx.....",
  "..xxxxxxxx......",
  "....xxxx........",
  "................",
  "................",
  "................",
  "................",
};

static void makeFloorTexture(void)
{
  GLubyte floorTexture[16][16][3];
  GLubyte *loc;
  int s, t;

  /* Setup RGB image for the texture. */
  loc = (GLubyte*) floorTexture;
  for (t = 0; t < 16; t++)
  {
    for (s = 0; s < 16; s++)
    {
      if (circle[t][s] == 'x')
      {
        loc[0] = 0x1f;
        loc[1] = 0x8f;
        loc[2] = 0x1f;
      }
      else
      {
        loc[0] = 0xaa;
        loc[1] = 0xaa;
        loc[2] = 0xaa;
      }
      loc += 3;
    }
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
}

void updateAxis(void)
{
  cutoutX[0] = (GLfloat)(0.3 * cos(logoAngle/180.0 * M_PI));
  cutoutX[1] = 0.0f;
  cutoutX[2] = (GLfloat)(0.3 * -sin(logoAngle/180.0 * M_PI));

  cutoutY[0] = (GLfloat)(0.3 * sin(logoAngle/180.0 * M_PI));
  cutoutY[1] = 0.0f;
  cutoutY[2] = (GLfloat)(0.3 * cos(logoAngle/180.0 * M_PI));
}

int init(void)
{
  /* init the nvidia logo */
  initNVidiaLogo(DL_CUT_OUT, DL_CUT_OUT_VOLUME);

  /* init the teapot, don't use the glutSolidTeapot
     since it's not a true closed surface. */
  glNewList(DL_TEAPOT, GL_COMPILE);
    glDisable(GL_CULL_FACE);
    initTeapot(3, 1.6f);
    glEnable(GL_CULL_FACE);
  glEndList();

  glNewList(DL_SPHERE, GL_COMPILE);
    glutSolidSphere(0.5, 7, 7);
  glEndList();

  findPlane(uGroundPlane, sbg, tbg, rbg);
  findPlane(aGroundPlane, sg, tg, rg);
  makeFloorTexture();

  return 0;
}

void renderObject(void)
{
  glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glCallList(DL_SPHERE);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(2.0, -0.5, 2.0);
    glCallList(DL_SPHERE);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(2.0, -0.5, -2.0);
    glCallList(DL_SPHERE);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.0, 0.0, 2.0);
    glRotatef(230, 0.0, 1.0, 0.0);
    glCallList(DL_TEAPOT);
  glPopMatrix();
}

void renderFloor(void)
{
  float x, y;
  float d = 1.0;

  glEnable(GL_TEXTURE_2D);
  glColor3f(1.0, 1.0, 0.0);
  glNormal3f(0.0, 1.0, 0.0);

  for (x = -8; x <= 7; x += d)
  {
    glBegin(GL_QUAD_STRIP);
    for (y =- 8; y <= 8; y += d)
    {
      glTexCoord2f(x + 1, y);
      glVertex3f(x + 1, -1, y);
      glTexCoord2f(x, y);
      glVertex3f(x, -1, y);
    }
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}

void renderCutout(void)
{
  glNormal3f(0.0, 0.0, 1.0);
  glCallList(DL_CUT_OUT);

  glNormal3f(0.0, 0.0, -1.0);
  glCallList(DL_CUT_OUT);
}

void renderCutoutVolume(void)
{
  glCallList(DL_CUT_OUT_VOLUME);
}

void display(void)
{
  /* calculate the light position */
  lightPosition[0] = (GLfloat)(3.0f + 1.5 * sin(lightAngle / 180.0 * M_PI));
  lightPosition[1] = (GLfloat)lightHeight;
  lightPosition[2] = (GLfloat)(3.0f + 3.0 * cos(lightAngle / 180.0 * M_PI));
  lightPosition[3] = 1.0f;

  glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightDiffuse);

  glColorMask(1,1,1,1);
  glDepthMask(1);
  glStencilMask(~0u);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  glEnable(GL_LIGHT0);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient1);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  computeShadowVolume(lightPosition, cutoutOrigin, cutoutX, cutoutY, uGroundPlane, projVolume);
  constructShadowVolumeMatrix(projVolume, matrix);
  shadowMatrix(shadowMat, aGroundPlane, lightPosition);

  glDisable(GL_LIGHTING);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_POINTS);
    glVertex3fv(lightPosition);
  glEnd();
  glEnable(GL_LIGHTING);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  renderObject();

  glPushMatrix();
    glMultMatrixf((GLfloat*)matrix);
    renderCutout();
  glPopMatrix();

  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0x2, 0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  renderFloor();

  if (displayMode == M_SHADOWS)
  {
    glPushMatrix();
      glMultMatrixf((GLfloat*)matrix);
      glColorMask(0,0,0,0);
      glDepthMask(0);
      glEnable(GL_STENCIL_TEST);
      glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);
      glStencilFunc(GL_ALWAYS, 0, 0x1);
      glStencilMask(0x1);
      glDisable(GL_CULL_FACE);
      renderCutoutVolume();
      glEnable(GL_CULL_FACE); 
    glPopMatrix();

    glColorMask(1,1,1,1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    glStencilFunc(GL_EQUAL, 0x1, 0x1);
    glDepthFunc(GL_EQUAL);
    glDisable(GL_LIGHT0);
    renderObject();
    renderFloor();
    glEnable(GL_LIGHT0);

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
      glMultMatrixf((GLfloat *) shadowMat);
      glStencilFunc(GL_EQUAL, 0x3, 0x2);
      glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      renderObject();

      glPushMatrix();
        glMultMatrixf((GLfloat*)matrix);
        renderCutout();
      glPopMatrix();
    glPopMatrix();

    glStencilFunc(GL_EQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColorMask(1, 1, 1, 1);
    glDisable(GL_LIGHT0);
    renderFloor();
    glEnable(GL_DEPTH_TEST);
  }

  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

  glFlush();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  gWindowWidth  = w;
  gWindowHeight = h;

  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLdouble)w / h, 1.0, 20.0);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      moving = 1;
      beginx = x;
      beginy = y;
    }
    else
    {
      moving = 0;
    }
  }

  if (button == GLUT_RIGHT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      lightMoving = 1;
      lightBeginx = x;
      lightBeginy = y;
    }
    else
    {
      lightMoving = 0;
    }
  }
}

void motion(int x, int y)
{
  if (moving)
  {
    logoAngle = logoAngle + (beginx - x);
    logoAngle = logoAngle % 360;

    updateAxis();

    beginx = x;
    beginy = y;
    glutPostRedisplay();
  }

  if (lightMoving)
  {
    lightAngle = lightAngle +  (lightBeginx - x);
    lightAngle = lightAngle % 360;

    lightBeginx = x;
    lightBeginy = y;
    glutPostRedisplay();
  }
}

static void special(int k, int x, int y)
{
  glutPostRedisplay();
}

void menuHandler(int value)
{
  switch (value)
  {
    case M_NO_SHADOWS:
    case M_SHADOWS:
      displayMode = value;
      glutPostRedisplay();
      break;
  }
}

void initMenu(void)
{
  glutCreateMenu(menuHandler);

  glutAddMenuEntry("No shadow", M_NO_SHADOWS);
  glutAddMenuEntry("Show shadow", M_SHADOWS);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitWindowPosition(100, 100);
  glutInitWindowSize(gWindowWidth, gWindowHeight);
  glutInitDisplayString("samples=4 stencil>=3 rgb double depth");
  glutCreateWindow("Homework3");

  updateAxis();

  int ret = init();
  if (ret)
  {
    printf("Error: %d!", ret);
    return ret;
  }

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutSpecialFunc(special);

  initMenu();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 1.0, 30.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 5.0, 12.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0);

  glEnable(GL_DEPTH_TEST);
  glPointSize(4.0);

  glutMainLoop();
  return 0;
}