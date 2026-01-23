#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd;
    struct stat sb;
    char *file;
    

    fd = open("Pune.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open failed");
        return -1;
    }

    if(fstat(fd, &sb) == -1)
    {
        perror("fstat failed");
        close(fd);
        return -1;
    }

    if(sb.st_size == 0)
    {
        printf("File is empty, cannot mmap write.\n");
        close(fd);
        return 0;
    }

    file = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(file == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return -1;
    }

    close(fd);

    // Modify first few bytes of file
    // NOTE: We cannot write more than sb.st_size bytes!
    char msg[] = "HELLO";
    int len = strlen(msg);

    if(len > sb.st_size)
    {
        printf("Message too big for file size!\n");
        munmap(file, sb.st_size);
        return -1;
    }

    memcpy(file, msg, len);

    // Force changes to be written back to disk
    if(msync(file, sb.st_size, MS_SYNC) == -1)
    {
        perror("msync failed");
    }

    munmap(file, sb.st_size);

    printf("File modified successfully using mmap!\n");
    return 0;
}

