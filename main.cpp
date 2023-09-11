#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

FILE * file_init();
size_t file_size(FILE * poem);
void buff_read(char *buff, size_t *poem_size, FILE *poem);

void set_array_lines(char **poem_lines, char *buff, size_t poem_size);

size_t count_lines_num(char *buff, size_t poem_size);

void free_mem_and_file(char **poem_lines, char *buff, FILE *poem);

int main() {
	
	FILE *poem = file_init();
	size_t poem_size = file_size(poem);
	
	char *buff = (char *)calloc(poem_size + 1, sizeof(char));
	
	buff_read(buff, &poem_size, poem);
	
	size_t n_lines = count_lines_num(buff, poem_size);
	char **poem_lines = (char**) calloc(n_lines, sizeof(char*));
	
	set_array_lines(poem_lines, buff, poem_size);

	free_mem_and_file(poem_lines, buff, poem);
	
	for(size_t i = 0; i < n_lines; i++)
		printf("%s\n", poem_lines[i]);
}

FILE * file_init() {
	FILE * text_source;
	if((text_source = fopen("poem.txt", "r")) == NULL) {
		printf("Unable to open file\n");
		exit(0);
	}

	return text_source;
}

size_t file_size(FILE *poem) {
	fseek(poem, 0, SEEK_END);
	size_t poem_size = ftell(poem);
	fseek(poem, 0, SEEK_SET);
	
	return poem_size;
}

void buff_read(char *buff, size_t *poem_size, FILE *poem) {
	fread(buff, sizeof(char), *poem_size, poem);
	
	buff[*poem_size] = '\n';
	(*poem_size)++;
}

void set_array_lines(char **poem_lines, char *buff, size_t poem_size) {
	poem_lines[0] = buff;
	for(size_t i = 0, line = 1; i + 1 < poem_size; i++) {
		if(buff[i] == '\0')
			poem_lines[line++] = buff + i + 1;
	}
}

size_t count_lines_num(char *buff, size_t poem_size) {
	size_t n_lines = 0;
	for(size_t i = 0; i < poem_size; i++) {
		if(buff[i] == '\n') {
			*(buff + i) = '\0';
			n_lines++;
		}
	}
	printf("\n%ld", n_lines);
	
	return n_lines;
}

void free_mem_and_file(char **poem_lines, char *buff, FILE *poem) {
	free(buff);
	free(poem_lines);
	fclose(poem);
}