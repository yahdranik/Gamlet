#include "Onegin.h"
#include "all_for_sort.c"
#include "oper_with_file.c"
#include "oper_with_str.c"

//TODO - логи 

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
