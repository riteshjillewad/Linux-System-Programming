#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *ptr = NULL;

    printf("Memory before malloc: %p\n", (void*)ptr);

    printf("Allocating the memory...\n");
    ptr = (int *)malloc(5 * sizeof(int));
    if(ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Memory allocated successfully\n");
    printf("Memory after malloc: %p\n", (void*)ptr);

    printf("Allocated %ld bytes\n", 5 * sizeof(int));

    free(ptr);
    return 0;
}

