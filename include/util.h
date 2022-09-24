#include <stdint.h>

typedef struct STRING_ARRAY_STRUCT
{
    char** data;
    uint32_t length;
} STRING_ARRAY;

struct PROGRAM_USER_INPUT
{    
    int input;
    int is_input_folder;
    char* input_path;
    
    int output;
    int is_output_folder;
    char* output_path;

    int multithread; // for futere implementation
};

int endsWith(char*, char*);

char* get_filename(char*);

char* get_extension(char*);

int isDir(char*);

void invalidArguments(int, int);

struct PROGRAM_USER_INPUT parseArguments(int argc, const char *argv[]);

STRING_ARRAY* search_bmp(const char*);