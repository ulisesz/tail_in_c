#include "fileTailHelper.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

static char** getTail(FILE* fileHandle, int numberOfLines);
static void printTail(char** fileTail, int numberOfLines);
static char** initFifoQueue(numberOfLines);
static void fifoQueueInsert(FILE* fileHandle, char** queue, int numberOfLines);
static char* getFileLine(FILE* fileHandle);
static void freeQueue(char** queue, int numberOfLines);
static int hasReachedNewline(char* line);
static int isQueueFull(char** queue, int numberOfLines);
static void leftShiftQueue(char** queue); // TODO;

// Tail operations

void printFileTail(FILE* fileHandle, int numberOfLines)
{
    char** fileTail = getTail(fileHandle, numberOfLines);
    printTail(fileTail, numberOfLines);
    freeQueue(fileTail, numberOfLines);
}

static char** getTail(FILE* fileHandle, int numberOfLines)
{
    char** queue = initFifoQueue(numberOfLines);
    
    while (!feof(fileHandle))
    {
        fifoQueueInsert(fileHandle, queue, numberOfLines);
    }

    return queue;
}

static void printTail(char** fileTail, int numberOfLines)
{
    printf(" - Tail Output:\n");

    for (int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
    {
        printf("[%d]: %s", lineIndex, fileTail[lineIndex]);
    }
}

// Queue operations

static char** initFifoQueue(numberOfLines)
{
    size_t queueSize = sizeof(char*) * numberOfLines;
    char** queue = calloc(queueSize, queueSize);
    
    for (int queueIndex = 0; queueIndex < numberOfLines; queueIndex++)
    {
        queue[queueIndex] = NULL;
    }

    return queue;
}

static void fifoQueueInsert(FILE* fileHandle, char** queue, int numberOfLines)
{
    char* fileLine = getFileLine(fileHandle);
    if (isQueueFull(queue, numberOfLines))
    {
        leftShiftQueue(queue);
    }
    addToEndOfQueue(fileLine);
}

static char* getFileLine(FILE* fileHandle)
{
    char* fileLine = NULL;

    while (!hasReachedNewline(fileLine))
    {
        char lineSegment[100];
        fgets(lineSegment, 100, fileHandle);

        size_t newLineSize = strlen(lineSegment) + 1;
        if (fileLine = NULL)
        {
            fileLine = (char*)calloc(newLineSize, newLineSize);
            strcpy_s(fileLine, newLineSize, lineSegment);
        }
        else
        {
            size_t existingLineSize = strlen(fileLine);
            char* newPtr = realloc(fileLine, existingLineSize + newLineSize);
            fileLine = newPtr;
            strcpy_s(fileLine + existingLineSize, newLineSize, lineSegment);
        }
    }

    return fileLine;
}

static int hasReachedNewline(char* line)
{
    if (line)
    {
        int stringLength = strlen(line);
        return (line[stringLength] == '\n');
    }
    else 
    {
        return FALSE;
    }
}

static void freeQueue(char** queue, int numberOfLines)
{
    for (int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
    {
        free(queue[lineIndex]);
    }

    free(queue);
}

static int isQueueFull(char** queue, int numberOfLines)
{
    for (int queueIndex = 0; queueIndex < numberOfLines; queueIndex++)
    {
        if (!queue[queueIndex])
        {
            return FALSE;
        }
    }
    return TRUE;
}

static void 