#include<stdio.h>
#include<stdlib.h>

/* THIS CODE SHOWS THAT MALLOC MAY REUSE THE SAME MEMORY AGAIN */

int main()
{
    int *p1 = NULL;
    int *p2 = NULL;

    p1 = malloc(100);
    printf("p1 = %p\n", (void*)p1);
    free(p1);

    p2 = malloc(100);
    printf("p2 = %p\n", (void*)p2);
    free(p2);

    return 0;
}

