#include "../headers/builtin-commands.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *builtin_commands_strings[2] = {
	"cd",
	"exit"
};

builtin_command builtin_commands[] = {
	&cd_command,
	&exit_command,
};

// calculate the number of builtin commands available
int builtin_commands_size() {
	return sizeof(builtin_commands_strings) / sizeof(char *);
}

// cd is a builtin shell function, it uses chdir() function to change the
// process directory
int cd_command(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "shell: expected arguments to cd\n");
	}

	int response = chdir(args[1]);

	if (response != 0) {
		perror("shell");
	}

	return 1;
}

// if returns 0 the program loop finishes
int exit_command(char **args) {
	return 0;
}

// uses a dispatch table to run the correct function
int check_builtin_commands(char **args) {
	for (int i = 0; i < builtin_commands_size(); i++) {
		if (strcmp(args[0], builtin_commands_strings[i]) == 0) {
			return builtin_commands[i] (args);
		}
	}

	return -1;
}
