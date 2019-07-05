并行计算作业4
===

简单的使用GPU并行计算
---

将`add.c`修改成`add`的代码如下：

``` c
#include <stdio.h>
#include <stdlib.h>

// function to add the elements of two arrays
__global__ void add(int n, float *x, float *y)
{
  for (int i = 0; i < n; i++)
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

  // Run add on 1M elements on the CPU
  add<<<1, 1>>>(N, x, y);

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
```

使用命令编译：

``` bash
nvcc -o add_gpu add.cu
```

使用`nvprof ./add_gpu`运行编译的结果如下：

``` txt
==7757== NVPROF is profiling process 7757, command: ./add_gpu
Max error: 0.00
==7757== Profiling application: ./add_gpu
==7757== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:  100.00%  184.21ms         1  184.21ms  184.21ms  184.21ms  add(int, float*, float*)
      API calls:   57.62%  184.27ms         1  184.27ms  184.27ms  184.27ms  cudaDeviceSynchronize
                   42.14%  134.76ms         2  67.379ms  68.603us  134.69ms  cudaMallocManaged
                    0.10%  326.72us         2  163.36us  157.74us  168.98us  cudaFree
                    0.06%  181.03us         1  181.03us  181.03us  181.03us  cuDeviceTotalMem
                    0.05%  155.17us        94  1.6500us     170ns  63.769us  cuDeviceGetAttribute
                    0.02%  68.924us         1  68.924us  68.924us  68.924us  cudaLaunch
                    0.01%  23.204us         1  23.204us  23.204us  23.204us  cuDeviceGetName
                    0.00%  10.066us         3  3.3550us     450ns  8.4510us  cudaSetupArgument
                    0.00%  5.0830us         1  5.0830us  5.0830us  5.0830us  cudaConfigureCall
                    0.00%  4.7610us         3  1.5870us     243ns  3.8280us  cuDeviceGetCount
                    0.00%  1.1220us         2     561ns     265ns     857ns  cuDeviceGet

==7757== Unified Memory profiling result:
Device "GeForce GTX 1060 6GB (0)"
   Count  Avg Size  Min Size  Max Size  Total Size  Total Time  Name
      48  170.67KB  4.0000KB  0.9961MB  8.000000MB  703.6480us  Host To Device
      24  170.67KB  4.0000KB  0.9961MB  4.000000MB  331.5520us  Device To Host
      12         -         -         -           -  2.297760ms  Gpu page fault groups
Total CPU Page faults: 36
```

其中，`add`函数耗时`184.21ms`。

使用块内多线程加速
---

上面使用的函数仅仅使用了`1`个块，每个块内使用`1`个线程。为了能够加速，每个块内使用`256`个县城。

`add`的代码修改如下：

``` c
__global__ void add(int n, float *x, float *y)
{
  int index = threadIdx.x;
  int stride = blockDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}
```

调用的时候，指定每个块内的线程数：

``` c
add<<<1, 256>>>(N, x, y)
```

编译并使用`nvprof`运行结果如下：

``` txt
==8581== NVPROF is profiling process 8581, command: ./add_gpu
Max error: 0.00
==8581== Profiling application: ./add_gpu
==8581== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:  100.00%  3.0916ms         1  3.0916ms  3.0916ms  3.0916ms  add(int, float*, float*)
      API calls:   97.16%  139.08ms         2  69.539ms  46.722us  139.03ms  cudaMallocManaged
                    2.20%  3.1464ms         1  3.1464ms  3.1464ms  3.1464ms  cudaDeviceSynchronize
                    0.35%  507.19us         2  253.59us  246.12us  261.07us  cudaFree
                    0.13%  179.72us         1  179.72us  179.72us  179.72us  cuDeviceTotalMem
                    0.11%  161.34us        94  1.7160us     164ns  66.590us  cuDeviceGetAttribute
                    0.02%  33.915us         1  33.915us  33.915us  33.915us  cudaLaunch
                    0.02%  21.700us         1  21.700us  21.700us  21.700us  cuDeviceGetName
                    0.00%  5.1930us         3  1.7310us     113ns  4.4660us  cudaSetupArgument
                    0.00%  2.5520us         3     850ns     198ns  1.7410us  cuDeviceGetCount
                    0.00%  2.3410us         1  2.3410us  2.3410us  2.3410us  cudaConfigureCall
                    0.00%     999ns         2     499ns     239ns     760ns  cuDeviceGet

==8581== Unified Memory profiling result:
Device "GeForce GTX 1060 6GB (0)"
   Count  Avg Size  Min Size  Max Size  Total Size  Total Time  Name
      48  170.67KB  4.0000KB  0.9961MB  8.000000MB  967.8080us  Host To Device
      24  170.67KB  4.0000KB  0.9961MB  4.000000MB  336.6400us  Device To Host
      12         -         -         -           -  2.093664ms  Gpu page fault groups
Total CPU Page faults: 36

```

