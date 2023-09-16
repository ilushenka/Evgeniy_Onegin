#include "work_with_text.h"

int main(int argc, char *argv[]) {
	Text poem;
	work_with_file(argc, argv, &poem);	
	put_text_in_lines(&poem);

	sort(poem.poem_lines, 0, poem.n_lines - 1, comparator, sizeof(char**));	
	for(size_t i = 0; i < poem.n_lines; i++)
		printf("%s\n", poem.poem_lines[i]);

	destroy_structure(&poem);
}

FILE * file_init(int argc, char *argv[]) {
	if(argc != 2) {
		printf("wrong program run, error with passed arguments. \nTry to open this program like that: ./example.out text.txt\n");
		exit(0);
	}
	FILE * text_source;
	if((text_source = fopen(argv[1], "r")) == NULL) {
		printf("Unable to open file with this name.");
		exit(0);
	}
	return text_source;
}

void work_with_file(int argc, char *argv[], Text *poem) {
	FILE *fp = file_init(argc, argv);
	
	poem->poem_size = file_size(fp);
	poem->buff = (char *)calloc(poem->poem_size + 1, sizeof(char));

	buff_read(poem, fp);

	fclose(fp);
}

size_t file_size(FILE *fp) {
	fseek(fp, 0, SEEK_END);
	size_t poem_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	return poem_size;
}

void buff_read(Text *poem, FILE * fp) {
	fread(poem->buff, sizeof(char), poem->poem_size, fp);
	poem->buff[poem->poem_size] = '\n';
	(poem->poem_size)++;
}

void put_text_in_lines(Text *poem) {
	count_lines_num(poem);
	poem->poem_lines = (char**) calloc(poem->n_lines, sizeof(char*));
	
	set_array_lines(poem);
}

void set_array_lines(Text *poem) {
	poem->poem_lines[0] = poem->buff;
	for(size_t i = 0, line = 1; i + 1 < poem->poem_size; i++) {
		if(poem->buff[i] == '\0')
			poem->poem_lines[line++] = poem->buff + i + 1;
	}
}

void count_lines_num(Text *poem) {
	for(size_t i = 0; i < poem->poem_size; i++) {
		if(poem->buff[i] == '\n') {
			poem->buff[i] = '\0';
			poem->n_lines++;
		}
	}
}

void destroy_structure(Text *poem) {
	free_mem(poem->poem_lines, poem->buff);
	poem->poem_size = -1;
	poem->n_lines = -1;
	poem->poem_lines = NULL;
	poem->buff = NULL;
}

void free_mem(char **poem_lines, char *buff) {
	free(buff);
	free(poem_lines);
}

int comparator(const void *a, const void *b) {
	return strcmp(*(const char **)a,*(const char **)b);
}