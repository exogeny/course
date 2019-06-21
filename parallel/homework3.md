并行计算作业3
===

1. mpi_hello.c

    ``` text
    Hello from task 0 on workstation!
    MASTER: Number of MPI tasks is: 2
    Hello from task 1 on workstation!
    ```

1. mpi_send_recv.c

    ``` text
    end_recv
    Task 0: Received 1 char(s) from task 1 with tag 1
    Task 1: Received 1 char(s) from task 0 with tag 1
    ```

1. mpi_helloBsend.c

    ``` text
    MASTER: Number of MPI tasks is: 2
    Hello from task 0 on workstation!
    Hello from task 1 on workstation!
    Task 0 is partner with 1
    Task 1 is partner with 0
    ```

1. mpi_helloNBsend.c

    ``` text
    Hello from task 1 on workstation!
    Hello from task 0 on workstation!
    MASTER: Number of MPI tasks is: 2
    Task 1 is partner with 0
    Task 0 is partner with 1
    ```

1. mpi_send_recv_nonblocking.c
    运行无输出结果

1. cpi.c

    ``` text
    Process 1 of 2 is on workstation
    Process 0 of 2 is on workstation
    pi is approximately 3.1415926544231318, Error is 0.0000000008333387
    wall clock time = 0.000184
    ```

1. mpi_scatter.c

    ``` text
    rank= 1  Results: 5.000000 6.000000 7.000000 8.000000
    rank= 0  Results: 1.000000 2.000000 3.000000 4.000000
    rank= 3  Results: 13.000000 14.000000 15.000000 16.000000
    rank= 2  Results: 9.000000 10.000000 11.000000 12.000000
    ```

