
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

printf("A");
if(fork())  fork();
printf("B");
if(!fork()){
printf("C");
execlp("echo","echo","D",NULL);
}
printf("D");
vim 
}
