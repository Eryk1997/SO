#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

void wypisz(void);

int main(void)
{
    switch(fork())
       {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        printf("potomek\n");
    default:
        printf("proces macierzysty\n");



    }

    return 0;
}

