#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *arr = NULL;
    int i = 0;

    arr = (int*)malloc(5 * sizeof(int));
    
    printf("Values after malloc (garbage):\n");
    for(i = 0; i < 5; i++)
    {
        printf("%d\n", arr[i]);
    }

    free(arr);
    return 0;
}

