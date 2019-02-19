#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "camera.h"

void initCamera(camera_t * camera)
{
  identity_matrix(&camera->view);
  identity_matrix(&camera->inv_view);
  identity_matrix(&camera->proj);
  identity_matrix(&camera->inv_proj);
}

void cameraLookAt(camera_t * camera, float const eyex, float const eyey, float const eyez,
                                     float const centerx, float const centery, float const centerz,
                                     float const upx, float const upy, float const upz)
{
  vector_t minusz = {centerx - eyex, centery - eyey, centerz - eyez, 1.0f};
  vector_t x = {0.0f, 0.0f, 0.0f, 1.0f};
  vector_t y = {upx, upy, upz, 1.0f};

  normalize_vector3(&minusz);
  cross(&minusz, &y, &x);
  normalize_vector3(&x);
  cross(&x, &minusz, &y);

  identity_matrix(&camera->view);
  camera->view.elem[0] = x.x;
  camera->view.elem[1] = y.x;
  camera->view.elem[2] = -minusz.x;

  camera->view.elem[4] = x.y;
  camera->view.elem[5] = y.y;
  camera->view.elem[6] = -minusz.y;

  camera->view.elem[8] = x.z;
  camera->view.elem[9] = y.z;
  camera->view.elem[10] = -minusz.z;

  translate(&camera->view, -eyex, -eyey, -eyez);

  camera->inv_view.elem[ 0] = x.x;
  camera->inv_view.elem[ 1] = x.y;
  camera->inv_view.elem[ 2] = x.z;
  camera->inv_view.elem[ 3] = 0.0f;

  camera->inv_view.elem[ 4] = y.x;
  camera->inv_view.elem[ 5] = y.y;
  camera->inv_view.elem[ 6] = y.z;
  camera->inv_view.elem[ 7] = 0.0f;

  camera->inv_view.elem[ 8] = -minusz.x;
  camera->inv_view.elem[ 9] = -minusz.y;
  camera->inv_view.elem[10] = -minusz.z;
  camera->inv_view.elem[11] = 0.0f;

  camera->inv_view.elem[12] = eyex;
  camera->inv_view.elem[13] = eyey;
  camera->inv_view.elem[14] = eyez;
  camera->inv_view.elem[15] = 1.0f;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(camera->view.elem);
}

void cameraPerspective(camera_t * camera, float const fovy, float const aspect, float const znear, float const zfar)
{
  float tanangle = tan(fovy * 0.00872664625997f);
  float cotangle = 1.0f / tanangle;
  float fn = 1.0f / (zfar -  znear);

  camera->proj.elem[0] = cotangle / aspect;
  camera->proj.elem[1] = 0.0f;
  camera->proj.elem[2] = 0.0f;
  camera->proj.elem[3] = 0.0f;

  camera->proj.elem[4] = 0.0f;
  camera->proj.elem[5] = cotangle;
  camera->proj.elem[6] = 0.0f;
  camera->proj.elem[7] = 0.0f;

  camera->proj.elem[8] = 0.0f;
  camera->proj.elem[9] = 0.0f;
  camera->proj.elem[10] = -(zfar + znear) * fn;
  camera->proj.elem[11] = -1.0f;

  camera->proj.elem[12] = 0.0f;
  camera->proj.elem[13] = 0.0f;
  camera->proj.elem[14] = -2.0f * zfar * znear * fn;
  camera->proj.elem[15] = 0.0f;

  float inv2fn = 0.5f / (znear * zfar);
  camera->inv_proj.elem[0] = aspect * tanangle;
  camera->inv_proj.elem[1] = 0.0f;
  camera->inv_proj.elem[2] = 0.0f;
  camera->inv_proj.elem[3] = 0.0f;

  camera->inv_proj.elem[4] = 0.0f;
  camera->inv_proj.elem[5] = tanangle;
  camera->inv_proj.elem[6] = 0.0f;
  camera->inv_proj.elem[7] = 0.0f;

  camera->inv_proj.elem[8] = 0.0f;
  camera->inv_proj.elem[9] = 0.0f;
  camera->inv_proj.elem[10] = 0.0f;
  camera->inv_proj.elem[11] = (znear - zfar) * inv2fn;

  camera->inv_proj.elem[12] = 0.0f;
  camera->inv_proj.elem[13] = 0.0f;
  camera->inv_proj.elem[14] = -1.0f;
  camera->inv_proj.elem[15] = (znear + zfar) * inv2fn;

  camera->para_proj = FALSE;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(camera->proj.elem);
}