其中，`add`函数耗时`3.0916ms`，相对于之前的算法提升了60倍。

使用多个块再次加快计算性能
---

除了能够制定每个块内的线程数，还能够制定块的数量，修改`add`函数如下：

``` c
__global__ void add(int n, float *x, float *y)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = gridDim.x * blockDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}
```

调用的部分相应的修改：

``` c
  int block_size = 256;
  int num_blocks = (N + block_size - 1) / block_size;
  add<<<num_blocks, block_size>>>(N, x, y);
```

编译并使用`nvprof`调用结果如下：

``` txt
==8906== NVPROF is profiling process 8906, command: ./add_gpu
Max error: 0.00
==8906== Profiling application: ./add_gpu
==8906== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:  100.00%  1.8201ms         1  1.8201ms  1.8201ms  1.8201ms  add(int, float*, float*)
      API calls:   97.90%  134.56ms         2  67.281ms  34.276us  134.53ms  cudaMallocManaged
                    1.37%  1.8765ms         1  1.8765ms  1.8765ms  1.8765ms  cudaDeviceSynchronize
                    0.25%  342.75us         2  171.37us  163.48us  179.26us  cudaFree
                    0.23%  321.34us         1  321.34us  321.34us  321.34us  cuDeviceTotalMem
                    0.19%  267.80us        94  2.8480us     256ns  106.13us  cuDeviceGetAttribute
                    0.02%  32.978us         1  32.978us  32.978us  32.978us  cudaLaunch
                    0.02%  29.048us         1  29.048us  29.048us  29.048us  cuDeviceGetName
                    0.00%  5.2230us         3  1.7410us      95ns  4.6920us  cudaSetupArgument
                    0.00%  3.6910us         3  1.2300us     394ns  2.3920us  cuDeviceGetCount
                    0.00%  2.7660us         1  2.7660us  2.7660us  2.7660us  cudaConfigureCall
                    0.00%  1.8280us         2     914ns     393ns  1.4350us  cuDeviceGet

==8906== Unified Memory profiling result:
Device "GeForce GTX 1060 6GB (0)"
   Count  Avg Size  Min Size  Max Size  Total Size  Total Time  Name
      78  105.03KB  4.0000KB  996.00KB  8.000000MB  914.4640us  Host To Device
      24  170.67KB  4.0000KB  0.9961MB  4.000000MB  395.5840us  Device To Host
      12         -         -         -           -  1.771712ms  Gpu page fault groups
Total CPU Page faults: 36
```

其中，`add`函数耗时`1.8201ms`，相对于之前的算法提升了1.5倍左右。

练习
---

- 在`kernel`中使用`printf`打印块和线程信息：

  ``` c
  __global__ void add(int n, float *x, float *y)
  {
    printf("block: %d, thread: %d\n", blockIdx.x, threadIdx.x);
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = gridDim.x * blockDim.x;
    for (int i = index; i < n; i += stride)
      y[i] = x[i] + y[i];
  }
  ```

  得到的打印结果如下：

  ``` txt
  blockIdx: 18, threadIdx: 32
  blockIdx: 18, threadIdx: 33
  blockIdx: 18, threadIdx: 34
  blockIdx: 18, threadIdx: 35
  blockIdx: 18, threadIdx: 36
  blockIdx: 18, threadIdx: 37
  blockIdx: 18, threadIdx: 38
  blockIdx: 18, threadIdx: 39
  blockIdx: 18, threadIdx: 40
  blockIdx: 18, threadIdx: 41
  blockIdx: 18, threadIdx: 42
  blockIdx: 18, threadIdx: 43
  blockIdx: 18, threadIdx: 44
  blockIdx: 18, threadIdx: 45
  blockIdx: 18, threadIdx: 46
  blockIdx: 18, threadIdx: 47
  blockIdx: 18, threadIdx: 48
  blockIdx: 18, threadIdx: 49
  blockIdx: 18, threadIdx: 50
  blockIdx: 18, threadIdx: 51
  blockIdx: 18, threadIdx: 52
  blockIdx: 18, threadIdx: 53
  blockIdx: 18, threadIdx: 54
  blockIdx: 18, threadIdx: 55
  blockIdx: 18, threadIdx: 56
  blockIdx: 18, threadIdx: 57
  blockIdx: 18, threadIdx: 58
  blockIdx: 18, threadIdx: 59
  blockIdx: 18, threadIdx: 60
  blockIdx: 18, threadIdx: 61
  blockIdx: 18, threadIdx: 62
  blockIdx: 18, threadIdx: 63
  blockIdx: 10, threadIdx: 32
  blockIdx: 10, threadIdx: 33
  ...
  ```

