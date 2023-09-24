#include "work_with_text.h"

static FILE *file_init(int argc, char *argv[]);
static size_t get_file_size(FILE *fp);

static void buff_read(Buffer *buff, FILE *fp);
static void set_array_lines(Text *poem);
static void count_lines_num(Text *poem);

static void write_in_file(FILE * sorted_file, Text *poem);

static FILE *file_init(int argc, char *argv[]) {
	MY_ASSERT((argc == 3), "Wrong program usage, error with passed arguments.\n"
	"Try to open this program like that: ./example.out text.txt dest.txt"
	"(the first is where we read from, the second is where we write to).\n");
	
	FILE *text_source = fopen(argv[1], "r");
	
	MY_ASSERT((text_source != NULL), "Unable to open file with this name.\n");
	return text_source;
}

void Text_read_from_file(int argc, char *argv[], Text *poem) {
	MY_ASSERT((argc == 3), "Wrong program usage, error with passed arguments.\n"
	"Try to open this program like that: ./example.out text.txt dest.txt"
	"(the first is where we read from, the second is where we write to).\n");

	FILE *fp = file_init(argc, argv);
	
	poem->buff.size = get_file_size(fp);
	poem->buff.data = (char *)calloc(poem->buff.size + 1, sizeof(char));

	MY_ASSERT(poem->buff.data, "Buffer memory allocation error");

	buff_read(&poem->buff, fp);

	MY_ASSERT(!(fclose(fp)), "Can't close the file");
}

static size_t get_file_size(FILE *fp) {
	MY_ASSERT(fp, "File has not been opened");

	fseek(fp, 0, SEEK_END);
	size_t poem_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	return poem_size;
}

static void buff_read(Buffer *buff, FILE *fp) {
	MY_ASSERT(fp, "File has not been opened");
	MY_ASSERT(buff->data, "Buffer memory allocation error");
	MY_ASSERT(buff->size, "File is empty");

	fread(buff->data, sizeof(char), buff->size, fp);
	buff->data[buff->size] = '\n';
	(buff->size)++;
}

void put_text_in_lines(Text *poem) {
	MY_ASSERT(poem->buff.size, "File is empty");
	MY_ASSERT(poem->buff.data, "Buffer memory allocation error");
	
	count_lines_num(poem);
	poem->poem_lines = (char**) calloc(poem->n_lines, sizeof(char*));

	MY_ASSERT(poem->poem_lines, "Poem lines memory allocation error");

	set_array_lines(poem);
}

static void set_array_lines(Text *poem) {
	MY_ASSERT(poem->buff.size, "File is empty");
	MY_ASSERT(poem->buff.data, "Buffer memory allocation error");
	MY_ASSERT(poem->poem_lines, "Poem lines memory allocation error");

	poem->poem_lines[0] = poem->buff.data;
	for(int i = 0, line = 1; i < poem->buff.size - 1; i++) {
		if(poem->buff.data[i] == '\0')
			poem->poem_lines[line++] = poem->buff.data + i + 1;
	}
}

static void count_lines_num(Text *poem) {
	MY_ASSERT(poem->buff.size, "File is empty");
	MY_ASSERT(poem->buff.data, "Buffer memory allocation error");

	for(size_t i = 0; i < poem->buff.size; i++) {
		if(poem->buff.data[i] == '\n') {
			poem->buff.data[i] = '\0';
			poem->n_lines++;
		}
	}
}

void sort_and_write(FILE *sorted_file, Text *poem, size_t left, size_t right,
	  int (*comparator)(const void *, const void *), size_t type_size) {
	MY_ASSERT(poem, "The passed structure is a null pointer");
	MY_ASSERT(poem->poem_lines, "The passed structure with poem lines is a null pointer");
	MY_ASSERT(poem->buff.data, "The passed structure with buffer is a null pointer");
	MY_ASSERT((right >= left), "The passed variable data is a null pointer");
	MY_ASSERT(type_size, "The transferred type size is zero");
	MY_ASSERT(comparator, "The transferred function is null pointer");
	MY_ASSERT(sorted_file, "File has not been opened");

	sort(poem->poem_lines, left, right, comparator, type_size);
	write_in_file(sorted_file, poem);
}

static void write_in_file(FILE *sorted_file, Text *poem) {
	MY_ASSERT(sorted_file, "File has not been opened");
	MY_ASSERT(poem, "The passed structure is a null pointer");
	MY_ASSERT(poem->poem_lines, "The passed structure with poem lines is a null pointer");

	for(int i = 0; i < poem->n_lines; i++) {
		fputs(poem->poem_lines[i], sorted_file);
		fputc('\n', sorted_file);
	}
	fputs("\n-------------------------------------------------------\n", sorted_file);
}

void write_buff(FILE *sorted_file, Buffer *buff) {
	MY_ASSERT(sorted_file, "File has not been opened");
	MY_ASSERT(buff_size, "Buff size is a null");
	MY_ASSERT(buff->data, "buff is an empty(has a null pointer)");

	for(size_t i = 0; i < buff->size; i += fprintf(sorted_file, "%s\n", buff->data + i));
	fputs("\n-------------------------------------------------------\n", sorted_file);
}

void print_poem(Text *poem) {
	MY_ASSERT(poem->poem_lines, "Poem lines memory allocation error");
	
	for(size_t i = 0; i < poem->n_lines; i++)
		printf("%s\n", poem->poem_lines[i]);
}

void text_destructor(Text *poem) {
	free(poem->poem_lines);
	free(poem->buff.data);
	poem->buff.size = -1;
	poem->n_lines = -1;
	poem->poem_lines = NULL;
	poem->buff.data = NULL;
}