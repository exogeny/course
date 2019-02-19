#ifndef __TRACKBALL_H__
#define __TRACKBALL_H__

#include "vector.h"
#include "matrix.h"

struct trackball
{
  float ball_size;
  unsigned count;

  float last_x, last_y;

  vector_t curr_quat;
  vector_t last_quat;
};

typedef struct trackball trackball_t;

void init_track(trackball_t * track);
void start_track(trackball_t * track, float x, float y);
void update_track(trackball_t * track, float x, float y);
void build_rot_matrix(trackball_t const * track, matrix_t * mat);

#endif