#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <math.h>
#include "vector.h"
#include "matrix.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct camera
{
  struct matrix view;
  struct matrix proj;
  struct matrix inv_view;
  struct matrix inv_proj;
  short para_proj;
};

typedef struct camera camera_t;

void initCamera(camera_t * camera);
void cameraLookAt(camera_t * camera, float const eyex, float const eyey, float const eyez,
                                     float const centerx, float const centery, float const centerz,
                                     float const upx, float const upy, float const upz);
void cameraPerspective(camera_t * camera, float const fonvy, float const aspect, float const znear, float const zfar);

#endif