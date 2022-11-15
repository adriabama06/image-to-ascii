#include "include/string-util.h"

#include <stdlib.h>
#include <string.h>

STRING string_from(char* c_str)
{
    STRING str;

    str.length = strlen(c_str);

    str.data = (char*) malloc(str.length * sizeof(char));

    strncpy(str.data, c_str, str.length);

    return str;
}

int endsWith(char* str, char* sub_str)
{
    int str_len = strlen(str);
    int sub_str_len = strlen(sub_str);

    if(sub_str_len > str_len)
    {
        return 0;
    }

    for (int i = 0; i < sub_str_len; i++)
    {
        if(str[(str_len - sub_str_len) + i] != sub_str[i])
        {
            return 0;
        }
    }

    return 1;
}

char* get_filename(char* file)
{
    // myfile.txt
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    // myfile.txt
    //       |<-- return pointer to this word
    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return NULL;
    }

    *ext = '\0';

    /*
        Ignore this if you not are adriabama06
        TOME:
            if i like, copy the filename to filename_clear because "txt" exist in memory but because is "\0" where "." whas before it uses extra memory
    */

    return filename;
}

char* get_extension(char* file)
{
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return NULL;
    }

    /*
        Ignore this if you not are adriabama06
        TOME:
            SEE get_filename
            ext_clear = malloc strlen(ext)
            copy ext -> ext_clear
            free ext
            return ext_clear
    */

    return ext;
}

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