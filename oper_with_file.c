
#include <fcntl.h>
#include <unistd.h>

ssize_t get_file_size(const char* NAME)
{
    struct stat file_info = {};
    stat(NAME, &file_info);
    ssize_t size_of_file = file_info.st_size;

    if (size_of_file == -1 || size_of_file == 0)
    {
        return EMPTY_FILE;
    }

    return size_of_file;
}

struct FileData read_file_and_get_data(const char* FILE_NAME)
{
    int text = open(FILE_NAME, O_RDONLY);
    if (text == -1) {return {};}

    size_t size_of_file = get_file_size(FILE_NAME);
    if (size_of_file == EMPTY_FILE) {close(text); return {};}
    printf("%lld\n", size_of_file);
    char* original_text = (char*) calloc(size_of_file + 1, sizeof(char));
    if (original_text == NULL) {close(text); return {};}

    size_t bytes_read = read(text, original_text, size_of_file);
    if (bytes_read == -1) {close(text); FREE_MASS(original_text); return {};}
    printf("%lld\n", bytes_read);
    original_text[bytes_read] = '\0';

    close(text);

    size_t count_of_strings = count_entry_in_string(original_text, '\n');

    if (bytes_read > 0 && original_text[bytes_read - 1] != '\n')
    {
        original_text[bytes_read - 1] = '\n';
        count_of_strings += 1;
    }
    printf("%lld\n", count_of_strings);
    struct FileData file_info = {bytes_read, count_of_strings, original_text};
    printf("%s\n", file_info.original_text);
    return file_info;
}

int print_strings_into_file(FILE* filestream, StringData* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i].begin_pointer != NULL)
        {
            fprintf(filestream, "%s\n", array[i].begin_pointer);
        }
    }

    return 0;
}

// TODO проверка может ли fprintf еще выводить в файл 
int print_into_file(const char* name, const FileData file_info, StringData* array, int mode)
{
    FILE* result = fopen(name, "a");

    if (result == NULL) //TODO написать почему файл не открылся
    {
        fclose(result);
        return FILE_NOT_OPEN;
    }

    if (mode == SORT_FOR_BEGIN)
    {    
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
        fprintf(result, "SORT FOR BEGIN\n");
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
    }

    else if (mode == SORT_FOR_END)
    {    
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
        fprintf(result, "SORT FOR END\n");
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
    }
    
    else if (mode == ORIGINAL)
    {    
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
        fprintf(result, "THE ORIGINAL\n");
        fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");
    }

    print_strings_into_file(result, array, file_info.count_of_strings);

    fclose(result);
    return 0;
}
