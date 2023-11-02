#include <stdio.h>
#include <unistd.h>
#include "main.h"
int _parent_pid() {
    pid_t parent_pid = getppid();
    printf("Parent PID: %d\n", parent_pid);
    return 0;
}
