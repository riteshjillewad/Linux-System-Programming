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
    char *ptr = NULL;
    
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
    
    ptr = shmat(shmid, NULL, 0);
    if(ptr == (char *) -1)
    {
        printf("Unable to attach shared memory segment by server!\n");
        return -1;
    }
    
    *ptr = 'R';
    ptr++;
    
    *ptr = 'i';
    ptr++;
    
    *ptr = 't';
    ptr++;
    
    *ptr = 'e';
    ptr++;
    
    *ptr = 's';
    ptr++;
    
    *ptr = 'h';
    ptr++;
    
    *ptr = '\0';
    
    printf("Data is written to shared memory segment by server.\n");
    
    shmdt(ptr);
    return 0;
}
