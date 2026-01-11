////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_4.c
// Task:          1. Accept directory name
//                2. Find and print:
//                   Largest file name and its size in bytes
// Date:          Jan 11, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, errno.h, string.h, sys/types.h, dirent.h, sys/stat.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 1024

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         displayLargestFile
// Description:  Finds the longest filename in a directory and displays its metadata
// Input:        Directory name
// Output:       Prints largest filename and its size
// Date:         Jan 11, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayLargestFile(const char *directoryName)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat fileStat;
    
    char largestName[256] = "";
    int maxLen = 0;
    char fullPath[BUFFER_SIZE];

    /* Step 1: Open the directory */
    dp = opendir(directoryName);
    if(dp == NULL)
    {
        perror("Open failed");
        return;
    }

    /* Step 2: Iterate to find the longest name */
    while((ptr = readdir(dp)) != NULL)
    {
        // Skip current and parent directory entries
        if(strcmp(ptr -> d_name, ".") == 0 || strcmp(ptr -> d_name, "..") == 0)
        {
            continue;
        }

        int currentLen = strlen(ptr -> d_name);
        if(currentLen > maxLen)
        {
            maxLen = currentLen;
            // Store the longest name found so far
            strncpy(largestName, ptr -> d_name, sizeof(largestName) - 1);
        }
    }

    /* Step 3: If a file was found, get its size and print details */
    if(maxLen > 0)
    {
        /* Path construction part */
        strcpy(fullPath, directoryName);
        strcat(fullPath, "/");
        strcat(fullPath, largestName);

        if(stat(fullPath, &fileStat) == 0)
        {
            printf("\n-----------------------------------------------\n");
            printf("Largest Filename : %s\n", largestName);
            printf("Filename Length  : %d characters\n", maxLen);
            printf("File Size        : %ld bytes\n", (long)fileStat.st_size);
            printf("-----------------------------------------------\n");
        }
        else
        {
            perror("Stat failed for the largest file");
        }
    }
    else
    {
        printf("No files found in the directory.\n");
    }

    /* Step 4: Close the directory */
    closedir(dp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char directoryName[BUFFER_SIZE];
    
    memset(directoryName, '\0', BUFFER_SIZE);
    
    printf("Enter name of directory: \n");
    scanf("%[^\n]", directoryName);
    
    displayLargestFile(directoryName);
    return 0;
}// End of main