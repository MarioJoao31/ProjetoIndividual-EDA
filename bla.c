#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
char *newargv[] = { "printenv", NULL };
char *newenviron[] = { NULL };
execve("/usr/bin/printenv",newargv,newenviron);
perror("erro no execve");
exit(EXIT_FAILURE);
}