## 解决方法
可以将数组看成是前后两个部分，前部分记作$X$，后部分记作$Y$。那么对于数组整体就可以写作$XY$。首先对前后两个部分进行翻转操作，记作$X^T$。那么经过翻转后，整个数组变成$X^TY^T$。然后再次对整体进行翻转则有
$$ (X^TY^T)^T = (Y^T)^T(X^T)^T = YX $$
即，将X和Y部分进行了交换。而循环右移实际上就可以看作是将前面的n-k个元素和后面的k个元素进行位置的交换。按照上面的原理，可以将前n-k个元素看作$X$，而后面的k个元素看作Y，那么只需要分别进行对$X、Y$进行翻转，然后再整体进行翻转即可。

## 具体实现
### 翻转操作
对于翻转操作，我们只需要一个临时变量进行存储数据交换时的数据。前后的交换可以由外向内进行，时间复杂度为$O(n / 2)$，C语言实现如下：
``` c
void reverse(void *array, int start, int end, size_t size)
{
    void *tmp = malloc(size);
    while (start < end)
    {
        // the array is the pointer of void, not the real type, so add the size.
        memcpy(tmp,                         (char*)array + start * size, size);
        memcpy((char*)array + start * size, (char*)array +   end * size, size);
        memcpy((char*)array +   end * size, tmp,                         size);
        start++; end--;
    }
    free(tmp);
}
```

### 主体操作
主体操作实际上就是3次翻转操作，前两次是分别对前n-k个元素以及后面n个元素进行翻转，时间复杂度$O((n - k)/ 2) + O(k / 2) = O(n)$。最后一次翻转是对整个数组进行翻转，时间复杂度为$O(n)$。最终整体时间复杂度为$O(n)$，而空间复杂度仅为1，是在翻转过程中进行数据交换而使用的临时变量。另外，假如循环右移的位数大于数组长度时，很容易的可以想到，当循环移动了n位时，数组各个元素的位置不会发生变化，那么最终循环的位数实际上是k对n取模。这里没有考虑为负数的情况。C语言实现代码如下：
``` c
void loop_right_shift(void *array, int n, int k, size_t size)
{
    if (k >= n) k = k % n;
    reverse(array, 0, n - k - 1, size);
    reverse(array, n - k, n - 1, size);
    reverse(array, 0, n - 1, size);
}
```

### 测试
下面给出了包含n = 31个元素，循环右移k位的一个例子：
``` c
int main(int argc, char const *argv[])
{
    int i, n = 31, k = 5;
    long long *array = (long long*)malloc(sizeof(long long) * n);
    for (i = 0; i < n; i++)
        *(array + i) = i;

    printf("origin: ");
    for (i = 0; i < n; i++)
        printf("%lld ", *(array + i));
    printf("\n");

    printf("shifted: ");
    loop_right_shift(array, n, k, sizeof(long long));
    for (i = 0; i < n; i++)
        printf("%lld ", *(array + i));
    printf("\n");

    free(array);
    return 0;
}
```
程序的输出结果为：
```
origin:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 
shifted: 26 27 28 29 30 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
```
可以看出程序得到了预期的运行结果。
