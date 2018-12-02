
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

int pid1,pid2;
if(pid1=fork()){
	printf("rodzic - pid=%d  ppid=%d pid1=%d gpid=%d\n",getpid(), getppid(),pid1,getpgrp());
	pid2=wait(NULL);
        printf("zakonczyl sie proces %d\n",pid2);
        }
else
       printf("potomek - pid=%d  ppid=%d  pid1=%d gpid=%d\n",getpid(), getppid(), pid1,getpgrp());


}
