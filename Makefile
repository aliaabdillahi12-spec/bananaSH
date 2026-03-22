all: shell
CC=gcc
CFLAGS=
shell: shell.c
  $(CC) shell.c -o shell
