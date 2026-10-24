#define STDIN_BUFFER_SIZE 1024
#define STRTOK_TOKEN_BUFFER_SIZE 64

// delimeters = space, tab, ret, enter and alert escape
#define STRTOK_DELIMETERS " \t\r\n\a"

void execution_loop();
char *read_line();
char **parse_line(char *line);
int execute_program(char **args);

void buffer_allocation_error();
void exit_child_process();
