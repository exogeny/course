# 习题3

## 描述
现有 n 块 “多米诺骨牌” $s_1, s_2, ... , s_n$ 水平放成一排，每块骨牌 si 包含左右两个部分，每个部分赋予一个非负整数值，如下图所示为包含 6 块骨牌的序列。骨牌可做 180度旋转，使得原来在左边的值变到右边，而原来在右边的值移到左边，假设不论 si 如何旋转，L\[i\] 总是存储 si 左边的值，R\[i\] 总是存储 si 右边的值，W\[i\] 用于存储 si 的状态：当 L\[i\] ≤ R\[i\] 时记为 0，否则记为 1，试采用分治法设计算法求$\sum_{i=1}^{n-1}R[i]L[i+1]$的最大值，以及当取得最大值时每个骨牌的状态。

## 实现原理
根据分治的思想，需要将多米诺骨牌分成两个部分。给出的例子的多米诺骨牌如下：
$$ (5 | 8) (4 | 2) (9 | 6) (7 | 7) (3 | 9) (11 | 10) $$
**分**
为了能够更好的计算$\sum_{i=1}^{n-1}R[i]L[i+1]$，我们在两侧加入0：
$$ 0) (5 | 8) (4 | 2) (9 | 6) (7 | 7) (3 | 9) (11 | 10) (0 $$
在对所给例子进行划分的时候，能够很方便的分成如下两个部分：
$$ 0) (5 | 8) (4 | 2) (9 | 6) (7 $$
$$ 7) (3 | 9) (11 | 10) (0 $$
按照这种方式持续的进行的划分，达到**分**的目的。
当我们划分到只含有一对数字的时候，例如$0) (5$或者 $8) (4$，直接的返回乘积。
**治**
下面讨论如何将两个部分合起来，我们能够很显然的看出，最终的结果是两个部分的和即可。但是需要注意的是：**骨牌能够进行旋转**。注意到在边界的骨牌只有两个状态，即当前的值和旋转后的状态。最终我们取两种情况的最大值即可。
**实现**
下面给出分治部分的代码：
``` c
unsigned long processure(unsigned * l, unsigned * r, int start, int end)
{
    unsigned tmp;
    unsigned long sum = 0, sum1, sum2;
    unsigned long mid = (start + end) / 2;

    if (start == end)
    {
        return r[start] * l[start];
    }

    if (l[mid] == r[mid + 1])
    {
        sum = processure(l, r, start, mid) + processure(l, r, mid + 1, end);
    }
    else
    {
        sum1 = processure(l, r, start, mid) + processure(l, r, mid + 1, end);
        tmp = l[mid]; l[mid] = r[mid + 1]; r[mid + 1] = tmp;
        sum2 = processure(l, r, start, mid) + processure(l, r, mid + 1, end);
        sum = sum1 > sum2 ? sum1 : sum2;

        if (sum == sum1)
        {
            tmp = l[mid]; l[mid] = r[mid + 1]; r[mid + 1] = tmp;
        }
    }
    return sum;
}
```
代码中，第6-10行判断当前是否只有一对数字，如果是的话，直接返回。第12-15行，当分界处的骨牌左右的数字相同的时候，旋转后的结果和当前的结果相同，因此无需分成两种情况。第16-27行则是左右数字不相同的情况。首先计算当前情况下分成两个部分和。然后对分解的骨牌进行旋转，再次求出当前情况下分成两个部分的和。最终对和进行比较，取得最大的值。由于该过程中对骨牌进行了旋转，假如旋转前的和是大的，那么需要再次进行旋转以将将状态调整回去。
**测试驱动代码**
下面给出测试的代码：
``` c
int main(int argc, char const *argv[])
{
    unsigned R[LR_SIZE + 1] = {0, 8, 2, 6, 7, 9, 10};
    unsigned L[LR_SIZE + 1] = {5, 4, 9, 7, 3, 11, 0};
    unsigned W[LR_SIZE];

    unsigned long sum = processure(L, R, 0, LR_SIZE);
    printf("The sum is %lu\n", sum);
    for (int i = 0; i < LR_SIZE; i++)
    {
        W[i] = (L[i] <= R[i + 1] ? 0 : 1);
        printf("%u|%u[%u]\t", L[i], R[i + 1], W[i]);
    }
    printf("\n");
    return 0;
}
```
*注意 在对数组进行赋值的时候，在两侧按照介绍的加入了0*
最终的输出结果为：
```
The sum is 227
5|8[0]  4|2[1]  6|9[0]  7|7[0]  3|9[0]  11|10[1]
```
