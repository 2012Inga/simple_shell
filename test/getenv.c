#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

 extern char **environ; 
char *_getenv(const char *name) {

  char **env = environ;
 
  while (*env) {
    char *sepa = strchr(*env, '=');
    if (sepa) {
      if (strncmp(*env, name, sepa - *env) == 0) {
        return sepa + 1;
      }
    }
    env++;
  }
   return NULL;
}
int main(int argc, char *argv[]) {
  char *name = argv[1];
   char *value = _getenv(name);
   if (value) {
    printf("%s: %s\n", name, value);
  } else {
     printf("The environment variable %s is not defined.\n", name);
  }

  return 0;
}