1. mpi_reduce_pi.c

    ``` text
    MPI task 1 has started...
    MPI task 0 has started...
      After    50000 throws, average value of pi = 3.14344000
      After   100000 throws, average value of pi = 3.14376000
      After   150000 throws, average value of pi = 3.14330667
      After   200000 throws, average value of pi = 3.14384000
      After   250000 throws, average value of pi = 3.14427200
      After   300000 throws, average value of pi = 3.14362667
      After   350000 throws, average value of pi = 3.14387429
      After   400000 throws, average value of pi = 3.14231000
      After   450000 throws, average value of pi = 3.14185778
      After   500000 throws, average value of pi = 3.14134400
      After   550000 throws, average value of pi = 3.14254545
      After   600000 throws, average value of pi = 3.14369333
      After   650000 throws, average value of pi = 3.14371077
      After   700000 throws, average value of pi = 3.14372000
      After   750000 throws, average value of pi = 3.14355733
      After   800000 throws, average value of pi = 3.14323000
      After   850000 throws, average value of pi = 3.14400941
      After   900000 throws, average value of pi = 3.14388889
      After   950000 throws, average value of pi = 3.14332211
      After  1000000 throws, average value of pi = 3.14287200
      After  1050000 throws, average value of pi = 3.14297905
      After  1100000 throws, average value of pi = 3.14294545
      After  1150000 throws, average value of pi = 3.14271304
      After  1200000 throws, average value of pi = 3.14224333
      After  1250000 throws, average value of pi = 3.14160960
      After  1300000 throws, average value of pi = 3.14196923
      After  1350000 throws, average value of pi = 3.14232889
      After  1400000 throws, average value of pi = 3.14248000
      After  1450000 throws, average value of pi = 3.14225655
      After  1500000 throws, average value of pi = 3.14239733
      After  1550000 throws, average value of pi = 3.14208774
      After  1600000 throws, average value of pi = 3.14218250
      After  1650000 throws, average value of pi = 3.14214545
      After  1700000 throws, average value of pi = 3.14215529
      After  1750000 throws, average value of pi = 3.14229486
      After  1800000 throws, average value of pi = 3.14201556
      After  1850000 throws, average value of pi = 3.14215135
      After  1900000 throws, average value of pi = 3.14208211
      After  1950000 throws, average value of pi = 3.14229333
      After  2000000 throws, average value of pi = 3.14237200
      After  2050000 throws, average value of pi = 3.14233171
      After  2100000 throws, average value of pi = 3.14223238
      After  2150000 throws, average value of pi = 3.14191070
      After  2200000 throws, average value of pi = 3.14196182
      After  2250000 throws, average value of pi = 3.14194667
      After  2300000 throws, average value of pi = 3.14200000
      After  2350000 throws, average value of pi = 3.14179915
      After  2400000 throws, average value of pi = 3.14189000
      After  2450000 throws, average value of pi = 3.14181878
      After  2500000 throws, average value of pi = 3.14189760
      After  2550000 throws, average value of pi = 3.14207529
      After  2600000 throws, average value of pi = 3.14241846
      After  2650000 throws, average value of pi = 3.14243472
      After  2700000 throws, average value of pi = 3.14254222
      After  2750000 throws, average value of pi = 3.14253236
      After  2800000 throws, average value of pi = 3.14259571
      After  2850000 throws, average value of pi = 3.14255719
      After  2900000 throws, average value of pi = 3.14272690
      After  2950000 throws, average value of pi = 3.14281085
      After  3000000 throws, average value of pi = 3.14282267
      After  3050000 throws, average value of pi = 3.14288262
      After  3100000 throws, average value of pi = 3.14268774
      After  3150000 throws, average value of pi = 3.14255873
      After  3200000 throws, average value of pi = 3.14266875
      After  3250000 throws, average value of pi = 3.14261908
      After  3300000 throws, average value of pi = 3.14257697
      After  3350000 throws, average value of pi = 3.14269851
      After  3400000 throws, average value of pi = 3.14252118
      After  3450000 throws, average value of pi = 3.14263188
      After  3500000 throws, average value of pi = 3.14269600
      After  3550000 throws, average value of pi = 3.14251155
      After  3600000 throws, average value of pi = 3.14257333
      After  3650000 throws, average value of pi = 3.14256438
      After  3700000 throws, average value of pi = 3.14240108
      After  3750000 throws, average value of pi = 3.14219520
      After  3800000 throws, average value of pi = 3.14213368
      After  3850000 throws, average value of pi = 3.14194078
      After  3900000 throws, average value of pi = 3.14200000
      After  3950000 throws, average value of pi = 3.14202734
      After  4000000 throws, average value of pi = 3.14210600
      After  4050000 throws, average value of pi = 3.14216395
      After  4100000 throws, average value of pi = 3.14211024
      After  4150000 throws, average value of pi = 3.14211759
      After  4200000 throws, average value of pi = 3.14216000
      After  4250000 throws, average value of pi = 3.14224188
      After  4300000 throws, average value of pi = 3.14217302
      After  4350000 throws, average value of pi = 3.14215080
      After  4400000 throws, average value of pi = 3.14211727
      After  4450000 throws, average value of pi = 3.14221124
      After  4500000 throws, average value of pi = 3.14228889
      After  4550000 throws, average value of pi = 3.14230242
      After  4600000 throws, average value of pi = 3.14219913
      After  4650000 throws, average value of pi = 3.14231828
      After  4700000 throws, average value of pi = 3.14236255
      After  4750000 throws, average value of pi = 3.14231663
      After  4800000 throws, average value of pi = 3.14229500
      After  4850000 throws, average value of pi = 3.14230515
      After  4900000 throws, average value of pi = 3.14243918
      After  4950000 throws, average value of pi = 3.14246384
      After  5000000 throws, average value of pi = 3.14243120

    Real value of PI: 3.1415926535897
    ```

1. mpi_group_communicater.c

    ``` text
    rank= 0 newrank= 0 recvbuf= 6
    rank= 1 newrank= 1 recvbuf= 6
    rank= 2 newrank= 2 recvbuf= 6
    rank= 3 newrank= 3 recvbuf= 6
    rank= 4 newrank= 0 recvbuf= 22
    rank= 5 newrank= 1 recvbuf= 22
    rank= 6 newrank= 2 recvbuf= 22
    rank= 7 newrank= 3 recvbuf= 22
    ```

1. mpi_dedrived_datatype_continous.c

    ``` text
    rank= 0  b= 1.0 2.0 3.0 4.0
    rank= 1  b= 5.0 6.0 7.0 8.0
    rank= 2  b= 9.0 10.0 11.0 12.0
    rank= 3  b= 13.0 14.0 15.0 16.0
    ```

