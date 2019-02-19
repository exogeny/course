#ifndef __VECTOR_H__
#define __VECTOR_H__

struct vector 
{
  float x;
  float y;
  float z;
  float w;
};

typedef struct vector vector_t;

void print_vector(vector_t * vec);
void normalize_vector(vector_t * vec);
void normalize_vector3(vector_t * vec);
void identity_vector(vector_t * vec);
float length_vector(vector_t const * vec);
void cross(vector_t * vec_a, vector_t * vec_b, vector_t * vec_r);
void vector_mul_vector(vector_t const * p, vector_t const * q, vector_t * r);

void axis_rad_to_quat(vector_t * vec, float const ax, float const ay, float const az, float const angle);

#endif