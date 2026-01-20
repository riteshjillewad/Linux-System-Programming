/* THIS IS THE SERVER CODE FOR SHARED MEMORY - IT WILL WRITE DATA TO SHARED MEMORY */

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
    
    shmid = shmget(key, size, 0666 | IPC_CREAT);
    if(shmid != -1)
    {
        printf("Shared memory segment created by server.\n");
    }
    
    return 0;
}
