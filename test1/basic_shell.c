#include "main.h"

int main(int argc, char **argv, char **env) {
    char *command = NULL;
    size_t n_char = 0;
    char *emp[] = {NULL, NULL};
    int status;
    bool oneline = isatty(STDIN_FILENO); 
    pid_t child;

    while (1) {
	if (oneline){
        printf("#shell27$ ");
	}
        if (getline(&command, &n_char, stdin) == EOF){
	      if (oneline) {	
            printf("\n");
	      }
            break;
        }

        int i = 0;
        while (command[i]) {
            if (command[i] == '\n') {
                command[i] = 0;
            }
            i++;
        }

        emp[0] = strdup(command);
        child = fork();
        if (child < 0) {
            printf("fork failed");
        } else if (child == 0) {
            if (execve(emp[0], emp, env) == -1) {
                printf("%s: No such file or directory\n", emp[0]);
                exit(1);
            }
        } else {
            wait(&status);
        }
    }

    free(command);
    return 0;
}

