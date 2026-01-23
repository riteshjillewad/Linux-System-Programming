#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *ptr = NULL;
    int size = 5;
    
    ptr = (int*)malloc(size * sizeof(int));
    if(ptr == NULL)
    {
        printf("Failed to allocate memory!\n");
        return -1;
    }
    printf("Memory allocated successfully\n");
    
    free(ptr);
    free(ptr);
    
    return 0;
}
