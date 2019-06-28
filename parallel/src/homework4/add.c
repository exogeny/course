#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function to add the elements of two arrays
void add(int n, float *x, float *y)
{
  for (int i = 0; i < n; i++)
    y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1 << 20; // 1M elements

  float *x = (float *)malloc(sizeof(float) * N);
  float *y = (float *)malloc(sizeof(float) * N);

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++)
  {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the CPU
  add(N, x, y);

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i] - 3.0f));
  printf("Max error: %.02f\n", maxError);

  // Free memory
  free(x);
  free(y);

  return 0;
}