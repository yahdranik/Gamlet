#include "Onegin.h"
#include "sorts.h"

//TODO - логи или сделать норм вывод ошибок
int main()
{
    struct FileData file_info = read_file_and_get_data();

    if (file_info.size_of_file == 0)
    {
        printf(MY_RED_AND_BOLD "Error. File if empty and not sliced\n" MY_END_CUSTOM);
        return EMPTY_FILE;
    }

    quick_sort(file_info.list_indexes_1, file_info.count_of_strings, sizeof(char*), compare_for_beginning_strings);
    qsort(file_info.list_indexes_2, file_info.count_of_strings, sizeof(char*), compare_for_end_strings);

    print_into_file(file_info);

    FREE_MASS(file_info.original_text, file_info.size_of_file);
    FREE_MASS(file_info.list_indexes_1, file_info.count_of_strings);
    FREE_MASS(file_info.list_indexes_2, file_info.count_of_strings);
    FREE_MASS(file_info.list_indexes_3, file_info.count_of_strings);
}

ssize_t get_file_size(const char* NAME)
{
    struct stat file_info = {};
    stat(NAME, &file_info);
    ssize_t SIZE_OF_FILE = file_info.st_size;

    if (SIZE_OF_FILE == -1 || SIZE_OF_FILE == 0)
    {
        return EMPTY_FILE;
    }

    return SIZE_OF_FILE;
}

size_t count_entry_in_string(char* array, size_t len_array, char symbol)
{
    size_t counter = 0;
    for (size_t i = 0; i < len_array - 1; i++)
    {
        if (array[i] == symbol)
        {
            counter++;
        }
    }
    return counter;
}

int slize_to_string(char* array, char** sliced_array, size_t len_array) 
{
    sliced_array[0] = array;
    size_t line_number = 1;
    
    for (size_t i = 0; i < len_array; i++)
    {
        if (array[i] == '\n')
        {
            array[i] = '\0';
            sliced_array[line_number] = array + i + 1;
            line_number += 1;
        }
    }

    if (line_number == 1)
    {
        return NOT_SLICED;
    }

    return 0;
}

struct FileData read_file_and_get_data()
{
    FILE* text = fopen(FILE_NAME, "r");
    if (text == NULL) 
    {
        return {};
    }

    ssize_t SIZE_OF_FILE = get_file_size(FILE_NAME);

    if (SIZE_OF_FILE == EMPTY_FILE)
    {
        return {};
    }

    char* original_text = (char*) calloc(SIZE_OF_FILE, sizeof(char));
    if (original_text == NULL) {return {};}

    SIZE_OF_FILE = fread(original_text, sizeof(char), SIZE_OF_FILE + 1, text);

    fclose(text);

    ssize_t count_of_strings = count_entry_in_string(original_text, SIZE_OF_FILE, '\n') + 1;

    char** list_index_1 = (char**) calloc(count_of_strings, sizeof(char*));
    if (list_index_1 == NULL) {return {};}

    char** list_index_2 = (char**) calloc(count_of_strings, sizeof(char*));
    if (list_index_2 == NULL) {return {};}

    char** list_index_3 = (char**) calloc(count_of_strings, sizeof(char*));
    if (list_index_3 == NULL) {return {};}

    int res_of_slice = slize_to_string(original_text, list_index_1, SIZE_OF_FILE);
    if (res_of_slice == NOT_SLICED) {return {};}

    my_memcpy(list_index_2, list_index_1, (count_of_strings) * sizeof(char*));
    my_memcpy(list_index_3, list_index_1, (count_of_strings) * sizeof(char*));

    struct FileData file_info = {SIZE_OF_FILE, count_of_strings, original_text, list_index_1,
                                                                                list_index_2,
                                                                                list_index_3};
    return file_info;
}

int compare_for_beginning_strings(const void* a, const void* b)
{
    const char* const* elem_1 = (const char* const*) a;
    const char* const* elem_2 = (const char* const*) b;

    return strcmp_letters_only(*elem_1, *elem_2);
}

