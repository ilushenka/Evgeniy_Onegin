#include "sort.h"

void sort(void *data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size) {
	if(right == left + 1) {
		sort_two(data, left, right, comparator, type_size);
		return;
	}
	if(right == left)
		return;
	
	size_t mid = partition(data, left, right, comparator, type_size);

	if(mid > left)
		sort(data, left, mid, comparator, type_size);
	if(mid + 1 < right)
		sort(data, (mid + 1), right, comparator, type_size);
}

void sort_two(void *data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size) {
	if(comparator((char *)data + type_size * right, (char *)data + type_size * left) < 0)
		swap((char *)data + type_size * left, (char *)data + type_size * right, type_size);
}

void swap(void *a, void *b, size_t size) {
	void **temp = (void **)calloc(size, sizeof(char));
	
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);

	free(temp);
}

size_t partition(void *data, size_t left, size_t right, int (*comparator)(const void *, const void *), size_t type_size) {
	size_t mid = (left + right)/2;
	void **mid_elem = (void **)calloc(type_size, sizeof(char));
	memcpy(mid_elem, (char *)data + type_size * mid, type_size);
	
	while(true) {
		while(comparator((char *)data + type_size * left, mid_elem) < 0)
			left++;
		
		while(comparator(mid_elem, (char *)data + type_size * right) < 0)
			right--;
		
		if(left >= right) {
			free(mid_elem);
			
			return right;
		}
		swap(((char *)data + left * type_size), ((char *)data + type_size * right), type_size);
		left++;
		right--;
	}
}