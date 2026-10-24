#include "headers/shell.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	// TODO load config files
	
	printf("Shell started!\n");

	execution_loop();
	return 0;
}

