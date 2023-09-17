#pragma once

#include <ctype.h>
#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	size_t poem_size = 0;
	size_t n_lines = 0;
	char *buff = NULL;
	char **poem_lines = NULL;
}Text;

int left_compare(const void *a, const void *b);
int right_compare(const void *a, const void *b);
const char * move_left_pointer(const char *str);
const char * move_right_pointer(const char *str);


FILE * file_init(int argc, char *argv[]);
void work_with_file(int argc, char *argv[], Text *poem);
size_t file_size(FILE *poem);

void buff_read(Text *poem, FILE *fp);

void put_text_in_lines(Text *poem);
void set_array_lines(Text *poem);
void count_lines_num(Text *poem);

void destroy_structure(Text *poem);
void free_mem(char **poem_lines, char *buff);