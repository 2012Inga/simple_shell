#include "main.h"



void _buildInCmd(char **arg) {
    char *home_dir;
    char *old_pwd;
    char *previous_dir;
    char cwd[1024];
    if (strcmp(arg[0], "cd") == 0) {
        old_pwd = getenv("PWD");
        if (old_pwd == NULL) {
            perror("getenv");
            return;
        }

        if (arg[1] == NULL) {
            home_dir = getenv("HOME");
            if (home_dir == NULL) {
                perror("getenv");
                return;
            }
            chdir(home_dir);
        } else if (strcmp(arg[1], "-") == 0) {
            previous_dir = getenv("OLDPWD");
            if (previous_dir == NULL) {
                perror("getenv");
                return;
            }
            chdir(previous_dir);
        } else {
            chdir(arg[1]);
        }

        
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            return;
        }

        if (setenv("PWD", cwd, 1) == -1) {
            perror("setenv");
            return;
        }

        if (setenv("OLDPWD", old_pwd, 1) == -1) {
            perror("setenv");
            return;
        }
    }
    return;
}

void execute_command(char *command)
{
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;
    char **env = environ;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL;

    
   
     if (strcmp(argv[0], "env") == 0)
    {
        while (*env)
	{
            printf("%s\n", *env);
            env++;
        }
    } else {
        if (execvp(argv[0], argv) == -1)
	{
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");

            while (dir != NULL)
	    {
                char full_path[BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
                if (access(full_path, X_OK) == 0)
		{
                    if (execve(full_path, argv, environ) == -1)
		    {
                        perror("Command execution error");
                        exit(EXIT_FAILURE);
                    }
                }
                dir = strtok(NULL, ":");
            }

            
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
}

