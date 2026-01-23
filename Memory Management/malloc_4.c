#include<stdio.h>
#include<stdlib.h>

/* THIS CODE SHOWS THAT MALLOC ALLOCATES CONTAGIOUS MEMORY */

int main()
{
    int *arr = NULL;

    arr = (int*)malloc(5 * sizeof(int));
    for(int i = 0; i < 5; i++)
    {
        printf("&arr[%d] = %p\n", i, (void*)&arr[i]);
    }

    free(arr);
    return 0;
}

