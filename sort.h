#pragma once

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(void *data, size_t left, size_t right,
	  int (*comparator)(const void *, const void *), size_t type_size);
