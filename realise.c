#include <stdio.h>
#include <cassert>
#include <unistd.h>
#include <stdint.h>


const char* string5 = "Hello";
const char* delim = ",";
const long int offset_adress = 100;
const int MY_MAX_LEN = 100;
const char* string1 = "Hello World";
const char* string2 = "Hello Mip";


size_t my_strlen( const char* string )
{
    assert(string);

    size_t count_of_symbols = 0;
    while (string[count_of_symbols] != '\0' && string[count_of_symbols] != '\n')
    {
        count_of_symbols += 1;
    }
    return count_of_symbols;
}

const char* my_strchr( const char* string, int symbol )
{
    if (string == NULL)
    {
        return NULL;
    }

    int number_of_symbol = 0;

    while (string[number_of_symbol] != symbol && string[number_of_symbol] != '\0')
    {
        number_of_symbol += 1;
    }

    return string + number_of_symbol;
}

int my_strcmp( const char* string1, const char* string2 ) 
{
    if (string1 == NULL || string2 == NULL)
    {
        return NULL;
    }

    size_t current_symbol = 0;

    while (true)
    {
        if (string1[current_symbol] != string2[current_symbol]) 
        {
            if (string1[current_symbol] > string2[current_symbol])
            {
                return 1;
            }
            return -1;
        }

        current_symbol += 1;
    }
    return 0;
}

int my_strncmp( const char* string1, const char* string2, size_t num )
{
    if (string1 == NULL || string2 == NULL)
    {
        return NULL;
    }    

    size_t current_symbol = 0;

    while (current_symbol != num)
    {
        if (string1[current_symbol] != string2[current_symbol]) 
        {
            if (string1[current_symbol] > string2[current_symbol])
            {
                return 1;
            }
            return -1;
        }

        current_symbol += 1;
    }
    return 0;
}

char* my_strcat( char* destptr, const char* srcptr )
{
    if (destptr == NULL || srcptr == NULL)
    {
        return NULL;
    }

    size_t length_of_destptr = my_strlen((const char*) destptr);
    size_t number_of_symbol = 0;

    while (srcptr[number_of_symbol] != '\0')
    {
        destptr[number_of_symbol + length_of_destptr] = srcptr[number_of_symbol];
        number_of_symbol += 1;
    }
    destptr[number_of_symbol + length_of_destptr] = '\0';

    return destptr;
}

char* my_strncat( char* destptr, const char* srcptr, size_t num )
{
    if (destptr == NULL || srcptr == NULL || num == NULL)
    {
        return NULL;
    }

    size_t length_of_destptr = my_strlen((const char*) destptr);
    size_t number_of_symbol = 0;

    while (number_of_symbol <= num)
    {
        if (srcptr[number_of_symbol] == '\0')
        {
            destptr[number_of_symbol + length_of_destptr] = '\0';
            break;
        }
        destptr[number_of_symbol + length_of_destptr] = srcptr[number_of_symbol];
        number_of_symbol += 1;
    }
    return destptr;
}

char* my_strcpy( char* destptr, const char* srcptr )
{
    if (destptr == NULL || srcptr == NULL)
    {
        return NULL;
    }

    size_t number_of_symbol = 0;
    while (srcptr[number_of_symbol] != '\0' || srcptr[number_of_symbol] != '\n')
    {
        destptr[number_of_symbol] = srcptr[number_of_symbol];
        number_of_symbol += 1;
    }
    destptr[number_of_symbol] = '\n';
    return destptr;
}

char* my_strncpy( char* destptr, const char* srcptr, size_t num )
{
    if (destptr == NULL || srcptr == NULL || num == NULL)
    {
        return NULL;
    }

    size_t number_of_symbol = 0;
    while (srcptr[number_of_symbol] != '\0' && number_of_symbol != num - 1)
    {
        destptr[number_of_symbol] = srcptr[number_of_symbol];
        number_of_symbol += 1;
    } 
    
    return destptr;
}

