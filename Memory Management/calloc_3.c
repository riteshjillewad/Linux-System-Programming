#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *ptr = NULL;
    int i = 0;

    printf("Memory before calloc: %p\n", (void*)ptr);

    ptr = (int*)calloc(5, sizeof(int));
    if(ptr == NULL)
    {
        printf("Failed to allocate memory!\n");
        return -1;
    }

    printf("Memory allocated successfully at: %p\n", (void*)ptr);

    printf("Values after calloc (should be 0):\n");
    for(i = 0; i < 5; i++)
    {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    
    printf("Enter 5 elements: \n");
    for(i = 0; i < 5; i++)
    {
        scanf("%d", &ptr[i]);
    }
    
    printf("Array elements: \n");
    for(i = 0; i < 5; i++)
    {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }

    free(ptr);
    ptr = NULL;
    return 0;
}

