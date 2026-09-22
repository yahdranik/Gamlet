//TODO переписать для strchr
size_t count_entry_in_string(char* array, char symbol)
{
    size_t counter = 0;
    char* array_copy = array;
    while (true)
    {
        char* entry = strchr(array_copy, symbol);
        if (entry == NULL)
        {
            break;
        }

        array_copy = entry + 1;
    }
    return counter;
}

int slize_to_string(char* array, char** sliced_array, size_t len_array) 
{
    sliced_array[0] = array;
    size_t line_number = 1;
    
    for (size_t i = 0; i < len_array - 1; i++)
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

void* my_memcpy(void* destination, const void* source, size_t n)
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

