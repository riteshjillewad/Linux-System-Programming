/* malloc vs calloc demonstration */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *a = NULL;
    int *b = NULL;
    int i = 0;

    a = (int*)malloc(5 * sizeof(int));
    b = (int*)calloc(5, sizeof(int));

    if(a == NULL || b == NULL)
    {
        printf("Memory allocation failed!\n");
        free(a);
        free(b);
        return -1;
    }

    printf("malloc block address : %p\n", (void*)a);
    printf("calloc block address : %p\n", (void*)b);

    printf("\nValues after malloc (uninitialized / garbage):\n");
    for(i = 0; i < 5; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }

    printf("\nValues after calloc (initialized to 0):\n");
    for(i = 0; i < 5; i++)
    {
        printf("b[%d] = %d\n", i, b[i]);
    }

    free(a);
    free(b);
    a = NULL;
    b = NULL;

    return 0;
}

