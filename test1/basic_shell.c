#include "main.h"



int main(int c,char **argv, char **env) {
    (void)c;
    char *command = NULL;
    size_t n_char = 0;
    char *arg[] = {NULL, NULL};
    int status;

    while (1 && getline(&command, &n_char, stdin) != EOF) {
        printf("#shell27$ ");
        
    int i =0;
    while (command[i])
    {
    	if (command[i] =='\n')
		command[i] = 0;
	i++;
    }

    arg[0] = strdup(command);    
    pid_t child_pid = fork();
if (child_pid < 0) {
  perror("fork");
  exit(EXIT_FAILURE);
}

if (child_pid == 0) {
  /* This code runs in the child process */
  if (execve(arg[0], arg, env) == -1) {
    printf("\n./shell: No such file or directory\n");
    exit(EXIT_FAILURE);
  }
	
        } else {
            /* This code runs in the parent process */
          
            wait(&status);
    
   	}}
     free(command);
     exit(EXIT_SUCCESS);
     return (0);
    }

