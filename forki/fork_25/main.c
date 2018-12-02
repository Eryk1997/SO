#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

void wypisz(void);

int main(void)
{
    int i;
    int status;  //stan wyjścia z wait()
    pid_t wpid;  //identyfikator procesu z wait()
    pid_t pid;  //identyfikator procesu potomnego
    system("clear");

    for(int i=0;i<3;i++)
    {
        puts("\n");
        pid = fork();

        switch(pid)
        {
        case -1:
            fprintf(stderr,"%s:Bład\n",strerror(errno));
            exit(1);
        case 0:
            printf("PID %ld: Proces potomny uruchomiony PPID: %ld \n",(long)getpid(),(long)getppid());
            execl("/bin/ps","ps",NULL);
            break;
        default:
            printf("PID %ld: Proces macierzysty, PID %ld. \n",(long)getpid,(long)pid);
            wpid = wait(&status);  //stan wyjścia z procesu
        if(wpid==-1)
        {
            fprintf(stderr,"%s: wait()\n",strerror(errno));
            return(1);
        }
        else if(wpid != pid)
            abort();  //to się nigdy nie powinno zdażyć w tym programie
       else
        {
            printf("Proces potomny o ident. %ld zakoczył działanie ze stanem 0x%04X\n",(long)pid,status);
        }
        }
        return 0;
    }}



