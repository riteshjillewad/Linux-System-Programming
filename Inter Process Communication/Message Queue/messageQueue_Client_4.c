/* THIS IS MESSAGE QUEUE CLIENT CODE -> IT WILL READ DATA FROM MESSAGE QUEUE */

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
    struct msqid_ds qinfo;
    
    key = ftok(".", 'r');
    if(key == -1)
    {
        printf("Unable to create unique key!\n");
        return -1;
    }
    
    mqid = msgget(key, 0666);
    if(mqid == -1)
    {
        printf("Unable to open message queue by client!\n");
        return -1;
    }
    
    iRet = msgrcv(mqid, (void *)&robj, MAX_BUFFER_SIZE, 11, 0);                   // Can specify IPC_NOWAIT so that client does not go to waiting state 
    if(iRet > 0)
    {
        printf("Message read successfully from message queue by client.\n");
        printf("Message: %s\n", robj.buffer);
    }
    
    
    if(msgctl(mqid, IPC_STAT, &qinfo) == -1)
    {
        perror("msgctl IPC_STAT");
        return -1;
    }

    printf("-----------------------------------------------------------\n");
    printf("Current bytes in queue: %ld\n", qinfo.msg_cbytes);
    printf("Number of messages: %ld\n", qinfo.msg_qnum);
    printf("-----------------------------------------------------------\n");
    
    return 0;
}

