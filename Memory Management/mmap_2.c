#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>

int main()
{
    char *ptr = NULL;
    size_t size = 4096;
    
    ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap failed");
        return -1;
    }
    printf("Memory mapped successfully\n");
    
    printf("Writing data to mapped memory\n");
    strcpy(ptr, "Jay ganesh");
    
    printf("Reading data from mapped memory\n");
    printf("Data from mapped memory: %s\n", ptr);
    
    return 0;
}
    
