#ifndef ALL_FOR_SORT_H
#define ALL_FOR_SORT_H

#include <stdio.h>
#include <cstdint>
#include <fcntl.h>


int compare_for_beginning_strings(const void* a, const void* b);
int compare_for_end_strings(const void* a, const void* b);
int compare_for_indexes(const void* a, const void* b);
void quick_sort(void* array, size_t len_array, size_t size_element, int (*compare)(const void* a, const void* b));
void swap(void* a, void* b, size_t size_element);

#endif