char* my_strdup( const char* s )
{
    if (s == NULL)
    {
        return NULL;
    }

    char* s_dublicate = (char*) malloc(my_strlen(s) + 1);
    return my_strcpy(s_dublicate, s);
}

char* my_strndup( const char* s, size_t num )
{
    if (s == NULL || num == 0)
    {
        return NULL;
    }
    char* s_dublicate = (char*) malloc(num);
    return my_strncpy(s_dublicate, s, num);
}

char* my_strsep( char** stringp, const char* delim )
{
    if (stringp == NULL|| *stringp == NULL || delim == NULL)
    {
        return NULL;
    }

    char* begin_adress = *stringp;
    char* current_adress = begin_adress;

    while (*current_adress != '\0')
    {
        for (const char* d = delim; *d != '\0'; d++)
        {
            if (*current_adress == *d)
            {
                *current_adress = '\0';
                *stringp = begin_adress + 1;
                return begin_adress;
            }

            current_adress += 1;
        }
    }

    begin_adress = NULL;
    return begin_adress;
}

int my_puts( const char* string )
{
    if (string == NULL)
    {
        return EOF;
    }
    size_t length_of_string = my_strlen(string);
    for (size_t i = 0; i < length_of_string; i++)
    {
        putchar(string[i]);
    }
    putchar('\n');
    return 1;
}

int my_fseek( FILE* filestream, long int offset, int origin )
{
    if (filestream == NULL)
    {
        return NULL;
    }

    int fd = fileno(filestream);
    if (lseek(fd, offset, origin) == -1)
    {
        return -1;
    }
    clearerr(filestream);
    return 0;
}

char* my_fgets( char* string, int num, FILE* filestream ) 
{
    if (filestream == NULL || string == NULL || num == 0)
    {
        return NULL;
    }

    size_t number_of_symbol = 0;

    while (number_of_symbol <= (size_t) num)
    {
        int file_symbol = fgetc(filestream);

        if (file_symbol == '\n')
        {
            break;
        }

        else if (file_symbol == EOF)
        {
            return NULL;
        }

        string[number_of_symbol] = (char) file_symbol;
        number_of_symbol += 1;
    }

    return string;
}

int my_fputs( const char* string, FILE* filestream )
{
    if (filestream == NULL || string == NULL)
    {
        return EOF;
    }

    size_t length_of_string = strlen(string);

    for (size_t i = 0; i < length_of_string; i++)
    {
        fputc((int) string[i], filestream);
    }

    return 1;
}

