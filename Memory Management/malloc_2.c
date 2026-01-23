#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *arr = NULL;
    int i = 0, size = 0;
    
    printf("Enter the size of array: \n");
    scanf("%d", &size);
    
    if(size <= 0)
    {
        printf("Invalid size!\n");
        return -1;
    }
    
    arr = (int*)malloc(size * sizeof(int));
    if(arr == NULL)
    {
        printf("Memory allocation for array failed!\n");
        return -1;
    }
    printf("Memory for array allocated successfully\n");
    
    printf("Enter %d elements: \n", size);
    for(i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    printf("Allocated array: \n");
    for(i = 0; i < size; i++)
    {
        printf("arr[%d]: %d\n", i, arr[i]);
    }
    
    printf("Deallocating the memory...\n");
    free(arr);
    arr = NULL;
    printf("Deallocated memory successfully\n");
    
    return 0;
}
