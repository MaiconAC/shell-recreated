#include "../headers/termios_config.h"
#include <termios.h>

static struct termios old, current;

void init_termios() {
	// get old i/o settings
	tcgetattr(0, &old);
	current = old;

	// disable buffered i/o
	current.c_lflag &= ~ICANON;

	// disable echo mode
	current.c_lflag &= ~ECHO;

	// set new configuration
	tcsetattr(0, TCSANOW, &current);
}

void reset_termios() {
	// return original config
	tcsetattr(0, TCSANOW, &old);
}					
