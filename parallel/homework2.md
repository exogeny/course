并行计算作业2
===

问题描述
---

运行提供的代码

基本环境配置
---

* **CPU**: Intel(R) Core(TM) i7-7700K CPU @ 4.20GHz
* **Memory**: 16GB DDR4 2.666 Ghz
* **OS**: CentOS Linux release 7.6.1810 (Core)
* **Compiler**: gcc version 4.8.5 20150623 (Red Hat 4.8.5-36) (GCC) 

运行结果
---

1. 计算Pi
    * **不使用OpenMP**： `pi with 100000000 steps is 3.141593 in 1.005606 seconds`
    * **使用OpenMP**：

      ``` text
        num_threads = 1
        pi is 3.141593 in 0.997004 seconds and 1 threads
        num_threads = 2
        pi is 3.141593 in 0.506157 seconds and 2 threads
        num_threads = 3
        pi is 3.141593 in 0.446211 seconds and 3 threads
        num_threads = 4
        pi is 3.141594 in 0.463299 seconds and 4 threads
      ```

1. Fibonacci
    * **不使用OpenMP**：

      ``` text
      Process linked list
        Each linked list node will be processed by function 'processwork()'
        Each ll node will compute 5 fibonacci numbers beginning with 38
      38 : 39088169
      39 : 63245986
      40 : 102334155
      41 : 165580141
      42 : 267914296
      43 : 433494437
      Compute Time: 6.469986 seconds
      ```

    * **使用OpenMP**：

      ``` text
      Process linked list
        Each linked list node will be processed by function 'processwork()'
        Each ll node will compute 5 fibonacci numbers beginning with 38
      Threads:      8
      38 : 39088169
      39 : 63245986
      40 : 102334155
      41 : 165580141
      42 : 267914296
      43 : 433494437
      Compute Time: 3.112225 seconds
      ```

1. Pi mc
    * **不使用OpenMP**：`1000000 trials, pi is 3.141456`
    * **使用OpenMP**：

      ``` text
       8 threads
       1000000 trials, pi is 3.142852  in 0.012415 seconds
      ```
