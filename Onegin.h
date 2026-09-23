#ifndef ONEGIN_H
#define ONEGIN_H

// #include "TXlib.h"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdint>


#define MY_RED_AND_BOLD        "\033[1;31m"
#define MY_END_CUSTOM          "\033[0m"

#define FREE_MASS(array) do {                           \
    free(array);                                        \
    array = NULL;                                       \
} while(0)

enum Mode
{
    SORT_FOR_BEGIN,
    SORT_FOR_END,
    ORIGINAL
};

enum Erros
{
    EMPTY_FILE,
    NOT_SLICED,
    FILE_NOT_OPEN,
    NOT_ALLOCATE
};

struct StringData
{
    int index;
    char* begin_pointer;
    size_t length;
};

struct FileData
{
    size_t size_of_file;
    size_t count_of_strings;
    char* original_text;
};

// functions for work with file ------------------------------------------------------------------------
struct FileData read_file_and_get_data(const char* FILE_NAME);
int print_into_file(const char* name, const FileData file_info, StringData* array, int mode);
int print_strings_into_file(FILE* filestream, StringData* array, size_t size);
ssize_t get_file_size(const char* name);


// functions for work with sorts -----------------------------------------------------------------------
int compare_for_beginning_strings(const void* a, const void* b);
int compare_for_end_strings(const void* a, const void* b);
int compare_for_indexes(const void* a, const void* b);
void quick_sort(void* array, size_t len_array, size_t size_element, int (*compare)(const void* a, const void* b));
void swap(void* a, void* b, size_t size_element);


// functions for work with strings ---------------------------------------------------------------------
size_t my_strlen(const char* string);
char* my_strrev(char* string);
int slize_to_string(char* array, char** sliced_array, size_t len_array);
size_t count_entry_in_string(char* array, char symbol);
int strcmp_letters_from_beginning(const char* string_1, size_t len_1, const char* string_2, size_t len_2);
int strcmp_letters_from_end(const char* string_1, size_t len_1, const char* string_2, size_t len_2);
int get_string_data(StringData* data_strings, char* array, size_t len_array);
void print_struct(StringData* str, size_t len);

const int MAX_LEN_STR = 100;
const int MAX_LINES = 1000;
const char* INPUT_FILE_NAME = "Onegin.txt";
const char* OUTPUT_FILE_NAME = "Onegin_result.txt";

#endif
