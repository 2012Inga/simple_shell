#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

/* environ variables */
extern char **environ;
extern __sighandler_t signal(int_sig_sgihandler_t_handler);


/* From custom_getline.c */
ssize_t custom_getline(char **line, size_t *len, FILE *stream);

/* From fork_exec_wait.c */
pid_t fork_exec_wait(const char *command);

/* From getenv.c */
char *custom_getenv(const char *name);

/* from stat.c */
int custom_stat(const char *path);

/*========Split_string.c=======*/
char **split_string(const char *str, const char *delimiter);

/* fork*/
pid_t custom_fork();


#endif
