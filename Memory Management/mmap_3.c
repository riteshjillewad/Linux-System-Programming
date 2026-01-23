#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char *file = NULL;
    int fd = 0;
    int i = 0;
    struct stat sb;
    
    fd = open("file1.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open fail");
        return -1;
    }
    
    fstat(fd, &sb);
    
    file = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(file == MAP_FAILED)
    {
        perror("mmap failed");
        return -1;
    }
    
    close(fd);
    
    for(i = 0; i < sb.st_size; i++)
    {
        printf("%c\n", file[i]);
    }
    
    return 0;
}
    
    
