#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function to add the elements of two arrays
__global__ void add(int n, float *x, float *y)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = gridDim.x * blockDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1 << 20; // 1M elements

  // Allocate Unified Memory -- accessible from CPU or GPU
  float *x, *y;
  cudaMallocManaged(&x, N * sizeof(float));
  cudaMallocManaged(&y, N * sizeof(float));

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++)
  {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  int block_size = 256;
  int num_blocks = (N + block_size - 1) / block_size;
  // Run kernel on 1M elements on the CPU
  add<<<num_blocks, block_size>>>(N, x, y);

  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i] - 3.0f));
  printf("Max error: %.02f\n", maxError);

  cudaFree(x);
  cudaFree(y);

  return 0;
}