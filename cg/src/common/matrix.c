#include <stdio.h>

#include "matrix.h"
#include "vector.h"

void print_matrix(matrix_t * matrix)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
      printf("%f ", matrix->elem[i * 4 + j]);
    printf("\n");
  }
}

void matrix_mul_matrix(matrix_t const * p, matrix_t const * q, matrix_t * r)
{
  matrix_t res;
  float * pelem = p->elem, * qelem = q->elem;

  res.elem[ 0] = pelem[0] * qelem[ 0] + pelem[4] * qelem[ 1] + pelem[ 8] * qelem[ 2] + pelem[12] * qelem[ 3];
  res.elem[ 1] = pelem[1] * qelem[ 0] + pelem[5] * qelem[ 1] + pelem[ 9] * qelem[ 2] + pelem[13] * qelem[ 3];
  res.elem[ 2] = pelem[2] * qelem[ 0] + pelem[6] * qelem[ 1] + pelem[10] * qelem[ 2] + pelem[14] * qelem[ 3];
  res.elem[ 3] = pelem[3] * qelem[ 0] + pelem[7] * qelem[ 1] + pelem[11] * qelem[ 2] + pelem[15] * qelem[ 3];
  res.elem[ 4] = pelem[0] * qelem[ 4] + pelem[4] * qelem[ 5] + pelem[ 8] * qelem[ 6] + pelem[12] * qelem[ 7];
  res.elem[ 5] = pelem[1] * qelem[ 4] + pelem[5] * qelem[ 5] + pelem[ 9] * qelem[ 6] + pelem[13] * qelem[ 7];
  res.elem[ 6] = pelem[2] * qelem[ 4] + pelem[6] * qelem[ 5] + pelem[10] * qelem[ 6] + pelem[14] * qelem[ 7];
  res.elem[ 7] = pelem[3] * qelem[ 4] + pelem[7] * qelem[ 5] + pelem[11] * qelem[ 6] + pelem[15] * qelem[ 7];
  res.elem[ 8] = pelem[0] * qelem[ 8] + pelem[4] * qelem[ 9] + pelem[ 8] * qelem[10] + pelem[12] * qelem[11];
  res.elem[ 9] = pelem[1] * qelem[ 8] + pelem[5] * qelem[ 9] + pelem[ 9] * qelem[10] + pelem[13] * qelem[11];
  res.elem[10] = pelem[2] * qelem[ 8] + pelem[6] * qelem[ 9] + pelem[10] * qelem[10] + pelem[14] * qelem[11];
  res.elem[11] = pelem[3] * qelem[ 8] + pelem[7] * qelem[ 9] + pelem[11] * qelem[10] + pelem[15] * qelem[11];
  res.elem[12] = pelem[0] * qelem[12] + pelem[4] * qelem[13] + pelem[ 8] * qelem[14] + pelem[12] * qelem[15];
  res.elem[13] = pelem[1] * qelem[12] + pelem[5] * qelem[13] + pelem[ 9] * qelem[14] + pelem[13] * qelem[15];
  res.elem[14] = pelem[2] * qelem[12] + pelem[6] * qelem[13] + pelem[10] * qelem[14] + pelem[14] * qelem[15];
  res.elem[15] = pelem[3] * qelem[12] + pelem[7] * qelem[13] + pelem[11] * qelem[14] + pelem[15] * qelem[15];

  for (int i = 0; i < 16; i++)
  {
    r->elem[i] = res.elem[i];
  }
}

void identity_matrix(matrix_t * matrix)
{
  matrix->elem[ 0] = matrix->elem[ 5] = 1.0f;
  matrix->elem[10] = matrix->elem[15] = 1.0f;

  matrix->elem[ 1] = matrix->elem[ 2] = 0.0f;
  matrix->elem[ 3] = matrix->elem[ 4] = 0.0f;
  matrix->elem[ 6] = matrix->elem[ 7] = 0.0f;
  matrix->elem[ 8] = matrix->elem[ 9] = 0.0f;
  matrix->elem[11] = matrix->elem[12] = 0.0f;
  matrix->elem[13] = matrix->elem[14] = 0.0f;
}

void matrix_from_vector(vector_t const * vec, matrix_t * mat)
{
  mat->elem[0] = 1.0f - 2.0f * (vec->y * vec->y + vec->z * vec->z);
  mat->elem[1] = 2.0f * (vec->x * vec->y + vec->z * vec->w);
  mat->elem[2] = 2.0f * (vec->z * vec->x - vec->y * vec->w);
  mat->elem[3] = 0.0f;

  mat->elem[4]  = 2.0f * (vec->x * vec->y - vec->z * vec->w);
  mat->elem[5]  = 1.0f - 2.0f * (vec->z * vec->z + vec->x * vec->x);
  mat->elem[6]  = 2.0f * (vec->y * vec->z + vec->x * vec->w);
  mat->elem[7]  = 0.0f;

  mat->elem[8]  = 2.0f * (vec->z * vec->x + vec->y * vec->w);
  mat->elem[9]  = 2.0f * (vec->y * vec->z - vec->x * vec->w);
  mat->elem[10] = 1.0f - 2.0f * (vec->x * vec->x + vec->y * vec->y);
  mat->elem[11] = 0.0f;

  mat->elem[12] = 0.0f;
  mat->elem[13] = 0.0f;
  mat->elem[14] = 0.0f;
  mat->elem[15] = 1.0f;
}

void translate(matrix_t * matrix, float const dx, float const dy, float const dz)
{
  matrix_t trans;

  identity_matrix(&trans);
  trans.elem[12] = dx;
  trans.elem[13] = dy;
  trans.elem[14] = dz;
  matrix_mul_matrix(matrix, &trans, matrix);
}