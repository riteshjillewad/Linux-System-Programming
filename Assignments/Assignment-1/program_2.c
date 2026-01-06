////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_2.c
// Task:          1. Accept file name and mode(R, W, RW, A) from user
//                2. Convert mode to flags
//                3. Open file accordingly and display fd
// Date:          Jan 5, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 50

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         openFile
// Description:  This function is used to open the file
// Input:        File name and mode
// Output:       Opened file
// Date:         Jan 5, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void openFile(const char *fileName, const char *mode)
{
    int fd = -1;
    int flags = 0;

    if(strcmp(mode, "R") == 0)
    {
        flags = O_RDONLY;
    }
    else if(strcmp(mode, "W") == 0)
    {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if(strcmp(mode, "RW") == 0)
    {
        flags = O_RDWR | O_CREAT;
    }
    else if(strcmp(mode, "A") == 0)
    {
        flags = O_WRONLY | O_CREAT | O_APPEND;
    }
    else if(strcmp(mode, "C") == 0)
    {
        flags = O_CREAT | O_EXCL | O_WRONLY;
    }
    else if(strcmp(mode, "ALL") == 0)
    {
        flags = O_RDWR | O_CREAT | O_APPEND;
    }
    else
    {
        printf("Invalid mode\n");
        return;
    }

    fd = open(fileName, flags, 0777);
    if(fd == -1)
    {
        perror("open failed");
        return;
    }

    printf("File opened successfully\n");
    printf("Mode : %s\n", mode);
    printf("FD   : %d\n", fd);

    close(fd);
}
  
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];
    char mode[10];

    memset(fileName, 0, BUFFER_SIZE);
    memset(mode, 0, sizeof(mode));

    printf("Enter file name: \n");
    scanf("%[^\n]", fileName);
    getchar();

    printf("--------- File mode options ---------\n"); 
    printf("1. R   (Read only)\n"); 
    printf("2. W   (Write only)\n"); 
    printf("3. RW  (Read-Write)\n"); 
    printf("4. A   (Append)\n"); 
    printf("5. C   (Create)\n"); 
    printf("6. ALL (All options)\n");
    printf("--------------------------------------\n");
    printf("Enter mode: \n");
    scanf("%[^\n]", mode);

    openFile(fileName, mode);
    return 0;
}// End of main


