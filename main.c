#include "Onegin.h"
#include "all_for_sort.c"
#include "oper_with_file.c"
#include "oper_with_str.c"

int main()
{
    FileData file_info = read_file_and_get_data(INPUT_FILE_NAME);

    if (file_info.size_of_file == 0)
    {
        printf(MY_RED_AND_BOLD "Error\n" MY_END_CUSTOM);
        return EMPTY_FILE;
    }

    StringData* array_to_sort = (StringData*) calloc(file_info.count_of_strings, sizeof(StringData));
    if (array_to_sort == NULL)
    {
        printf("Calloc sdoh\n");
        FREE_MASS(file_info.original_text);
        return NOT_ALLOCATE;
    }

    get_string_data(array_to_sort, file_info.original_text, file_info.size_of_file);
    print_struct(array_to_sort, file_info.count_of_strings);
    
    qsort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_beginning_strings);
    print_into_file(OUTPUT_FILE_NAME, file_info, array_to_sort, SORT_FOR_BEGIN);


    qsort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_end_strings);
    print_into_file(OUTPUT_FILE_NAME, file_info, array_to_sort, SORT_FOR_END);


    qsort(array_to_sort, file_info.count_of_strings, sizeof(StringData), compare_for_indexes);
    print_into_file(OUTPUT_FILE_NAME, file_info, array_to_sort, ORIGINAL);


    FREE_MASS(file_info.original_text);
    FREE_MASS(array_to_sort);

    return 0;
}