all: shell
CC=gcc
CFLAGS=
shell: shell.c
	$(CC) $(CFLAGS) shell.c -o shell
