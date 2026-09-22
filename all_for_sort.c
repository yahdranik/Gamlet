
int compare_for_beginning_strings(const void* a, const void* b)
{
    const char* const* elem_1 = (const char* const*) a;
    const char* const* elem_2 = (const char* const*) b;

    return strcmp_letters_only(*elem_1, *elem_2);
}
//TODO убрать реверс и написать еще strcmp
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

void quick_sort(void* array, size_t len_array, size_t size_element, int (*compare)(const void* a, const void* b))
{
    uint8_t* ptr = (uint8_t *) array;

    if (len_array <= 1)
    {
        return;
    }

    uint8_t* pivot = ptr;
    uint8_t* left = ptr + size_element;
    uint8_t* right = ptr + len_array * size_element - size_element;

    while ( right >= left )
    {
        while (right >= left && compare(left, pivot) < 0)
        {
            left += size_element;
        }
        
        while (right >= left && compare(right, pivot) > 0)
        {
            right -= size_element;
        }

        if (left <= right)
        {
            swap(left, right, size_element);
            left += size_element;
            right -= size_element;
        }
    }

    swap(pivot, right, size_element);
    quick_sort(ptr, (right - ptr) / size_element, size_element, compare);
    quick_sort(right + size_element, len_array - (right - ptr) / size_element - 1, size_element, compare);
}

void swap(void* a, void* b, size_t size_element)
{
    uint8_t* elem_1 = (uint8_t*)a;
    uint8_t* elem_2 = (uint8_t*)b;
    
    for (size_t i = 0; i < size_element; i++) 
    {
        uint8_t temp = elem_1[i];
        elem_1[i] = elem_2[i];
        elem_2[i] = temp;
    }
}