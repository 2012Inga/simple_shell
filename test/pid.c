#include <stdio.h>
#include <unistd.h>
#include "main.h"
/**
 * main - PID
 *
 * Return: Always 0.
 */
int _pid(void)
{
    pid_t my_pid;

    my_pid = getpid();
    printf("%u\n", my_pid);
    return (0);
}
