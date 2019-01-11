#include <stdio.h>
#include <stdlib.h>

/**
 * H: 房子离街道起点处的距离
 * P: 用来存放邮局距离起点的距离
 * n: 房子的总数
 * 返回值: 返回邮局的总数，并将邮局距离起点的距离放到P中
 * P的大小至少位n

 **/
int buildPostOffice(int * H, int * P, int n)
{
    if (n == 0) return 0;

    int m = 1, i;
    P[0] = H[0] + 100;

    for (i = 1; i < n; i++)
    {
        if (H[i] - P[m - 1] > 100)
        {
            P[m] = H[i] + 100;
            m++;
        }
    }

    return m;
}

int main(int argc, char const *argv[])
{
    int m, n, i;

    printf("Please input the number of house: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("The number of house is invalid, exit...\n");
        return -1;
    }

    int * H = (int *)malloc(sizeof(int) * n);
    int * P = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n;)
    {
        printf("Enter the distance from start to %dth house: ", i + 1);
        scanf("%d", H + i);
        if ((i > 1 && H[i] < H[i - 1]) || H[i] < 0)
            printf("Invalid, Please Enter again:\n");
        else
            i++;
    }

    m = buildPostOffice(H, P, n);
    printf("\nWe need build %d post office, And the distances from start is\n", m);
    for (i = 0; i < m; i++)
    {
        printf("%d ", P[i]);
    }
    printf("\n");

    return 0;
}
