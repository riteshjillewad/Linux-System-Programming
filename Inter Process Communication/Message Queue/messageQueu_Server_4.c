/* THIS IS MESSAGE QUEUE SERVER CODE -> IT WILL WRITE DATA TO MESSAGE QUEUE */

#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

#define MAX_BUFFER_SIZE 512

struct riteshMessage
{
    long int msgtype;
    char buffer[MAX_BUFFER_SIZE];
};

int main()
{
    key_t key;
    int mqid = 0;
    int iRet = 0;
    struct riteshMessage robj;
    
    key = ftok(".", 'r');
    if(key == -1)
    {
        printf("Unable to create unique key!\n");
        return -1;
    }
    
    mqid = msgget(key, 0666 | IPC_CREAT);
    if(mqid == -1)
    {
        printf("Unable to create message queue by server!\n");
        return -1;
    }
    
    robj.msgtype = 11;
    strcpy(robj.buffer, "Jay Ganesh...");

    iRet = msgsnd(mqid, (void *)&robj, MAX_BUFFER_SIZE, 0);
    if(iRet == -1)
    {
        perror("msgsnd");
        return -1;
    }
    printf("Message 1 sent successfully!\n");


    robj.msgtype = 11;                                                        // same type, client can read both by msgtype=11
    strcpy(robj.buffer, "Hello from Server - Message 2");

    iRet = msgsnd(mqid, &robj, MAX_BUFFER_SIZE, 0);
    if(iRet == -1)
    {
        perror("msgsnd");
        return -1;
    }
    printf("Message 2 sent successfully!\n");
    
    return 0;
}

