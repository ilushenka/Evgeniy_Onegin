#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MY_ASSERT(cond, msg) \
	do {					\
	    if (!cond)			\
		{					\
			printf(msg);	\
			printf("FILE: %s\n", __FILE__); \
			printf("FUNCTION: %s\n", __PRETTY_FUNCTION__); \
			printf("LINE: %d\n", __LINE__); \
			exit(0);		\
		}					\
	} while (0)

void swap(void *a, void *b, size_t size);