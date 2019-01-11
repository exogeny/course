#include <stdio.h>
#include <stdlib.h>
#define LR_SIZE 6

#define MAX(x, y) ((x) > (y) ? (x) : (y))

void swap(unsigned *l, unsigned *r)
{
    unsigned tmp = *l;
    *l = *r;
    *r = tmp;
}

unsigned long processure(unsigned *l, unsigned *r, int length)
{
    int i;
    unsigned long *sum = (unsigned long *)malloc(sizeof(unsigned long) * length * 2);
    sum[0] = sum[length] = 0;

    for (i = 0; i < length; i++)
    {
        if (l[i] > r[i]) swap(l + i, r + i);
    }

    for (i = 1; i < length; i++)
    {
        sum[i] = MAX(r[i - 1] * l[i] + sum[i - 1], l[i - 1] * l[i] + sum[i - 1 + length]);
        sum[i + length] = MAX(r[i - 1] * r[i] + sum[i - 1], l[i - 1] * r[i] + sum[i - 1 + length]);
    }

    i = length;
    unsigned long maxsum = MAX(sum[length - 1], sum[length * 2 - 1]);
    unsigned long temp = maxsum, cur;
    while (--i)
    {
        if (temp == sum[length + i]) swap(l + i, r + i);

        cur = l[i] * l[i - 1];
        if (temp - cur == sum[i - 1] ||
            temp - cur == sum[i - 1 + length])
            temp = temp - cur;
        else
            temp = temp - l[i] * r[i - 1];
    }

    free(sum);
    return maxsum;
}

int main(int argc, char const *argv[])
{
    unsigned R[LR_SIZE + 1] = {8, 2, 6, 7, 9, 10};
    unsigned L[LR_SIZE + 1] = {5, 4, 9, 7, 3, 11};
    unsigned W[LR_SIZE];

    unsigned long sum = processure(L, R, LR_SIZE);
    printf("The sum is %lu\n", sum);
    for (int i = 0; i < LR_SIZE; i++)
    {
        W[i] = (L[i] <= R[i] ? 0 : 1);
        printf("%u|%u[%u]\t", L[i], R[i], W[i]);
    }
    printf("\n");
    return 0;
}
