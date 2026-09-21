
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

void print_into_file(struct FileData data)
{
    FILE* result = fopen("Onegin_result.txt", "w");

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nSORT FOR BEGIN\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");

    print_strings_into_file(result, data.list_indexes_1, data.count_of_strings);

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nSORT FOR END\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");

    print_strings_into_file(result, data.list_indexes_2, data.count_of_strings);

    fprintf(result, "\n-----------------------------------------------------------------------------------\n");
    fprintf(result, "\nTHE ORIGINAL\n");
    fprintf(result, "\n-----------------------------------------------------------------------------------\n\n");

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