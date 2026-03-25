#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define INPUTBUFF 1024

void interrupt_handler() {return;}
void execute_cmd(char *input) {

	input[strcspn(input, "\n")] = 0;
	if(input[0] == 0) return;
	
	char *argvect[32];
	char *token = strtok(input, " ");

	if(0 == strcmp(token, "cd")) {
		chdir(strtok(NULL, " "));
		return;
	}
	
	int i = 0;
	while(token != NULL && i < 31) {
		argvect[i] = token;
		i++;
		token = strtok(NULL, " ");
	} 
	argvect[i] = NULL;
		
	if(0 == fork()) {
		int result = execvp(argvect[0], argvect);
		if(result == -1) {
			printf("Command not found.\n");
			exit(-1);
		}
	} else {wait(NULL);}
}

int main() {
	/* We will Make sure ctrl-C does not terminate */
	signal(SIGINT, interrupt_handler);

	char input_cmdline[INPUTBUFF];
	while(1) {
		if(0 == getuid()) {
			write(1, "#", 1);
		} else {
			write(1, "$", 1);
		}
		read(0, input_cmdline, INPUTBUFF);
		execute_cmd(input_cmdline);

	}
	return 0;
}
