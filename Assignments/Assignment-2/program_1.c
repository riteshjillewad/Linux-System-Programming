////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_1.c
// Task:          1. Accept file name and print full contents on console
//                2. Use buffer loop (read() until 0)
//                3. Show total bytes read
// Date:          Jan 11, 2026
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
#define BUFFER_SIZE 100

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         readFile
// Description:  This function is used to read the contents of file
// Input:        File name
// Output:       File contents
// Date:         Jan 11, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void readFile(const char* fileName)
{
    int fd = 0;
    char buffer[BUFFER_SIZE];
    int iRet = 0, totalBytes = 0;

    memset(buffer, '\0', BUFFER_SIZE);

    /* First we need to open the file */
    fd = open(fileName, O_RDONLY);
    if(fd == -1)
    {
        perror("Open failed");
        return;
    }
    printf("%s opened successfully.\n", fileName);

    /* Now we need to read the contents of the file */
    while((iRet = read(fd, buffer, BUFFER_SIZE)) != 0)
    {
        write(1, buffer, iRet);
        totalBytes = totalBytes + iRet;
    }

    if(iRet == -1)
    {
        perror("Error reading file");
    }
    else
    {
        printf("%d bytes read successfully.\n", totalBytes);
    }

    close(fd);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];
    
    memset(fileName, '\0', BUFFER_SIZE);
    
    printf("Enter name of file: \n");
    scanf("%[^\n]", fileName);
    
    readFile(fileName);
    
    return 0;
}// End of main