- 打印每个块内线程的结果如下：

  ``` txt
  blockIdx: 10, threadIdx: 0
  blockIdx: 10, threadIdx: 1
  blockIdx: 10, threadIdx: 2
  blockIdx: 10, threadIdx: 3
  blockIdx: 10, threadIdx: 4
  blockIdx: 10, threadIdx: 5
  blockIdx: 10, threadIdx: 6
  blockIdx: 10, threadIdx: 7
  blockIdx: 10, threadIdx: 8
  blockIdx: 10, threadIdx: 9
  blockIdx: 10, threadIdx: 10
  blockIdx: 10, threadIdx: 11
  blockIdx: 10, threadIdx: 12
  blockIdx: 10, threadIdx: 13
  blockIdx: 10, threadIdx: 14
  blockIdx: 10, threadIdx: 15
  blockIdx: 10, threadIdx: 16
  blockIdx: 10, threadIdx: 17
  blockIdx: 10, threadIdx: 18
  blockIdx: 10, threadIdx: 19
  blockIdx: 10, threadIdx: 20
  blockIdx: 10, threadIdx: 21
  blockIdx: 10, threadIdx: 22
  blockIdx: 10, threadIdx: 23
  blockIdx: 10, threadIdx: 24
  blockIdx: 10, threadIdx: 25
  blockIdx: 10, threadIdx: 26
  blockIdx: 10, threadIdx: 27
  blockIdx: 10, threadIdx: 28
  blockIdx: 10, threadIdx: 29
  blockIdx: 10, threadIdx: 30
  blockIdx: 10, threadIdx: 31
  blockIdx: 10, threadIdx: 128
  blockIdx: 10, threadIdx: 129
  blockIdx: 10, threadIdx: 130
  blockIdx: 10, threadIdx: 131
  blockIdx: 10, threadIdx: 132
  blockIdx: 10, threadIdx: 133
  blockIdx: 10, threadIdx: 134
  blockIdx: 10, threadIdx: 135
  blockIdx: 10, threadIdx: 136
  blockIdx: 10, threadIdx: 137
  blockIdx: 10, threadIdx: 138
  blockIdx: 10, threadIdx: 139
  blockIdx: 10, threadIdx: 140
  blockIdx: 10, threadIdx: 141
  blockIdx: 10, threadIdx: 142
  blockIdx: 10, threadIdx: 143
  blockIdx: 10, threadIdx: 144
  blockIdx: 10, threadIdx: 145
  blockIdx: 10, threadIdx: 146
  blockIdx: 10, threadIdx: 147
  blockIdx: 10, threadIdx: 148
  blockIdx: 10, threadIdx: 149
  blockIdx: 10, threadIdx: 150
  blockIdx: 10, threadIdx: 151
  blockIdx: 10, threadIdx: 152
  blockIdx: 10, threadIdx: 153
  blockIdx: 10, threadIdx: 154
  blockIdx: 10, threadIdx: 155
  blockIdx: 10, threadIdx: 156
  blockIdx: 10, threadIdx: 157
  blockIdx: 10, threadIdx: 158
  blockIdx: 10, threadIdx: 159
  blockIdx: 10, threadIdx: 96
  blockIdx: 10, threadIdx: 97
  blockIdx: 10, threadIdx: 98
  blockIdx: 10, threadIdx: 99
  blockIdx: 10, threadIdx: 100
  blockIdx: 10, threadIdx: 101
  blockIdx: 10, threadIdx: 102
  blockIdx: 10, threadIdx: 103
  blockIdx: 10, threadIdx: 104
  blockIdx: 10, threadIdx: 105
  blockIdx: 10, threadIdx: 106
  blockIdx: 10, threadIdx: 107
  blockIdx: 10, threadIdx: 108
  blockIdx: 10, threadIdx: 109
  blockIdx: 10, threadIdx: 110
  blockIdx: 10, threadIdx: 111
  blockIdx: 10, threadIdx: 112
  blockIdx: 10, threadIdx: 113
  blockIdx: 10, threadIdx: 114
  blockIdx: 10, threadIdx: 115
  blockIdx: 10, threadIdx: 116
  blockIdx: 10, threadIdx: 117
  blockIdx: 10, threadIdx: 118
  blockIdx: 10, threadIdx: 119
  blockIdx: 10, threadIdx: 120
  blockIdx: 10, threadIdx: 121
  ...
  ```

- 总结：由于GPU具有多个核心，因此，块的运行顺序并不是固定的。对于每个块内，CUDA使用的基本执行但愿是线程束，线程束包含32个线程，因此在块内，每`32`个线程是连续的，由于并行计算的因素，每个线程束的执行顺序也不是固定的，因此线程的执行顺序也不是固定的。
