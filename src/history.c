#include "../headers/history.h"
#include "../headers/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **history;
int history_length = 0;
int history_max_length = HISTORY_BUFFER_SIZE;
int history_offset = 0;

void add_to_history(char *command) {
	if (history_length == 0) {
		history = malloc(sizeof(char *) * HISTORY_BUFFER_SIZE);	

		if (!history) {
			buffer_allocation_error();
		}

	} else if (history_length == history_max_length) {
		history_max_length += HISTORY_BUFFER_SIZE;
		history = realloc(history, sizeof(char *) * history_max_length);

		if (!history) {
			buffer_allocation_error();
		}
	}

	// adds the new command to history, sets offset to last command 
	// and increase size
	// strdup duplicates line, necesasary because when dividing in tokens,
	// the original line string gets divided 
	history[history_length] = strdup(command);

	if (!history[history_length]) {
		buffer_allocation_error();
	}

	history_offset = history_length; 
	history_length++;
}

void print_history() {
	for (int i = 0; i < history_length; i++) {
		printf("[%d] %s\n", i, history[i]);
	}
}

void free_history_buffer() {
	for (int i = 0; i < history_length; i++) {
		free(history[i]);
	}
	
	free(history);
}

void decrease_offset();
void increase_offset();

