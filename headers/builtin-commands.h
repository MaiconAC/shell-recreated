// function pointer to create a dispatch table
typedef int (*builtin_command) (char **);

int cd_command(char **args);
int exit_command(char **args);
int builtin_commands_size();
int check_builtin_commands(char **args);
