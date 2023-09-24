#include "common.h"

void swap(void *a, void *b, size_t size) {
	
    MY_ASSERT(a, "Variable number one is null pointer");
    MY_ASSERT(b, "Variable number two is null pointer");
    MY_ASSERT(size, "variable size is zero");
    
    void *temp = calloc(size, sizeof(char));

    MY_ASSERT(temp, "Error when allocating memory for a temporary variable");

	memmove(temp, a, size);
	memmove(a, b, size);
	memmove(b, temp, size);

	free(temp);
}