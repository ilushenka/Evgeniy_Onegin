#include "sort.h"

static void sort_process(void *data, size_t left, size_t right,
	int (*comparator)(const void *, const void *), size_t type_size);

static void sort_routine(void *data, size_t left, size_t right,
		     int (*comparator)(const void *, const void *),
		     size_t type_size);

static size_t partition(void *data, size_t left, size_t right,
			int (*comparator)(const void *, const void *),
			size_t type_size);

#define DATA_ELEM(data, position, type_size) ((char *)data + type_size * position)

void sort(void *data, size_t left, size_t right,
	int (*comparator)(const void *, const void *), size_t type_size) {
	MY_ASSERT(data, "The passed variable data is a null pointer");
	MY_ASSERT((right >= left), "The passed variable data is a null pointer");
	MY_ASSERT(type_size, "The transferred type size is zero");
	MY_ASSERT(comparator, "The transferred function is null pointer");
	
	sort_process(data, left, right, comparator, type_size);
	}

static void sort_process(void *data, size_t left, size_t right,
	int (*comparator)(const void *, const void *), size_t type_size) {
	
	if(right == left + 1) {
		sort_routine(data, left, right, comparator, type_size);
		return;
	}
	if(right == left)
		return;
	
	size_t mid = partition(data, left, right, comparator, type_size);

	if(mid > left)
		sort_process(data, left, mid, comparator, type_size);
	if(mid + 1 < right)
		sort_process(data, (mid + 1), right, comparator, type_size);
}

static void sort_routine(void *data, size_t left, size_t right,
			int (*comparator)(const void *, const void *), size_t type_size) {
	if(comparator(DATA_ELEM(data, right, type_size),
				DATA_ELEM(data, left, type_size)) < 0)
		swap(DATA_ELEM(data, left, type_size),
			 DATA_ELEM(data, right, type_size), type_size);
}

static size_t partition(void *data, size_t left, size_t right,
			int (*comparator)(const void *, const void *), size_t type_size) {
	size_t mid = (left + right)/2;
	void *mid_elem = (void *)calloc(type_size, sizeof(char));
	memcpy(mid_elem,((char *)data + type_size * mid), type_size);

	while(true) {
		while(comparator(DATA_ELEM(data, left, type_size), mid_elem) < 0)
			left++;
		
		while(comparator(mid_elem, DATA_ELEM(data, right, type_size)) < 0)
			right--;
		
		if(left >= right) {
			free(mid_elem);
			return right;
		}

		swap(DATA_ELEM(data, left, type_size),
			DATA_ELEM(data, right, type_size), type_size);
		left++;
		right--;
	}
}
