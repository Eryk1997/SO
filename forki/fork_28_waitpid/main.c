#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    int status,exit_status;

    if((pid = fork()) < 0)
        printf("Blad! Nie można utworzyc nowego procesu\n");
    if(pid==0)
    {
        //potomek
        printf("Potomek o pid:%d jest uspiony...\n",getpid());
        sleep(7);
        exit(5);   //wyjscie potomka z wartoscia niezerowa
    }
    //odtad dziala rodzic
    while(waitpid(pid,&status,WNOHANG)==0)
    {
        printf("Nadal czekam na zakonczenie potomka...\n");
        sleep(1);
    }

    //Uruchomienie gdy potomek sie zakonczy
    exit_status = WEXITSTATUS(status);
    printf("Proces %d zakonczył się zwracajac wartosc %d\n",pid,exit_status);
    exit(0);


}

