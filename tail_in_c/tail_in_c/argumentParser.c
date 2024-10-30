#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argumentParser.h"

int hasValidArguments(int argc, char** argv)
{
    int ret = TRUE;

    if (argc != 2 && argc != 4)
    {
        ret = FALSE;
        goto exit;
    }

    if (argc == 4)
    {
        char expectedFlagArgument[] = "-n";
        char* flagArgument = argv[1];
        char* numberOfLinesArgument = argv[2];
        int numberOfLines = atoi(numberOfLinesArgument);
        
        if (strcmp(expectedFlagArgument, flagArgument))
        {
            ret = FALSE;
            goto exit;
        }

        if (numberOfLines < 0)
        {
            ret = FALSE;
            goto exit;
        }
    }

exit:
    return ret;
}

void extractArguments(int argc, char** argv, int* numberOfLines, char** fileName)
{
    int fileNameIndex = 0;
    if (argc == 2)
    {
        *numberOfLines = 10;
        fileNameIndex = 1;
    }
    else
    {
        *numberOfLines = atoi(argv[2]);
        fileNameIndex = 3;
    }
    
    size_t numberOfCharacters = strlen(argv[fileNameIndex]) + 1;
    *fileName = (char*) calloc(numberOfCharacters, numberOfCharacters);
    strcpy_s(*fileName, numberOfCharacters, argv[fileNameIndex]);
}