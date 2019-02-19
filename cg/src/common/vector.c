#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "matrix.h"
#define SQR(x) ((x) * (x))
#define EPSILON (0.001f)

void print_vector(vector_t * vec)
{
  printf("(%f, %f, %f, %f)\n", vec->x, vec->y, vec->z, vec->w);
}

void normalize_vector(vector_t * vec)
{
  float vecLenInv = sqrt(SQR(vec->x) + SQR(vec->y) + SQR(vec->z) + SQR(vec->w));
  vecLenInv = 1.0f / vecLenInv;

  vec->x = vec->x * vecLenInv;
  vec->y = vec->y * vecLenInv;
  vec->z = vec->z * vecLenInv;
  vec->w = vec->w * vecLenInv;
}

void normalize_vector3(vector_t * vec)
{
  float vecLenInv = sqrt(SQR(vec->x) + SQR(vec->y) + SQR(vec->z));
  vecLenInv = 1.0f / vecLenInv;

  vec->x = vec->x * vecLenInv;
  vec->y = vec->y * vecLenInv;
  vec->z = vec->z * vecLenInv;
}

void identity_vector(vector_t * vec)
{
  vec->x = 0.0f;
  vec->y = 0.0f;
  vec->z = 0.0f;
  vec->w = 1.0f;
}

float length_vector(vector_t const * vec)
{
  return sqrt(SQR(vec->x) + SQR(vec->y) + SQR(vec->z));
}

void cross(vector_t * vec_a, vector_t * vec_b, vector_t * vec_r)
{
  vec_r->x = vec_a->y * vec_b->z - vec_a->z * vec_b->y;
  vec_r->y = vec_a->z * vec_b->x - vec_a->x * vec_b->z;
  vec_r->z = vec_a->x * vec_b->y - vec_a->y * vec_b->x;
  vec_r->w = 0.0f;
}

void vector_mul_vector(vector_t const * p, vector_t const * q, vector_t * r)
{
  vector_t res;
  res.w = p->w * q->w - p->x * q->x - p->y * q->y - p->z * q->z;
  res.x = p->w * q->x + p->x * q->w + p->y * q->z - p->z * q->y;
  res.y = p->w * q->y + p->y * q->w + p->z * q->x - p->x * q->z;
  res.z = p->w * q->z + p->z * q->w + p->x * q->y - p->y * q->x;

  r->w = res.w;
  r->x = res.x;
  r->y = res.y;
  r->z = res.z;
}

void axis_rad_to_quat(vector_t * vec, float const ax, float const ay, float const az, float const angle)
{
  float xx, yy, zz;
  double rad, scale;
  double length = sqrt(SQR(ax) + SQR(ay) + SQR(az));

  if (length - 0.0f < EPSILON && 0.0f - length < EPSILON)
  {
    vec->w = 1.0f;
    vec->x = 0.0f;
    vec->y = 0.0f;
    vec->z = 0.0f;
    return;
  }

  if (length - 1.0f < EPSILON && 1.0f - length < EPSILON)
  {
    xx = ax;
    yy = ay;
    zz = az;
  }
  else
  {
    xx = ax / (float)length;
    yy = ay / (float)length;
    zz = az / (float)length;
  }

  rad = angle / 2;
  vec->w = (float)(cos(rad));
  scale = sin(rad);

  vec->x = (float)(xx * scale);
  vec->y = (float)(yy * scale);
  vec->z = (float)(zz * scale);

  normalize_vector(vec);
}