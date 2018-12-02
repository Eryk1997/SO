
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

int pid1,pid2, status;

if(pid1=fork()){
	printf("rodzic - pid=%d  ppid=%d pid1=%d\n",getpid(), getppid(),pid1);
	sleep(1);
        kill(pid1,9);
        pid2=wait(&status);
        printf("zakonczyl sie proces %d z kodem %d\n",pid2, status);
        }
else
       printf("potomek - pid=%d  ppid=%d  pid1=%d\n",getpid(), getppid(), pid1);


}
