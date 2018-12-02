#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

void wypisz(void);

int main(void)
{
    int i;
    pid_t child;
    printf("Proces macierzysty:\n");
    wypisz();
    for(int i=1;i<4;i++)
    {
        child = fork();
        switch(child)
        {
        case -1:
            perror("fork error!!!!");
            exit(1);
        case 0:
            printf("\nProces potomny %d:\n",i);
            wypisz();
            execl("./zad1","zad1",NULL);
        }
    }
    sleep(3);
    exit(0);

}

void wypisz(void)
{
    printf("id uzytkownika: %d\n",(int)getuid());
    printf("id grupy uzytkownika: %d\n",(int)getgid());
    printf("id procesu: %d\n",(int)getpid());
    printf("id pr macierzystego: %d\n",(int)getppid());
    printf("id grupy procesów: %d\n",(int)getpgrp());
    fflush(NULL);


}

