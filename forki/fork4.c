
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
printf("START\n");
if(fork()==0)
    execlp("cal", "cal", "1290",NULL);
wait(NULL);
printf("META\n");

}
