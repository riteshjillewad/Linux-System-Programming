////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_1.c
// Task:          1. Accept source file and destination file
//                2. Create destination file if it does not exists
//                3. Copy using buffered read()/write() loop
//                4. Preserve permissions
// Date:          Jan 11, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h, sys/stat.h
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

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 1024

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         copyFile
// Description:  Copy the file contents from source file to destination file
// Input:        Source path, Destination path
// Output:       Status message
// Date:         Jan 15, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void copyFile(const char* sourceFile, const char* destinationFile)
{
    int fdSource = 0;
    int fdDest = 0;
    int iRet = 0;
    char buffer[BUFFER_SIZE];
    struct stat statObj;

    /* Step 1: Open source and get its permissions */
    fdSource = open(sourceFile, O_RDONLY);
    if(fdSource == -1)
    {
        perror("Error opening source file");
        return;
    }

    // Task 4: Get source file metadata to preserve permissions
    if(fstat(fdSource, &statObj) == -1)
    {
        perror("Error getting source file permissions");
        close(fdSource);
        return;
    }

    /* Step 2: Open/Create destination file with preserved permissions */
    // O_TRUNC ensures that if the file exists, it is wiped before copying
    fdDest = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, statObj.st_mode);
    if(fdDest == -1)
    {
        perror("Error opening/creating destination file");
        close(fdSource);
        return;
    }

    /* Step 3: Buffered Loop for Copying (Task 3) */
    printf("Copying in progress...\n");
    while((iRet = read(fdSource, buffer, BUFFER_SIZE)) > 0)
    {
        // Write exactly the number of bytes that were read
        if(write(fdDest, buffer, iRet) != iRet)
        {
            perror("Write error occurred during copy");
            break;
        }
    }

    if(iRet == -1)
    {
        perror("Read error occurred during copy");
    }
    else
    {
        printf("File copied successfully from %s to %s\n", sourceFile, destinationFile);
        printf("Permissions preserved: %o\n", statObj.st_mode & 0777);
    }

    /* Step 4: Cleanup */
    close(fdSource);
    close(fdDest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char sourceFile[256];
    char destinationFile[256];
    
    memset(sourceFile, '\0', 256);
    memset(destinationFile, '\0', 256);
    
    printf("Enter the source file path: ");
    scanf("%255[^\n]", sourceFile);
    getchar(); // Clear newline

    printf("Enter the destination file path: ");
    scanf("%255[^\n]", destinationFile);

    copyFile(sourceFile, destinationFile);
    
    return 0;
}
