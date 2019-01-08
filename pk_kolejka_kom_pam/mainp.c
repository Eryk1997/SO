#include <stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define P 50   // liczba procesow prod i kons
#define MAX 10  //rozmiar buforu
#define MAX2 12 // + dwa pola na indeksy zapis/odczyt
#define PUSTY 1 //typ komunikatu
#define PELNY 2 //typ komunikatu
#define WOLNY 3
//struktura komunikatu
struct bufor{
	long mtype;
	int mvalue;
};


   int msgID; //id kolejki kom.
   int shmID;	//id pamieci dzielonej


void koniec(int a )
{  
	printf("Złapano CTRL+C.\n");
	msgctl(msgID,IPC_RMID,NULL); 
   shmctl(shmID,IPC_RMID, NULL);
   printf("MAIN: Koniec.\n");

}

int main()
{
   key_t klucz, kluczm;  //klucze do kk i pam. dz.
 //  int msgID; //id kolejki kom.
 //  int shmID;	//id pamieci dzielonej
   
   int i;
   struct bufor komunikat;

	signal(SIGINT, koniec);
   
   if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   msgID=msgget(klucz,IPC_CREAT|IPC_EXCL|0666); //tworzenie kk
   if (msgID==-1)
	{printf("blad kolejki komunikatow\n"); exit(1);}

   kluczm=ftok(".",'B');
   shmID=shmget(kluczm, MAX2*sizeof(int), IPC_CREAT|IPC_EXCL|0666);//tworzenie pam. dz.

   komunikat.mtype=PUSTY;
//   komunikat.mvalue=0;   wazny jest typ komunikatu, tresc - dowolna 
  

  
 for(i=0;i<MAX;i++)
	 {
	if( msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0)==-1) //wyslanie komunikatu typu pusty
		{
			printf("blad wyslania kom. pustego\n");
			exit(1);
		};
	   printf("wyslany pusty komunikat %d\n",i);
	}
   	   
   for (i = 0; i < P; i++)
      switch (fork())
      {
         case -1:
            perror("Blad fork (mainprog)");
            exit(2);
         case 0:
            execl("./prod","prod", NULL);
      }

   for(i=0;i<P;i++)
	switch (fork())
	{
	case -1:
	
            printf("Blad fork (mainprog)\n");
	    exit(2);
	case 0:
		execl("./kons","kons",NULL);
	}

   komunikat.mtype=WOLNY;
   	if( msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0)==-1) //wyslanie komunikatu typu WOLNY
		{
			printf("blad wyslania kom. WOLNY\n");
			exit(1);
		};
	   printf("wyslany WOLNY komunikat \n");

/*
if (fork()==0)
            execl("./prod","prod", NULL);
else
            execl("./kons","kons",NULL);
*/
for(i=0;i<2*P;i++)
   wait(NULL);

//zwalnianie zasobow
   msgctl(msgID,IPC_RMID,NULL); 
   shmctl(shmID,IPC_RMID, NULL);
   printf("MAIN: Koniec.\n");
}