char* my_strstr( const char* string1, const char* string2 ) 
{
    if (string1 == NULL || string2 == NULL)
    {
        return NULL;
    }

    for (const char* s1 = string1; *s1 != '\0'; s1++)
    {
        const char* s1_ptr = s1;
        const char* s2_ptr = string2;

        while (*s1_ptr != '\0' && *s2_ptr != '\0' && *s1_ptr == *s2_ptr) 
        {
            s1_ptr +=1;
            s2_ptr +=1;
        }

        if (*s2_ptr == '\0') 
        {
            return (char*) s1;
        }
    }

    return NULL;
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

void* my_memmove( void * destination, const void * source, size_t n )
{
    if (destination == NULL || source == NULL || n == 0 || destination == source)
    {
        return NULL;
    }
    if ((char*) destination <= (char*) source + n)
    {
        size_t cursor = n;
        uint64_t* destination_1 = (uint64_t*) destination;
        uint64_t* source_1 = (uint64_t*) source;

        for (size_t i = n / sizeof(uint64_t); i > 0; i--)
        {
            destination_1[i] = source_1[i];
            cursor = i;
        }
        n = n - n % sizeof(uint64_t);

        if (n >= 4)
        {
            uint32_t* destination_2 = (uint32_t*) destination;
            uint32_t* source_2 = (uint32_t*) source;
            destination_2[cursor / 2 - 1] = source_2[cursor / 2 - 1];
            cursor = cursor / 2 - 1;
        }
        n = n - n % sizeof(uint32_t);

        if (n >= 2)
        {
            uint16_t* destination_3 = (uint16_t*) destination;
            uint16_t* source_3 = (uint16_t*) source;
            destination_3[cursor / 2 - 1] = source_3[cursor / 2 - 1];
            cursor = cursor / 2 - 1;
        }
        n = n - n % sizeof(uint16_t);

        if(n >= 1)
        {
            uint8_t* destination_4 = (uint8_t*) destination;
            uint8_t* source_4 = (uint8_t*) source;
            destination_4[cursor / 2 - 1] = source_4[cursor / 2 - 1];     
        }

        return (void*) destination;
    }

    else
    {
        my_memcpy(destination, source, n);
    }

    return (void*) destination;
}

ssize_t my_getline( char** lineptr, size_t* n, FILE* stream)
{
    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        return -1;
    }

    size_t new_size_buffer = 16;
    size_t append_to_buffer = 16;

    char* buffer = *lineptr;
    size_t len_buffer = *n;
    size_t get_len = 0;

    if (n == 0 || *lineptr == NULL)
    {
        char* new_buffer = (char*) calloc(new_size_buffer, sizeof(char));
        buffer = new_buffer;
        len_buffer = new_size_buffer;
    }

    int c = 0;
    while ((c = getc(stream)) != EOF)
    {
        if (get_len + 1 > len_buffer)
        {
            new_size_buffer = len_buffer + append_to_buffer;
            char* buffer_2 = (char*) realloc(buffer, new_size_buffer);
            if (buffer_2 == NULL)
            {
                return -1;
            }
            buffer = buffer_2;
        }

        buffer[get_len] = (char) c;
        get_len += 1;

        if (c == '\n')
        {
            buffer[get_len] = '\n';
            break;
        }
    }

    return get_len;
}

int main()
{
    FILE* file_musor = fopen("huymusor.txt", "r");

    char string3[ MY_MAX_LEN ] = "Hello World";
    char string4[ MY_MAX_LEN ] = "bebebbebebe";
    char string6_buffer[ MY_MAX_LEN ] = "Hello World, beatiful";
    char* string6 = string6_buffer;
    char string7[ MY_MAX_LEN ] = {};
    char* string8 = string6_buffer;
    char string9 [ MY_MAX_LEN ];
    const void* string10 = "Hello";
    char string11 [ MY_MAX_LEN ];
    const void* string12 = "Hello MIIr";
    char symbol = 'o';
    size_t num = 5;
    char* buffer[MY_MAX_LEN] = {};
    size_t MY_MAX_LEN_SIZE_T = 100;

    printf("result of strlen: %lld\n", my_strlen(string1));
    printf("result of strchr: %p\n", my_strchr(string1, symbol));
    printf("result of strcmp: %d\n", my_strcmp(string1, string2));
    printf("result of strncmp: %d\n", my_strncmp(string1, string2, num));
    printf("result of strcat: %p\n", my_strcat(string3, string2));
    printf("result of strncat: %p\n", my_strncat(string3, string2, num));
    printf("result of strcpy: %p\n", my_strcpy(string4, string2));
    printf("result of strncpy: %p\n", my_strncpy(string4, string2, num));
    printf("result of strdup: %p\n", my_strdup(string1));
    printf("result of strndup: %p\n", my_strndup(string1, num));
    printf("result of strsep: %p\n", my_strsep(&string6, delim));
    my_puts(string1);
    printf("result of fseek: %d\n", my_fseek(file_musor, offset_adress, SEEK_SET));
    printf("result of fgets: %p\n", my_fgets(string7, MY_MAX_LEN, file_musor));
    printf("result of fputs: %d\n", my_fputs(string1, file_musor));
    printf("result of strstr: %p\n", my_strstr(string5, string1));
    printf("result of getline: %d\n", my_getline(buffer, &MY_MAX_LEN_SIZE_T, file_musor));

    fclose(file_musor);
    my_strrev(string8);
    my_memcpy(string9, string10, MY_MAX_LEN);
    my_memmove(string11, string12, MY_MAX_LEN);
    printf("result of strrev: %s\n", string8);
    
    
}