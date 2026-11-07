#define HISTORY_BUFFER_SIZE 10

void add_to_history(char *command);
void decrease_offset(char *buffer, int *buffer_index);
void increase_offset(char *buffer, int *buffer_index);
void print_history();
void free_history_buffer();
