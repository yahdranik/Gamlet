#include "oper_with_str.h"
#include "oper_with_file.h"
#include "all_for_sort.h"

#define MY_RED_AND_BOLD        "\033[1;31m"
#define MY_END_CUSTOM          "\033[0m"

const char* INPUT_FILE_NAME = "Onegin.txt";
const char* OUTPUT_FILE_NAME = "Onegin_result.txt";

int main()
{
    FileData file_info = read_file_and_get_data(INPUT_FILE_NAME);

    if (file_info.size_of_file == 0)
    {
        printf(MY_RED_AND_BOLD "Error\n" MY_END_CUSTOM);
        return UNVALIBLE_FILE_SIZE;
    }
    
    StringData* array_to_sort = (StringData*) calloc(file_info.count_of_strings, sizeof(StringData));
    if (array_to_sort == NULL)
    {
        printf("Calloc sdoh\n");
        FREE_MASS(file_info.original_text);
        return NOT_ALLOCATE;
    }
    
    get_string_data(array_to_sort, file_info.original_text, file_info.size_of_file);

    FILE* result = fopen(OUTPUT_FILE_NAME, "a");
    if (result == NULL) { fclose(result); perror("File not open"); return FILE_NOT_OPEN; }

    quick_sort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_beginning_strings);
    print_into_file(result, file_info, array_to_sort, SORT_FOR_BEGIN);


    qsort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_end_strings);
    print_into_file(result, file_info, array_to_sort, SORT_FOR_END);


    qsort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_indexes);
    print_into_file(result, file_info, array_to_sort, ORIGINAL);

    fclose(result);

    FREE_MASS(file_info.original_text);
    FREE_MASS(array_to_sort);

    return 0;
}