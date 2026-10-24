#include "../headers/shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// The program loop needs to:
// 1) Read input
// 2) Parse program name + arguments
// 3) Run the command
void execution_loop()
{
	char *line;
	char **args;
	int status;

	do {
		printf("> ");
		line = read_line();
		args = parse_line(line);
		status = execute_program(args);

		free(line);
		free(args);
	} while (status);
}

// We dont know the size of the input, so we allocate
// a buffer with fixed size and if the input is bigger,
// increase buffer size
//
// newer C versions can use getline() command
char *read_line()
{
	int buffer_size = STDIN_BUFFER_SIZE;
	char *buffer = malloc(sizeof(char) * buffer_size);
	int index = 0, character;

	if (!buffer) {
		buffer_allocation_error();
	}

	while (1) {
		// The character is stored as an int to include EOF value
		character = getchar();

		// If user hit enter, put a null character and return the line
		// else add character to buffer and increase size counter;
		if (character == EOF || character == '\n') {
			buffer[index] = '\0';
			return buffer;
		} else {
			buffer[index] = character;
			index++;
		}

		// Check if needs to reallocate buffer
		if (index >= buffer_size) {
			buffer_size += STDIN_BUFFER_SIZE;
			buffer = realloc(buffer, buffer_size);

			if (!buffer) {
				buffer_allocation_error();
			}
		}	
	}
}

// The line is parsed using spaces as delimeters, breaking the line
// into tokens, each token is basically a word or command
char **parse_line(char *line)
{
	// TODO allow quoting and backslash on commands
	int buffer_size = STRTOK_TOKEN_BUFFER_SIZE;
	int index = 0;
	char **tokens = malloc(sizeof(char *) * buffer_size);
	char *token;

	if (!tokens) {
		buffer_allocation_error();
	}

	// strtok divide the string (line) into tokens by delimeters
	// put \0 on the end of the token and returns a pointer to it
	token = strtok(line, STRTOK_DELIMETERS);

	while (token != NULL) {
		tokens[index] = token;
		index++;

		if (index >= buffer_size) {
			buffer_size += STRTOK_TOKEN_BUFFER_SIZE;
			tokens = realloc(tokens, sizeof(char *) * buffer_size);

			if (!tokens) {
				buffer_allocation_error();
			}
		}

		// each subsequent call that use the same string
		// should use NULL, ref man strtok
		token = strtok(NULL, STRTOK_DELIMETERS);
	}

	// last position NULL
	tokens[index] = NULL;
	return tokens;
}

// to init a program it is necessary to create a new process with
// the fork syscall, it returns 2 times, one for the child and one for
// the parent becuse it duplicates the context, so both processes will
// continue from this point, that's why it is used only one if-else
int execute_program(char **args) {
	// empty command
	if (args[0] == NULL) return 1;

	pid_t pid;
	int status;

	pid = fork();

	// child process
	if (pid == 0) {
		int response = execvp(args[0], args);

		if (response == -1) {
			perror("shell-recreated");
		}

		exit_child_process();
	
	// error forking
	} else if (pid < 0) {
		perror("shell-recreated");

	// parent process
	} else {
		// put parent process in wait until it exits normally (WIFEXITED) or
		// it was killed WIFSIGNALED
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

void buffer_allocation_error()
{
	fprintf(stderr, "Buffer allocation error");
	exit(EXIT_FAILURE);
}

void exit_child_process()
{
	exit(EXIT_FAILURE);
}
