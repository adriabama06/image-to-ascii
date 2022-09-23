#include "include/bmp.h"

#include "include/image.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dirent.h>

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
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return 0;
    }

    *ext = '\0';

    return filename;
}

char* get_extension(char* file)
{
    char* filename = (char*) malloc(strlen(file) * sizeof(char));

    strcpy(filename, file);

    char* ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return 0;
    }

    return ext;
}

int isDir(char* dir_path)
{
    DIR* dir_to_scan = opendir(dir_path);

    if(dir_to_scan == NULL)
    {
        return 0;
    }

    closedir(dir_to_scan);

    return 1;
}

void invalidArguments(int i, int argc)
{
    if(i + 1 > argc)
    {
        printf("Invalid arguments, check if arguments are ok\n");
        exit(0);
    }
    return;
}

struct PROGRAM_USER_INPUT parseArguments(int argc, const char *argv[])
{
    struct PROGRAM_USER_INPUT options;

    options.input = 0;
    options.output = 0;
    options.multithread = 0;

    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];
        
        if(strcmp(arg, "--help") == 0)
        {
            printf("%s -i <input file/folder> -o <output file/folder>\n", argv[0]);
            printf("  (Optional) --help - Show this help menu\n");
            printf("  -i - Input file or folder, ONLY .bmp FILE SUPPORT\n");
            printf("  -o - Output file or folder if the input is a folder\n");
            printf("  (Optional) -t - Define number of threads for multithread, only work if the input is a folder\n");

            exit(0);
        }

        if(strcmp(arg, "-i") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.input = strlen(value);

            options.input_path = (char*) malloc(options.input * sizeof(char) + 1);

            strcpy(options.input_path, value);

            options.is_input_folder = isDir(options.input_path);

            continue;
        }

        if(strcmp(arg, "-o") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.output = strlen(value);

            options.output_path = (char*) malloc(options.output * sizeof(char) + 1);

            strcpy(options.output_path, value);

            options.is_output_folder = isDir(options.output_path);

            continue;
        }

        if(strcmp(arg, "-t") == 0)
        {
            invalidArguments(i, argc);

            i++;
            const char* value = argv[i];

            options.multithread = atoi(value);
            
            continue;
        }
    }

    if(options.input == 0 || options.output == 0)
    {
        printf("Please wrtie a input and output\n");

        exit(0);
    }

    if(options.is_input_folder != options.is_output_folder)
    {
        printf("If the input is a file, the output need to be a file, and the same for folders\n");
    
        exit(0);
    }

    return options;
}

void convert(char* input, char* output)
{
    BMP_DATA* bmp_data = bmp_read_data(input);
    
    IMAGE* raw_img = bmp_data_to_image(bmp_data);

    IMAGE* img = image_invert(raw_img);

    image_to_char_file(img, output);
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("%s --help\n", argv[0]);
        return 0;
    }

    struct PROGRAM_USER_INPUT options = parseArguments(argc, argv);

    if(options.is_input_folder == 0)
    {
        convert(options.input_path, options.output_path);
    }
    else
    {
        DIR* images_folder = opendir(options.input_path);
        
        long files_count = 0;

        while (readdir(images_folder)) {files_count++;}
    
        seekdir(images_folder, 0);

        struct dirent *dfile;

        char** files_to_work = (char**) malloc(files_count * sizeof(char*));
        long files_to_work_len = 0;

        for (long i = 0; i < files_count; i++)
        {
            dfile = readdir(images_folder);

            if(dfile->d_type == DT_REG)
            {
                if(endsWith(dfile->d_name, ".bmp"))
                {
                    files_to_work[files_to_work_len] = (char*) malloc(strlen(dfile->d_name) * sizeof(char));

                    strcpy(files_to_work[files_to_work_len], dfile->d_name);
                
                    files_to_work_len++;
                }
            }
        }

        for (long i = 0; i < files_to_work_len; i++)
        {
            char* file = files_to_work[i];

            char* file_input = (char*) malloc((options.input + strlen(file) + 1) * sizeof(char));

            strcpy(file_input, options.input_path);

            #ifdef _WIN32
                if(!endsWith(options.input_path, "\\"))
                {
                    strcat(file_input, "\\");
                }
            #else
                if(!endsWith(options.input_path, "/"))
                {
                    strcat(file_input, "/");
                }
            #endif
            

            strcat(file_input, file);

            char* file_name_no_extension = get_filename(file);

            char* file_bmp_extension = malloc((strlen(file_name_no_extension) + strlen(".bmp")) * sizeof(char));

            strcpy(file_bmp_extension, file_name_no_extension);

            strcat(file_bmp_extension, ".txt");

            char* file_output = (char*) malloc((options.output + strlen(file_bmp_extension) + 1) * sizeof(char));

            strcpy(file_output, options.output_path);

            #ifdef _WIN32
                if(!endsWith(options.output_path, "\\"))
                {
                    strcat(file_output, "\\");
                }
            #else
                if(!endsWith(options.output_path, "/"))
                {
                    strcat(file_output, "/");
                }
            #endif

            strcat(file_output, file_bmp_extension);

            convert(file_input, file_output);
        }
    }

    return 0;
}