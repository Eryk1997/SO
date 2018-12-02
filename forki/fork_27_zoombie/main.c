#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t child_pid;
    printf("Proces macierzysty:\n");
    //tworzymy proces potomny
    child_pid = fork();
    if(child_pid > 0)
    {
        //proces rodzica zasypiamy na minutę
        sleep(5);
    }
    else
    {
        //proces potomny natychmiast kończy działanie
        exit(0);
    }

    return 0;
}

