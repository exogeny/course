#ifndef __SHADOW_H__
#define __SHADOW_H__

#include <GL/glut.h>

/**
 * Create a matrix that will project the desired shadow.
 **/
void
shadowMatrix(
  GLfloat shadowMat[4][4],
  GLfloat groundplane[4],
  GLfloat lightpos[4]);

/**
 * Generate a cut-out shadow volume projection matrix from
 * the five points in world space.
 **/
void
constructShadowVolumeMatrix(
  GLfloat P[5][3],
  GLfloat M[4][4]);

/**
 * Compute a 4x4 matrix suitable for glMultMatrixd for
 * projecting into a plane.
 **/
void
computeShadowVolume(
  GLfloat L[3],     /* IN: light location */
  GLfloat O[3],     /* IN: cut-out plane */
  GLfloat M[3],     /* IN: cut-out X axis direction */
  GLfloat N[3],     /* IN: cut-out Z axis direction */
  GLfloat G[4],     /* IN: ground plane */
  GLfloat P[5][3]); /* OUT: five mutually non-coplanar points
                            defining the shadow volume projection */

/* Find the plane equation given 3 points. */
void
findPlane(
  float plane[4],
  float v0[3],
  float v1[3],
  float v2[3]);

void
initTeapot(
  GLint grid,
  GLfloat scale);

#endif