#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *arr = malloc(5 * sizeof(int));
    if(arr == NULL)
    {
        printf("malloc failed!\n");
        return -1;
    }

    printf("Allocated arr at: %p\n", (void*)arr);

    // Freeing using realloc(arr, 0)
    arr = realloc(arr, 0);

    printf("After realloc(arr, 0), arr = %p\n", (void*)arr);
    printf("Memory is freed, arr should not be used now.\n");

    return 0;
}

