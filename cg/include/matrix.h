#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"

struct matrix
{
  float elem[16];
};

typedef struct matrix matrix_t;

void print_matrix(matrix_t * matrix);
void identity_matrix(matrix_t * matrix);
void translate(matrix_t * matrix, float const dx, float const dy, float const dz);
void matrix_mul_matrix(matrix_t const * p, matrix_t const * q, matrix_t * r);
void matrix_from_vector(vector_t const * vec, matrix_t * mat);

#endif