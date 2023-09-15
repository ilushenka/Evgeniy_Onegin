#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>// сделать функцию, которая ищет символ, а также сделать функцию, которая меняет \n на \0 отдельно от первой.

FILE * file_init(int argc, char *argv[]);
size_t file_size(FILE * poem);
void buff_read(char *buff, size_t *poem_size, FILE *poem);

void set_array_lines(char **poem_lines, char *buff, size_t poem_size);

size_t count_lines_num(char *buff, size_t poem_size);

void free_mem_and_file(char **poem_lines, char *buff, FILE *poem);

typedef struct {
	size_t poem_size = 0;
	size_t n_lines = 0;
	char *buff = NULL;
	char **poem_lines = NULL;
}Text;

int main(int argc, char *argv[]) {
	Text poem;
	file_read_and_close(argc, argv, &poem);	
	put_text_in_lines(&poem);
		
	for(size_t i = 0; i < n_lines; i++)
		printf("%s\n", poem_lines[i]);

	free_mem_and_file(poem_lines, buff, poem);
}

FILE * file_read(int argc, char *argv[]) {
	if(argc != 2) {
		printf("wrong program run, error with passed arguments. Try to open this program like that: ./example.out text.txt");
		exit(0);
	}
	FILE * text_source;
	if((text_source = fopen(argv[1], "r")) == NULL) {
		printf("Unable to open file with this name.");
		exit(0);
	}
	return text_source
}

void work_with_file(int argc, char *argv[], Text *poem) {
	FILE *fp = file_init(argc, argv);
	
	poem->poem_size = file_size(fp);
	poem->buff = (char *)calloc(poem->poem_size + 1, sizeof(char));

	buff_read(poem->buff, &poem->poem_size, fp);

	fclose(fp);
}

void put_text_in_lines(Text *poem) {
	poem->n_lines = count_lines_num(poem->buff, poem->poem_size);
	poem->poem_lines = (char**) calloc(poem->n_lines, sizeof(char*));
	
	set_array_lines(poem->poem_lines, poem->buff, poem->poem_size);
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
	
	return n_lines;
}

void free_mem_and_file(char **poem_lines, char *buff, FILE *poem) {
	free(buff);
	free(poem_lines);
	fclose(poem);
}