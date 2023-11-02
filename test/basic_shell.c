#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 1000

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#shell22$ ");
        fflush(stdout);

	if (fgets(command, sizeof(command), stdin) == NULL) {
	    if (feof(stdin)) {
	   	 /* Reached end-ofofile (Ctrl+D)*/
	   	break;
	    } else {
		/* Error while reading */
		perror("fgets");
		exit(EXIT_FAILURE);
	    }
	}	    

        if (fgets(command, sizeof(command), stdin) == NULL) {
		printf("Exitting_shell22 \n");
            continue;
        }

        /* Remove the trailing newline character */
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        pid_t child_pid = fork();
if (child_pid == -1) {
  perror("fork");
  exit(EXIT_FAILURE);
}

if (child_pid == 0) {
  /* This code runs in the child process */
  if (execlp(command, command, NULL) == -1) {
    perror("execlp");
    exit(EXIT_FAILURE);
  }

        } else {
            /* This code runs in the parent process */
            int status;
            wait(&status);
        }
    }

    return 0;
}
