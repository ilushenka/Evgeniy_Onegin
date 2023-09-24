#include "work_with_text.h"

int main(int argc, char *argv[]) {
	Text poem = {};
	Text_read_from_file(argc, argv, &poem);	
	put_text_in_lines(&poem);
	
	MY_ASSERT((argc == 3), "Wrong program usage, error with passed arguments.\n"
	"Try to open this program like that: ./example.out text.txt dest.txt"
	"(the first is where we read from, the second is where we write to).\n");
	
	FILE * sorted_file = fopen(argv[2], "w+");

	sort_and_write(sorted_file, &poem, 0,
				(poem.n_lines - 1), left_compare, sizeof(char**));
	sort_and_write(sorted_file, &poem, 0,
				(poem.n_lines - 1), right_compare, sizeof(char**));

	write_buff(sorted_file, &poem.buff);

	fclose(sorted_file);
	
	text_destructor(&poem);
}

int left_compare(const void *a, const void *b) {
	const char *str1 = *(const char **)a;
	const char *str2 = *(const char **)b;
	str1 = skip_left_pointer(str1);
	str2 = skip_left_pointer(str2);

	while(*str1 && *str2) {
		str1 = skip_left_pointer(str1);
		str2 = skip_left_pointer(str2);
		char let1 = toupper(*str1);
		char let2 = toupper(*str2);

		if(*str1 && *str2 && let1 != let2)
			return let1-let2;

		if(*str1 && *str2) {
			str1++;
			str2++;
		}
	}
	return *str1 - *str2;
}

const char *skip_left_pointer(const char *str) {
	while(*str && !(isalnum(*str)))
		str++;
	
	return str;
}

const char *skip_right_pointer(const char *str, int *index) {
	while((*index) != 0 && !(isalnum(*str))) {
		str--;
		(*index)--;
	}
	return str;
}

int right_compare(const void *a, const void *b) {
	const char *str1 = *(const char **)a;
	const char *str2 = *(const char **)b;

	int x_index = strlen(str1) - 1;
	int y_index = strlen(str2) - 1;
	if(x_index)
		str1 = str1 + x_index;
	if(y_index)
		str2 = str2 + y_index;


	str1 = skip_right_pointer(str1, &x_index);
	str2 = skip_right_pointer(str2, &y_index);
	while(x_index && y_index) {
		str1 = skip_right_pointer(str1, &x_index);
		str2 = skip_right_pointer(str2, &y_index);

		char let1 = toupper(*str1);
		char let2 = toupper(*str2);
		
		if(x_index && y_index && let1 != let2)
			return let1-let2;
		
		if(x_index && y_index) {
			x_index--;
			y_index--;
			str1--;
			str2--;
		}
	}
	return x_index - y_index;
}
