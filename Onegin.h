#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MY_RED_AND_BOLD        "\033[1;31m"
#define MY_END_CUSTOM          "\033[0m"

#define FREE_MASS(array, len_array) do {                \
    for (ssize_t i = 0; i < len_array; i++) {           \
        array[i] = 0;                                   \
    }                                                   \
    free(array);                                        \
    array = NULL;                                       \
} while(0)

enum Erros 
{
    EMPTY_FILE,
    NOT_SLICED
};

struct FileData
{
    ssize_t size_of_file;
    ssize_t count_of_strings;

    char* original_text;

    char** list_indexes_1;
    char** list_indexes_2;
    char** list_indexes_3;
};

struct FileData read_file_and_get_data();
int compare_for_beginning_strings(const void* a, const void* b);
void print_into_file(struct FileData data);
int strcmp_letters_only(const char* string_1, const char* string_2);
int compare_for_end_strings(const void* a, const void* b);
size_t my_strlen(const char* string);
char* my_strrev(char* string);
void print_strings_into_file(FILE* filestream, char** array, size_t size);
int slize_to_string(char* array, char** sliced_array, size_t len_array);
size_t count_entry_in_string(char* array, size_t len_array, char symbol);
ssize_t get_file_size(const char* NAME);
void* my_memcpy(void* destination, const void* source, size_t n );

const int MAX_LEN_STR = 100;
const int MAX_LINES = 1000;
const char* FILE_NAME = "Onegin.txt";