int compare_for_end_strings(const void* a, const void* b)
{
    char** elem_1 = (char**) a;
    char** elem_2 = (char**) b;

    my_strrev(*elem_1);
    my_strrev(*elem_2);

    int value = strcmp_letters_only(*elem_1, *elem_2);

    my_strrev(*elem_1);
    my_strrev(*elem_2);

    return value;
}

void print_into_file(struct FileData data)
{
    FILE* result = fopen("Onegin_result.txt", "w");

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nSORT FOR BEGIN\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n");

    print_strings_into_file(result, data.list_indexes_1, data.count_of_strings);

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nSORT FOR END\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n");

    print_strings_into_file(result, data.list_indexes_2, data.count_of_strings);

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nTHE ORIGINAL\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n");

    print_strings_into_file(result, data.list_indexes_3, data.count_of_strings);

    fclose(result);
}

void print_strings_into_file(FILE* filestream, char** array, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        if (array[i] != NULL && *array[i] != '\0')
        {
            fprintf(filestream, "%s\n", array[i]);
        }
    }
}

int strcmp_letters_only(const char* string_1, const char* string_2)
{

    const char* pointer_1 = string_1;
    const char* pointer_2 = string_2;

    while (*pointer_1 != '\n' && *pointer_2 != '\n')
    {
        while (!isalpha(*pointer_1) && *pointer_1 != '\n')
        {
            pointer_1++;
        }

        while (!isalpha(*pointer_2) && *pointer_2 != '\n')
        {
            pointer_2++;
        }
        if (*pointer_1 != *pointer_2)
        {
            return (int) *pointer_1 - (int) *pointer_2;
        }

        pointer_1++;
        pointer_2++;
    }

    return 0;
}

char* my_strrev(char* string)
{
    if (string == NULL) 
    {
        return NULL;
    }

    size_t length_of_string = my_strlen(string);
    char help_cell = 0;

    for (size_t i = 0; i < length_of_string / 2; i++)
    {
        help_cell = string[i];
        string[i] = string[length_of_string - i - 1];
        string[length_of_string - i - 1] = help_cell;
    }
    
    return string;
}

size_t my_strlen(const char* string)
{
    if (string == NULL)
    {
        return 0;
    }

    size_t count_of_symbols = 0;
    while (string[count_of_symbols] != '\0' && string[count_of_symbols] != '\n')
    {
        count_of_symbols += 1;
    }
    return count_of_symbols;
}

void* my_memcpy(void* destination, const void* source, size_t n )
{
    size_t cursor = 0;
    if (destination == NULL || source == NULL || n == 0)
    {
        return NULL;
    }

    uint64_t* destination_1 = (uint64_t*) destination;
    uint64_t* source_1 = (uint64_t*) source;

    for (size_t i = 0; i <= n / sizeof(uint64_t); i++)
    {
        destination_1[i] = source_1[i];
        cursor = i;
    }
    n = n % sizeof(uint64_t);

    if (n >= 4)
    {
        uint32_t* destination_2 = (uint32_t*) destination;
        uint32_t* source_2 = (uint32_t*) source;
        destination_2[cursor * 2 + 1] = source_2[cursor * 2 + 1];
        cursor = cursor * 2 + 1;
    }
    n = n % sizeof(uint32_t);

    if (n >= 2)
    {
        uint16_t* destination_3 = (uint16_t*) destination;
        uint16_t* source_3 = (uint16_t*) source;
        destination_3[cursor * 2 + 1] = source_3[cursor * 2 + 1];
        cursor = cursor * 2 + 1;
    }
    n = n % sizeof(uint16_t);

    if(n >= 1)
    {
        uint8_t* destination_4 = (uint8_t*) destination;
        uint8_t* source_4 = (uint8_t*) source;
        destination_4[cursor * 2 + 1] = source_4[cursor * 2 + 1];     
    }

    return (void*) destination;
}