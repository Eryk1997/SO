#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{

printf("START\n");
execlp("ls", "ls", "-l",NULL);
printf("META\n");
}

