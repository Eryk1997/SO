#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

sig_atomic_t child_exit_status;

void clean_up_child_proces(int signal_number)
{
    //czyszczenie procesu potomnego
    int status;
    wait(&status);
    //zachowanie statusu wyjscia
    child_exit_status = status;
}

int main(void)
{
    //obsluga SIGCHLD poprzez wywołanie
    struct sigaction sigchld_action;
    memset (&sigchld_action,0,sizeof(sigchld_process));
    sigchld_action.sa_handler = &clean_up_child_proces;
    sigaction (SIGCHLD,&sigchld_action,NULL);


    return 0;
}

