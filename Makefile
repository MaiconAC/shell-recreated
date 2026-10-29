CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = -o shell-r.bin main.c headers/* src/*

shell-r.bin:
	$(CC) $(CFLAGS) $(TARGET)
	
clean:
	rm -rf shell-r.bin


