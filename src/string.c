#include "include/string-util.h"

#include <stdlib.h>
#include <string.h>

STRING string_from(const char* c_str)
{
    STRING str;

    str.length = strlen(c_str);

    //                                   + 1 for '\0'
    str.data = (char*) malloc(str.length + 1 * sizeof(char));

    //                                  + 1 for '\0'
    strncpy(str.data, c_str, str.length + 1);

    str.data[str.length] = '\0';

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

void free_string_array(STRING_ARRAY arr)
{
    for (uint32_t i = 0; i < arr.length; i++)
    {
        free(arr.strings[i].data);
    }

    free(arr.strings);
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