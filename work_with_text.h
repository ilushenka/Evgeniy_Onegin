#pragma once

#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

typedef struct {
	char *data;
	int size;
}Buffer;

typedef struct {
	Buffer buff;
	int n_lines;
	char **poem_lines;
} Text;

int left_compare(const void *a, const void *b);
int right_compare(const void *a, const void *b);
const char *skip_left_pointer(const char *str);
const char *skip_right_pointer(const char *str, int *index);

void Text_read_from_file(int argc, char *argv[], Text *poem);

void put_text_in_lines(Text *poem);

void sort_and_write(FILE *sorted_file, Text *poem, size_t left,
					size_t right, int (*comparator)(const void *, const void *),
					 size_t type_size);
void write_buff(FILE *sorted_file, Buffer *buff);

void print_poem(Text *poem);

void text_destructor(Text *poem);
