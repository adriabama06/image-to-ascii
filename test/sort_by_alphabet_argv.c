#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct STRING_S
{
    char* data;
    uint32_t length;
} STRING;

typedef struct STRING_ARRAY_S
{
    STRING* strings;
    uint32_t length;
} STRING_ARRAY;

void sort_by_aplhabet(STRING_ARRAY arr)
{
    for(int i = 0; i < arr.length; i++)
    {
        for(int j = i + 1; j < arr.length; j++)
        {
            if(strcmp(arr.strings[i].data, arr.strings[j].data) > 0)
            {
                STRING temp;

                temp.length = arr.strings[i].length;
                
                temp.data = (char*) malloc(temp.length * sizeof(char));
                strcpy(temp.data, arr.strings[i].data);
                
                free(arr.strings[i].data);


                STRING str_j;

                str_j.length = arr.strings[j].length;

                str_j.data = (char*) malloc(str_j.length * sizeof(char));
                strcpy(str_j.data, arr.strings[j].data);

                free(arr.strings[j].data);
                

                arr.strings[i] = str_j;
                arr.strings[j] = temp;
            }
        }
    }
}

void print_string_array(STRING_ARRAY arr)
{
    for (size_t i = 0; i < arr.length; i++)
    {
        printf("INDEX %d -> %d - %s\n", i, arr.strings[i].length, arr.strings[i].data);
    }
}

void clear_string_array(STRING_ARRAY arr)
{
    for (size_t i = 0; i < arr.length; i++)
    {
        free(arr.strings[i].data);
    }

    free(arr.strings);
}

int main(int argc, char** argv)
{
    STRING_ARRAY input;
    input.length = argc - 1;
    input.strings = (STRING*) malloc(input.length * sizeof(STRING));


    for (size_t i = 1; i < argc; i++)
    {
        STRING str;
        str.length = strlen(argv[i]);
        
        str.data = (char*) malloc(str.length * sizeof(char));
        strcpy(str.data, argv[i]);

        input.strings[i - 1] = str;
    }

    print_string_array(input);

    sort_by_aplhabet(input);    
    
    printf("\n");
    
    print_string_array(input);

    clear_string_array(input);

    return 0;
}