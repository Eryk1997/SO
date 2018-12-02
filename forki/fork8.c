
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){


if(fork()==0)
	exit(0);
sleep(10);
wait(NULL);
}
