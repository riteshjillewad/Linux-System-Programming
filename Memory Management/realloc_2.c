#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *arr = NULL;
    int i = 0;

    arr = (int*)malloc(10 * sizeof(int));
    if(arr == NULL)
    {
        printf("malloc failed!\n");
        return -1;
    }

    // Fill values
    for(i = 0; i < 10; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    printf("Before shrinking:\n");
    for(i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Shrinking memory (10 -> 5)
    arr = (int*)realloc(arr, 5 * sizeof(int));
    if(arr == NULL)
    {
        printf("realloc shrink failed!\n");
        return -1;
    }

    printf("\nAfter shrinking to 5 elements:\n");
    for(i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // arr[5] to arr[9] are now invalid (out of bounds)

    free(arr);
    return 0;
}

