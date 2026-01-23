#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *ptr = NULL;
    int *temp = NULL;

    printf("Allocating memory with malloc...\n");
    ptr = (int*)malloc(5 * sizeof(int));
    if(ptr == NULL)
    {
        printf("malloc failed!\n");
        return -1;
    }
    printf("Memory allocated successfully with malloc\n");
    printf("Allocated bytes: %ld\n", 5 * sizeof(int));

    printf("\nReallocating the memory...\n");
    temp = (int*)realloc(ptr, 10 * sizeof(int));
    if(temp == NULL)
    {
        printf("realloc failed! Old memory still valid.\n");
        free(ptr);
        return -1;
    }

    ptr = temp;
    printf("Memory reallocated successfully with realloc\n");
    printf("Reallocated bytes: %ld\n", 10 * sizeof(int));

    free(ptr);
    ptr = NULL;

    return 0;
}

