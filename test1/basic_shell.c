#include "main.h"



int main(char **argv, char **env) {
    char *command;
    size_t n_char = 0;
    char *arg[] = {NULL, NULL};
    while (getline(&command, &n_char, stdin) != EOF) {
        printf("#shell27$ ");
        }
    if (n_char == - 1)
	{
exit(EXIT_SUCCESS);
	}
    int i =0;
    while (command[i])
    {
    	if (command[i] =='\n')
		command[i] = 0;
	i++;
    }

        pid_t child_pid = fork();
if (child_pid == -1) {
  perror("fork");
  exit(EXIT_FAILURE);
}

if (child_pid == 0) {
  /* This code runs in the child process */
  if (execve(arg[0], command, env) == -1) {
    perror("Command is not alive");
    exit(EXIT_FAILURE);
  }

        } else {
            /* This code runs in the parent process */
            int status;
            wait(&status);
    
   	}
     free(command);
     return (0);
    }

