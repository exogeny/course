#include <stdio.h>
#define LR_SIZE 6

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
