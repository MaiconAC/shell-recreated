#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>

void buffer_allocation_error()
{
	fprintf(stderr, "Buffer allocation error");
	exit(EXIT_FAILURE);
}
