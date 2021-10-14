最优化算法理论与应用作业
===

1. 将下面的线性规划问题化为标准型。
  $$
  \begin{aligned}
  \max \quad&{x_1 - x_2 + 2x_3} \\
  s.t. \quad&x_1 - 2x_2 + 3x_3 \geq 6 \\
            &2x_1 + x_2 − x_3 \leq 3 \\
            &0 \leq x_1 \leq 3 \\
            &−1 \leq x_2 \leq 6
  \end{aligned}
  $$
  **解**：令$x_2' = x_2 + 1$，上述线性规划问题化为：
  $$
  \begin{aligned}
  \max \quad&{x_1 - x_2' + 2x_3} \\
  s.t. \quad&x_1 - 2x_2' + 3x_3 \geq 4 \\
            &2x_1 + x_2' − x_3 \leq 4 \\
            &x_1 \leq 3 \\
            &x_2' \leq 7 \\
            &x_1 \geq 0, x_2' \geq 0
  \end{aligned}
  $$
  用$x_4 - x_5$代替$x_3$，并引入松弛变量和剩余变量得到以下公式：
  $$
  \begin{aligned}
  \max \quad&{x_1 - x_2' + 2x_4 - 2x_5 + 0x_6 + 0x_7 + 0x_8 + 0x_9 } \\
  s.t. \quad&x_1 - 2x_2' + 3x_4 - 3x_5 + x_6 = 4 \\
            &2x_1 + x_2' − x_4 + x_5 - x_7 = 4 \\
            &x_1 - x_8 = 3 \\
            &x_2' - x_9 = 7 \\
            &x_1 \geq 0, x_2' \geq 0, x_4 \geq 0, x_5 \geq 0, x_6 \geq 0, x_7 \geq 0, x_8 \geq 0, x_9 \geq 0
  \end{aligned}
  $$
  整理可得：
  $$
  \begin{aligned}
  \max \quad&{x_1 - x_2 + 2x_3 - 2x_4 } \\
  s.t. \quad&x_1 - 2x_2 + 3x_3 - 3x_4 + x_5 = 4 \\
            &2x_1 + x_2 − x_3 + x_4 - x_6 = 4 \\
            &x_1 - x_7 = 3 \\
            &x_2 - x_8 = 7 \\
            &x_j \geq 0, j = 1, 2, ..., 8
  \end{aligned}
  $$
  写作向量方式：
  $$
  \begin{aligned}
  \max \quad&{C^TX} \\
  s.t. \quad&AX = \overrightarrow{b} \\
            &X \geq 0 \\
  \end{aligned}
  $$
  $$
  C = \begin{pmatrix} 1 \\ -1 \\ 2 \\ -2 \\ 0 \\ 0 \\ 0 \\ 0 \end{pmatrix} \quad
  X = \begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \\ x_5 \\ x_6 \\ x_7 \\ x_8 \end{pmatrix} \quad
  A = \begin{pmatrix} 1 & -2 &  3 & -3 & 1 &  0 &  0 &  0 \\
                      2 &  1 & -1 &  1 & 0 & -1 &  0 &  0 \\
                      1 &  0 &  0 &  0 & 0 &  0 & -1 &  0 \\
                      0 &  1 &  0 &  0 & 0 &  0 &  0 & -1 \end{pmatrix} \quad
  \overrightarrow{b} = \begin{pmatrix} 4 \\ 4 \\ 3 \\ 7 \end{pmatrix}
  $$

2. 用图解法求解下述线性规划问题，并写出其可行域中的所有顶点。
  $$
  \begin{aligned}
  \max \quad&{x_1 + 2x_2} \\
  s.t. \quad&2x_1 + 5x_2 \geq 12 \\
            &x_1 + 2x_2 \leq 8 \\
            &0 \leq x_1 \leq 4 \\
            &0 \leq x_2 \leq 3
  \end{aligned}
  $$
  **解**：画出可行域如下图所示：
  ![可行域](/opt/assignment/p2.png)
  求得所有顶点为：$(0, 2.4), (0, 3), (2, 3), (4, 2), (4, 0.8)$

3. 假设以下集合均为非空集合，请判断哪些集合一定有顶点，需要给出理由。
a) $\Omega_1: \{ x\in\mathbb{R}^n|Ax = b, x \geq 0\}$。
b) $\Omega_2: \{ x\in\mathbb{R}^n|Ax \geq b\}$，其中$A$是行满秩矩阵。
c) $\Omega_3: \{ x\in\mathbb{R}^n|Ax \geq b\}$，其中$A$是列满秩矩阵。
  **解**：
  a) 不一定有顶点
  b) 不一定有顶点
  c) 一定有顶点

4. (1) 写出如下线性规划问题可行区域 D 中的所有顶点；
    $$
    \begin{aligned}
    \max \quad&{x_1 + 2x_2} \\
    s.t. \quad&2x_1 + 5x_2 \geq 12 \\
              &x_1 + 2x_2 \leq 8 \\
              &0 \leq x_1 \leq 4 \\
              &0 \leq x_2 \leq 3
    \end{aligned}
    $$

   (2) 证明：若一个线性规划问题在两个顶点上达到最优值，则此线性规划问题必有无穷多个最优解。

   **解**：
   （1）可行域D中所有的顶点如题2所求：$(0, 2.4), (0, 3), (2, 3), (4, 2), (4, 0.8)$。
   （2）当线性规划问题上在两个顶点上达到最优值时，那么梯度与这两个顶点的连线垂直。如果梯度与两个顶点的连线不垂直，那么从一个到另一个顶点将会存在梯度差，即这两个顶点得到的结果不同，与**在两个顶点上达到最优值**矛盾。因此，在沿着这两个顶点进行移动时，不存在梯度，因此得到的解也是最优解。

5. 某线性规划问题的约束条件是
    $$
    \left\{
      \begin{array}{lr}
        -2x_1 + 2x_2 + x_3 &= 4 \\
        3x_1 + x_2 + x_4 &= 6 \\
        x_j \geq 0, \quad j = 1, 2, 3, 4
      \end{array}
    \right.
    $$
   问变量$x_2, x_4$所对应的列向量$A_2, A_4$是否构成可行基？若是，写出$B, N$，并求出$B$所对应的基本可行解。

  **解**：变量$x_2, x_4$所对应的列向量$A_2 = \left( \begin{array}{lr} 2 \\ 1 \end{array} \right)$，$A_4 = \left( \begin{array}{lr} 0 \\ 1 \end{array} \right)$构成矩阵$B = \left( \begin{array}{lr} 2 & 0 \\ 1 & 1 \end{array} \right)$为可逆矩阵，$B^{-1} = \left( \begin{array}{lr} \frac{1}{2} & 0 \\ -\frac{1}{2} & 1 \end{array} \right)$，计算$B^{-1}\overrightarrow{b}$，可得
  $B^{-1} \left( \begin{array}{lr} 4 \\ 6 \end{array} \right) = \left( \begin{array}{lr} 2 \\ 4 \end{array} \right)$满足$B^{-1}\overrightarrow{b} \geq 0$，则**能够作为可行基**。
