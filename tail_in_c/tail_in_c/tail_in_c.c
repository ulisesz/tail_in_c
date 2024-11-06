#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argumentParser.h"
#include "fileTailHelper.h"

// usage: tail <FILENAME>
// usage: tail -n K <FILENAME>
// - "-n K" specifies number of lines to pull from end
// - no argument uses default value of 10 lines

int main(int argc, char** argv)
{
    printf("Tail implementation in c\n");

    if (!hasValidArguments(argc, argv))
    {
        printf("Invalid arguments, exiting!\n");
        goto exit;
    }

    int numberOfLines = 10;
    char* fileName = NULL;
    extractArguments(argc, argv, &numberOfLines, &fileName);
    printf(" - Number of lines: %d\n", numberOfLines);
    printf(" - FileName: %s\n", fileName);
    
    FILE* fileHandle = fopen(fileName, "r");
    if (!fileHandle)
    {
        printf("Invalid filename argument, exiting!\n");
        goto freeExit;
    }

    printFileTail(fileHandle, numberOfLines);
    fclose(fileHandle);

freeExit:
    free(fileName);

exit:
    printf("\n\n");
    return 0;
}