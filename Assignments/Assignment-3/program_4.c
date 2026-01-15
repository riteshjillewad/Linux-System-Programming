////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_4.c
// Task:          1. Accept directory name
//                2. Delete files with size = 0 bytes (regular files only)
//                3. Print names deleted + total deleted count
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
// Name:         deleteEmptyFiles
// Description:  Identify and delete regular files that have 0 bytes size
// Input:        Directory path
// Output:       Names of deleted files and total count
// Date:         Jan 15, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void deleteEmptyFiles(const char* directoryName)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat fileStat;
    char filePath[BUFFER_SIZE] = {'\0'};
    int count = 0;

    dp = opendir(directoryName);
    if(dp == NULL) 
    { 
        perror("Error opening directory"); 
        return; 
    }

    printf("\n--- Scanning directory: %s ---\n", directoryName);

    while((ptr = readdir(dp)) != NULL) 
    {
        if(strcmp(ptr -> d_name, ".") == 0 || strcmp(ptr -> d_name, "..") == 0)
        {
            continue;
        }

        strcpy(filePath, directoryName);
        strcat(filePath, "/");
        strcat(filePath, ptr -> d_name);

        if(stat(filePath, &fileStat) == 0)
        {
            if(S_ISREG(fileStat.st_mode) && fileStat.st_size == 0)
            {
                if(unlink(filePath) == 0)
                {
                    printf("Deleted: %s\n", ptr->d_name);
                    count++;
                }
                else
                {
                    printf("Failed to delete: %s. ", ptr->d_name);
                    perror("Reason");
                }
            }
        }
    }
    
    closedir(dp);

    printf("\n-----------------------------------------------\n");
    printf("Operation Complete.\n");
    printf("Total empty files deleted: %d\n", count);
    printf("-----------------------------------------------\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char directoryName[256];
    
    memset(directoryName, '\0', 256);
    
    printf("Enter the directory name to clean: ");
    if (scanf("%255[^\n]", directoryName) != 1) return 1;

    deleteEmptyFiles(directoryName);

    return 0;
}