#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void loop_right_shift(void *array, int n, int k, size_t size)
{
    if (k >= n) k = k % n;
    reverse(array, 0, n - k - 1, size);
    reverse(array, n - k, n - 1, size);
    reverse(array, 0, n - 1, size);
}

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

