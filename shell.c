#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define INPUTBUFF 1024

void execute_cmd(char *input) {
	int i = 0;
	char *token;
	char arg_vect[16][32];
	char *argvect[32];
	input[strcspn(input, "\n")] = 0;
	if(input[0] == 0) return;
	token = strtok(input, " ");

	if(strcmp(token, "cd") == 0) {
		chdir(strtok(NULL, " "));
		return;
	}
	while(token != NULL && i < 31) {
		argvect[i] = token;
		i++;
		token = strtok(NULL, " ");
	} 
	argvect[i] = NULL;
	
	pid_t pid = fork();

	if(pid == 0) {
		execvp(argvect[0], argvect);
	} else {wait(NULL);}
}

int main() {
	int i = 0, ii = 0;
	char input_cmdline[INPUTBUFF];
	while(1) {
		write(1, ">", 1);
		read(0, input_cmdline, INPUTBUFF);
		execute_cmd(input_cmdline);

	}
	return 0;
}
