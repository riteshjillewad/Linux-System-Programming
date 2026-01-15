////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_2.c
// Task:          1. Accept directory name and file name
//                2. Check if the file exists in the directory
//                3. Print the absolute path if found
// Date:          Jan 15, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h, sys/stat.h, dirent.h, sys/types.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 1024

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         checkFile
// Description:  Check if the file is present in the directory
// Input:        Directory name, file name
// Output:       True or false
// Date:         Jan 15, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkFile(const char* directoryName, const char* fileName)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    bool found = false;

    dp = opendir(directoryName);
    if(dp == NULL)
    {
        perror("Directory open failed");
        return false;
    }

    while((ptr = readdir(dp)) != NULL)
    {
        if(strcmp(fileName, ptr->d_name) == 0)
        {
            found = true;
            break; 
        }
    }

    closedir(dp);
    return found;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char directoryName[256];
    char fileName[256];
    bool bRet = false;
    
    memset(directoryName, '\0', 256);
    memset(fileName, '\0', 256);
    
    printf("Enter the directory name(absolute path): \n");
    scanf("%[^\n]", directoryName);
    getchar();

    printf("Enter the file name: \n");
    scanf("%[^\n]", fileName);

    bRet = checkFile(directoryName, fileName);
    if(bRet == true)
    {
        printf("\n%s file found in %s directory.\n", fileName, directoryName);
    }
    else
    {
        printf("%s file not found in %s directory.\n", fileName, directoryName);
    }

    return 0;
}