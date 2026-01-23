#include<stdio.h>
#include<sys/mman.h>

int main() 
{
    size_t size = 4096;
    
    // Allocate
    void *mem = mmap(NULL, size,
                    PROT_READ | PROT_WRITE,
                    MAP_ANONYMOUS | MAP_PRIVATE,
                    -1, 0);
    
    printf("Mapped %zu bytes at %p\n", size, mem);
    
    // Use memory...
    int *array = (int *)mem;
    array[0] = 42;
    
    // Unmap
    if(munmap(mem, size) == 0) 
    {
        printf("Successfully unmapped\n");
    } 
    else 
    {
        perror("munmap failed");
    }
    
    // mem is now invalid! Don't use it!
    
    return 0;
}
