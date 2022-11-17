#include "arguments.h"
#include "string-util.h"

void convert(const char*, const char*, char*);

typedef struct CONVERT_MULTIPLE_ARGS_S
{
    uint32_t from;
    uint32_t to;

    STRING_ARRAY files;

    ARGUMENTS options;
} CONVERT_MULTIPLE_ARGS;


void* convert_multiple(void* /* CONVERT_MULTIPLE_ARGS */);
