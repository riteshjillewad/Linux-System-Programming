#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *arr = NULL;
    int *temp = NULL;
    int i = 0;

    // Allocate 5 integers
    arr = (int*)malloc(5 * sizeof(int));
    if(arr == NULL)
    {
        printf("malloc failed!\n");
        return -1;
    }

    // Store values
    for(i = 0; i < 5; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    printf("Before realloc (5 elements):\n");
    for(i = 0; i < 5; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    printf("\nAddress before realloc: %p\n", (void*)arr);

    // Expand to 10 integers
    temp = (int*)realloc(arr, 10 * sizeof(int));
    if(temp == NULL)
    {
        printf("realloc failed! Old memory still valid.\n");
        free(arr);
        return -1;
    }

    arr = temp;
    printf("\nAddress after realloc: %p\n", (void*)arr);

    // Add new values in extra memory
    for(i = 5; i < 10; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    printf("\nAfter realloc (10 elements):\n");
    for(i = 0; i < 10; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}

