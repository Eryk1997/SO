#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char * argv[])
{
FILE *wynik;
close(1);
wynik=fopen("wynik", "r+");

execvp("who", argv);
//argumenty linii polecen przekazane do who

execlp ("ls", "ls", "-l", NULL);

}
