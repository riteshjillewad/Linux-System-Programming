#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *ptr = NULL;

    printf("Memory before calloc: %p\n", (void*)ptr);

    ptr = (int*)calloc(5, sizeof(int));
    if(ptr == NULL)
    {
        printf("Failed to allocate memory!\n");
        return -1;
    }

    printf("Memory allocated successfully at: %p\n", (void*)ptr);

    free(ptr);
    ptr = NULL;
    return 0;
}

