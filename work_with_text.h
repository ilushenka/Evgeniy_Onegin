#pragma once

#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>// сделать функцию, которая ищет символ, а также сделать функцию, которая меняет \n на \0 отдельно от первой.

typedef struct {
	size_t poem_size = 0;
	size_t n_lines = 0;
	char *buff = NULL;
	char **poem_lines = NULL;
}Text;

int comparator(const void *a, const void *b);

FILE * file_init(int argc, char *argv[]);
void work_with_file(int argc, char *argv[], Text *poem);
size_t file_size(FILE *poem);

void buff_read(Text *poem, FILE *fp);

void put_text_in_lines(Text *poem);
void set_array_lines(Text *poem);
void count_lines_num(Text *poem);

void destroy_structure(Text *poem);
void free_mem(char **poem_lines, char *buff);