/* THIS IS THE CLIENT CODE FOR SHARED MEMORY - IT WILL READ DATA FROM SHARED MEMORY */

#include<stdio.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/ipc.h>

int main()
{
    key_t key;
    size_t size = 1024;
    int shmid = 0;
    
    key = ftok(".", 'a');
    if(key == -1)
    {
        perror("Error generating unique key");
        return -1;
    }
    
    shmid = shmget(key, size, 0666);
    if(shmid != -1)
    {
        printf("Shared memory segment created by client.\n");
    }
    
    return 0;
}
