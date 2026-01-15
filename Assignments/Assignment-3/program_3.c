////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_3.c
// Task:          1. Accept source directory and destination directory
//                2. Move all regular files
//                3. Print count of moved files
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
void moveFiles(const char* sourceDir, const char* destDir)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    char oldPath[BUFFER_SIZE] = {'\0'};
    char newPath[BUFFER_SIZE] = {'\0'};
    int count = 0;

    /* Step 1: Open the source directory */
    dp = opendir(sourceDir);
    if(dp == NULL) 
    { 
        perror("Error opening source directory"); 
        return; 
    }

    /* Step 2: We check if the dest directory exists or not*/
    mkdir(destDir, 0777); 

    /* Step 3: Iterate through directory entries */
    while((ptr = readdir(dp)) != NULL) 
    {
        // We need to skip the . and .. entries
        if(strcmp(ptr -> d_name, ".") == 0 || strcmp(ptr -> d_name, "..") == 0)
        {
            continue;
        }

        // We only move regular files
        if (ptr -> d_type == DT_REG) 
        {
            // Build full paths for both source and destination
            snprintf(oldPath, sizeof(oldPath), "%s/%s", sourceDir, ptr -> d_name);
            snprintf(newPath, sizeof(newPath), "%s/%s", destDir, ptr -> d_name);

            // Move the files
            if (rename(oldPath, newPath) == 0) 
            {
                count++;
            }
            else
            {
                fprintf(stderr, "Failed to move: %s (Error: %s)\n", ptr- > d_name, strerror(errno));
            }
        }
    }
    
    closedir(dp);

    printf("\n-----------------------------------------------\n");
    printf("Operation Complete.\n");
    printf("Total regular files moved: %d\n", count);
    printf("-----------------------------------------------\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char sourceDirectory[256];
    char destinationDirectory[256];
    
    memset(sourceDirectory, '\0', 256);
    memset(destinationDirectory, '\0', 256);
    
    printf("Enter the source directory name: \n");
    scanf("%[^\n]", sourceDirectory);
    getchar();

    printf("Enter the destination directory name: \n");
    scanf("%[^\n]", destinationDirectory);

    moveFiles(sourceDirectory, destinationDirectory);

    return 0;
}