1. mpi_dedrived_datatype_index.c

    ``` text
    rank= 0  b= 6.0 7.0 8.0 9.0 13.0 14.0
    rank= 1  b= 6.0 7.0 8.0 9.0 13.0 14.0
    rank= 2  b= 6.0 7.0 8.0 9.0 13.0 14.0
    rank= 3  b= 6.0 7.0 8.0 9.0 13.0 14.0
    ```

1. mpi_dedrived_datatype_struct.c

    ``` text
    rank= 0   0.00 -0.00 0.00 0.25 0 0
    rank= 1   1.00 -1.00 1.00 0.25 1 1
    rank= 2   2.00 -2.00 2.00 0.25 2 0
    rank= 3   3.00 -3.00 3.00 0.25 3 1
    ```

1. mpi_dedrived_datatype_vector.c

    ``` text
    rank= 0  b= 1.0 5.0 9.0 13.0
    rank= 1  b= 2.0 6.0 10.0 14.0
    rank= 2  b= 3.0 7.0 11.0 15.0
    rank= 3  b= 4.0 8.0 12.0 16.0
    ```

1. mpi_topology_graph.c

    ``` text
    rank= 0 coords= 0 0  neighbors(u,d,l,r)= -1 4 -1 1
    rank= 2 coords= 0 2  neighbors(u,d,l,r)= -1 6 1 3
    rank= 8 coords= 2 0  neighbors(u,d,l,r)= 4 12 -1 9
    rank= 10 coords= 2 2  neighbors(u,d,l,r)= 6 14 9 11
    rank= 12 coords= 3 0  neighbors(u,d,l,r)= 8 -1 -1 13
    rank= 14 coords= 3 2  neighbors(u,d,l,r)= 10 -1 13 15
    rank= 3 coords= 0 3  neighbors(u,d,l,r)= -1 7 2 -1
    rank= 4 coords= 1 0  neighbors(u,d,l,r)= 0 8 -1 5
    rank= 1 coords= 0 1  neighbors(u,d,l,r)= -1 5 0 2
    rank= 5 coords= 1 1  neighbors(u,d,l,r)= 1 9 4 6
    rank= 4                  inbuf(u,d,l,r)= 0 8 -1 5
    rank= 0                  inbuf(u,d,l,r)= -1 4 -1 1
    rank= 1                  inbuf(u,d,l,r)= -1 5 0 2
    rank= 11 coords= 2 3  neighbors(u,d,l,r)= 7 15 10 -1
    rank= 6 coords= 1 2  neighbors(u,d,l,r)= 2 10 5 7
    rank= 6                  inbuf(u,d,l,r)= 2 10 5 7
    rank= 7 coords= 1 3  neighbors(u,d,l,r)= 3 11 6 -1
    rank= 7                  inbuf(u,d,l,r)= 3 11 6 -1
    rank= 15 coords= 3 3  neighbors(u,d,l,r)= 11 -1 14 -1
    rank= 15                  inbuf(u,d,l,r)= 11 -1 14 -1
    rank= 8                  inbuf(u,d,l,r)= 4 12 -1 9
    rank= 9 coords= 2 1  neighbors(u,d,l,r)= 5 13 8 10
    rank= 2                  inbuf(u,d,l,r)= -1 6 1 3
    rank= 5                  inbuf(u,d,l,r)= 1 9 4 6
    rank= 11                  inbuf(u,d,l,r)= 7 15 10 -1
    rank= 3                  inbuf(u,d,l,r)= -1 7 2 -1
    rank= 13 coords= 3 1  neighbors(u,d,l,r)= 9 -1 12 14
    rank= 12                  inbuf(u,d,l,r)= 8 -1 -1 13
    rank= 13                  inbuf(u,d,l,r)= 9 -1 12 14
    rank= 10                  inbuf(u,d,l,r)= 6 14 9 11
    rank= 9                  inbuf(u,d,l,r)= 5 13 8 10
    rank= 14                  inbuf(u,d,l,r)= 10 -1 13 15
    ```
