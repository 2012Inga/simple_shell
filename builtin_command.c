#include "main.h"

/**
 * set_env_variable - Set or modify an environment variable.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: 0 on success, -1 on failure.
 */ 
  int
set_env_variable (const char *variable, const char *value) 
{
  
if (setenv (variable, value, 1) == -1)
    
    {
      
fprintf (stderr, "Error: Could not set environment variable %s\n",
		variable);
      
return (-1);
    
}
  
return (0);

}


 
/**
 * unset_env_variable - Unset an environment variable.
 * @variable: The name of the environment variable to unset.
 *
 * Return: 0 on success, -1 on failure.
 */ 
  int
unset_env_variable (const char *variable) 
{
  
if (unsetenv (variable) == -1)
    
    {
      
fprintf (stderr, "Error: Could not unset environment variable %s\n",
		variable);
      
return (-1);
    
}
  
return (0);

}


void
exit_arg (char *arg)
{
  
int status;
  
 
if (arg == NULL)
    {
      
 
status = 0;
    
}
  else
    {
      
 
status = atoi (arg);
    
}
  
exit (status);

}

/**
 * execute_command - Execute a shell command.
 * @command: The command string to be executed.
 */

