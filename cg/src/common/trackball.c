#include <stdio.h>
#include <math.h>

#include "trackball.h"
#include "vector.h"

unsigned int const RENORMCOUNT = 97;

float proj_sphere(float r, float x, float y)
{
  float d, z;

  d = x * x + y * y;
  if (d < r * r * 0.5f)
    z = sqrt(r * r - d);
  else
    z = 0.5f * r * r / sqrt(d);

  return z;
}

void init_track(trackball_t * track)
{
  track->last_x = 0.0f;
  track->last_y = 0.0f;

  track->ball_size = 0.6f;
  track->count = 0;
  identity_vector(&track->curr_quat);
  identity_vector(&track->last_quat);
}

void start_track(trackball_t * track, float x, float y)
{
  track->last_x = x;
  track->last_y = y;

  identity_vector(&track->last_quat);
}

void update_track(trackball_t * track, float x, float y)
{
  vector_t a = {0.0f, 0.0f, 0.0f, 1.0f};
  vector_t p1, p2, d;
  float phi, t;

  if (track->last_x == x && track->last_y == y)
  {
    identity_vector(&track->last_quat);
    return;
  }

  p1.x = track->last_x;
  p1.y = track->last_y;
  p1.z = proj_sphere(track->ball_size, track->last_x, track->last_y);
  p1.w = 1.0f;

  p2.x = x;
  p2.y = y;
  p2.z = proj_sphere(track->ball_size, x, y);
  p2.w = 1.0f;

  cross(&p1, &p2, &a);
  d.x = p1.x - p2.x;
  d.y = p1.y - p2.y;
  d.z = p1.z - p2.z;
  d.w = p1.w - p2.w;

  t = length_vector(&d) / (2.0f * track->ball_size);

  if (t > 1.0f) t = 1.0f;
  if (t < -1.0f) t = -1.0f;
  phi = 2.0f * asin(t);

  axis_rad_to_quat(&track->last_quat, a.x, a.y, a.z, phi);

  track->last_x = x;
  track->last_y = y;

  vector_mul_vector(&track->last_quat, &track->curr_quat, &track->curr_quat);
  if (++track->count > RENORMCOUNT)
  {
    track->count = 0;
    normalize_vector(&track->curr_quat);
  }
}

void build_rot_matrix(trackball_t const * track, matrix_t * mat)
{
  matrix_from_vector(&track->curr_quat, mat);
}