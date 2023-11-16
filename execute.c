#include "main.h"



void _buildInCmd(char *command) {
    char *home_dir;
    char *old_pwd;
    char *dup_command;
    char *arg0;
    char *arg1;
    char *previous_dir;
    char new_path[1024];
    char cwd[1024];

    dup_command = strdup(command);
    if (dup_command == NULL) {
        perror("strdup");
        return;
    }

    arg0 = strtok(dup_command, " \t");
    if (arg0 == NULL) {
        free(dup_command);
        return;
    }

    if (strcmp(arg0, "cd") == 0) {
        old_pwd = getenv("PWD");
        if (old_pwd == NULL) {
            perror("getenv");
            free(dup_command);
            return;
        }

        arg1 = strtok(NULL, " \t");
        if (arg1 == NULL) {
            home_dir = getenv("HOME");
            if (home_dir == NULL) {
                perror("getenv");
                free(dup_command);
                return;
            }
            if (chdir(home_dir) != 0) {
                perror("chdir");
                free(dup_command);
                return;
            }
        } else if (strcmp(arg1, "-") == 0) {
            previous_dir = getenv("OLDPWD");
            if (previous_dir == NULL) {
                perror("getenv");
                free(dup_command);
                return;
            }
            if (chdir(previous_dir) != 0) {
                perror("chdir");
                free(dup_command);
                return;
            }
        } else {
            if (arg1[0] == '~') {
                home_dir = getenv("HOME");
                if (home_dir == NULL) {
                    perror("getenv");
                    free(dup_command);
                    return;
                }
                snprintf(new_path, sizeof(new_path), "%s%s", home_dir, arg1 + 1);
                if (chdir(new_path) != 0) {
                    perror("chdir");
                    free(dup_command);
                    return;
                }
            } else if (arg1[0] == '/') {
                if (chdir(arg1) != 0) {
                    perror("chdir");
                    free(dup_command);
                    return;
                }
            } else {
                if (chdir(arg1) != 0) {
                    perror("chdir");
                    free(dup_command);
                    return;
                }
            }
        }

        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            free(dup_command);
            return;
        }

        if (setenv("PWD", cwd, 1) == -1) {
            perror("setenv");
            free(dup_command);
            return;
        }

        if (setenv("OLDPWD", old_pwd, 1) == -1) {
            perror("setenv");
            free(dup_command);
            return;
        }
    }

    free(dup_command);
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

