#include <stdint.h>

typedef struct STRING_ARRAY_STRUCT
{
    char** data;
    uint32_t length;
} STRING_ARRAY;

typedef struct PROGRAM_USER_INPUT_STRUCT
{    
    int input;
    int is_input_folder;
    char* input_path;
    
    int output;
    int is_output_folder;
    char* output_path;

    int multithread; // for futere implementation
} PROGRAM_USER_INPUT;

int endsWith(char*, char*);

char* get_filename(char*);

char* get_extension(char*);

int isDir(char*);

void invalidArguments(int, int);

PROGRAM_USER_INPUT parseArguments(int argc, const char *argv[]);

STRING_ARRAY* search_bmp(const char*);

void convert(char* input, char* output);

struct CONVERT_ARGS_STRUCT
{
    uint32_t from;
    uint32_t to;
    STRING_ARRAY* bmp_files;
    char* input_path;
    int input_path_length;
    char* output_path;
    int output_path_length;
};

void* convert_multithread(void* __args /* struct CONVERT_ARGS_STRUCT */);