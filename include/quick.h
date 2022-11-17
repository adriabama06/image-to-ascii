#include "arguments.h"
#include "string-util.h"

#define OUTPUT_EXTENSION ".txt"

void convert_to_file(const char*, const char*, char*);

typedef struct CONVERT_MULTIPLE_TO_FILE_ARGS_S
{
    uint32_t from;
    uint32_t to;

    STRING_ARRAY files;

    ARGUMENTS options;
} CONVERT_MULTIPLE_TO_FILE_ARGS;


void* convert_multiple_to_file(void* /* CONVERT_MULTIPLE_ARGS */);
