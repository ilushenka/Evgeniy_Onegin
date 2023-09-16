#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t partition(void **data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size);

void sort(void *data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size);
void sort_two(void **data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size);

void swap(void *a, void *b, size_t size);

void print_array(void *data, size_t left, size_t right, size_t mid);