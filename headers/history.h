#define HISTORY_BUFFER_SIZE 10

void add_to_history(char *command);
void decrease_offset();
void increase_offset();
void print_history();
void free_history_buffer();
