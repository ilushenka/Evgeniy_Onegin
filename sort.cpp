#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_PURPLE   "\x1b[38;5;140m"
#define ANSI_COLOR_LBLUE   "\x1b[38;5;20m"
#define ANSI_COLOR_YELLOW   "\x1b[38;5;221m"
#define ANSI_COLOR_TURQUOISE  "\x1b[38;5;87m"
#define ANSI_COLOR_ORANGE   "\x1b[38;5;209m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SIZE 28
 

size_t partition(int *data, size_t left, size_t right);

void sort(int *data, size_t left, size_t right);
void sort_two(int *data, size_t left, size_t right);

void swap(int *a, int *b);

void print_array(int *data, size_t left, size_t right, size_t mid);
//void debug(int *data, size_t left, size_t right, size_t mid);

int main() {
	int data[] = 	{
					58, 25, 46, 70, 72, 75, 2, 76, 60, 51, 54, 41, 64, 67, 58, 25, 46, 70, 72, 75, 2, 76, 60, 51, 54, 41, 64, 67};
	for(size_t i = 0; i < SIZE; i++)
		printf("%d ", data[i]);
	printf("\n");

	sort(data, 0, SIZE - 1);
	for(size_t i = 0; i < SIZE; i++)
		printf("%d ", data[i]);
	printf("\n");
}

void sort(int *data, size_t left, size_t right) {
	if(right == left + 1) {
		printf("QSWAP %d WITH %d, LEFT %ld RIGHT %ld\n", data[left], data[right], left, right);		
		sort_two(data, left, right);
		return;
	}
	if(right == left)
		return;
	
	size_t mid = partition(data, left, right);

	if(mid > left)
		sort(data, left, mid);
	if(mid+1 < right)
		sort(data, (mid + 1), right);
}

void sort_two(int *data, size_t left, size_t right) {
	if(data[left] > data[right])
		swap(data + left, data + right);
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(int *data, size_t left, size_t right, size_t mid) {
	for(size_t i = 0; i < SIZE; i++) {
		if(i == mid)
			printf(ANSI_COLOR_GREEN"%2d ", data[i]);
		else if(i < left)
			printf(ANSI_COLOR_TURQUOISE"%2d ", data[i]);
		else if(i == left)
			printf(ANSI_COLOR_LBLUE"%2d ", data[i]);
		else if(i == right)
			printf(ANSI_COLOR_RED"%2d ", data[i]);
		else if(i > left && i < mid)
			printf(ANSI_COLOR_PURPLE"%2d ", data[i]);
		else if(i < right && i > mid)
			printf(ANSI_COLOR_ORANGE"%2d ", data[i]);
		else if(i > right)
			printf(ANSI_COLOR_YELLOW"%2d ", data[i]);
	}
	printf("\n" ANSI_COLOR_RESET);
}

size_t partition(int *data, size_t left, size_t right) {
	size_t mid = (left + right)/2;
	int mid_elem = data[mid];
	print_array(data, left, right, mid);
	while(true) {
		while(data[left] < mid_elem)
			left++;
		while(data[right] > mid_elem)
			right--;
		print_array(data, left, right, mid);
		if(left >= right)
			return right;
		swap(data + left, data + right);
		printf("SWAP %d WITH %d, LEFT %ld RIGHT %ld, MID %ld\n", data[left], data[right], left, right, mid);
		left++;
		right--;
		print_array(data, left, right, mid);
	}
	printf("Закончен цикл\n");
}

/*void debug(int *data, size_t left, size_t right, size_t mid) {
	printf("----------------------\n");
	print_array(data);
	printf("data[left] %d, data[right] %d, data[mid] %d, left %ld, right %ld, mid %ld \n", data[left], data[right], data[mid], left, right, mid);
	printf("----------------------\n");
}*/