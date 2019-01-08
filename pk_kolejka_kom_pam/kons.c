#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>


struct bufor{
	int mtype;
	int mvalue;
};

int *pam; 
#define MAX2 12
#define MAX 10
#define PELNY 2
#define PUSTY 1
#define WOLNY 3
#define zapis pam[MAX+1]
#define odczyt pam[MAX]

int main()
{
   key_t klucz, kluczm;
   int msgID, shmID;
   int i;
   int pamm[12];
   struct bufor komunikat;
    
   if ((klucz = ftok(".", 'A')) == -1 ){printf("Blad ftok (main)\n");exit(1);}

   msgID=msgget(klucz,IPC_EXCL|0666);                                            //uzyskanie dosepu do kolejki komunikatow 
   if (msgID==-1){printf("blad kolejki komunikatow\n"); exit(1);}

   kluczm=ftok(".",'B');                                                         //uzyskanie dosepu do pamieci dzielonej
   shmID=shmget(kluczm, MAX2*sizeof(int),IPC_EXCL|0666);

	if((pam = shmat(shmID, NULL, 0)) == (int *)-1)                                //przylaczenie pam. dzielonej
   {
		printf("Blad pamieci wspoldzielonej\n");
		exit(EXIT_FAILURE);
	}
//	printf("Adres: %d\n",*pam);

   msgrcv(msgID, &komunikat, sizeof(int), PELNY, 0);                             //odbieranie/wysylanie odpowiednich komunikatow +
   msgrcv(msgID, &komunikat, sizeof(int), WOLNY, 0);//sk
   
	printf("konsument odebrał: %d\n", pam[odczyt]);                               // odczyt z bufora  elementu o  indeksie odczyt (pam. dzielona)
   pam[odczyt++] = 0;                                                            
   komunikat.mtype = PUSTY;
   msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0);

   if(odczyt == MAX) odczyt = 0;
      
   printf("------konsument------\n");
   komunikat.mtype = WOLNY;
   msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0);
  


//uzyskanie dosepu do kolejki komunikatow 
//uzyskanie dosepu do pamieci dzielonej
//przylaczenie pam. dzielonej
//odbieranie/wysylanie odpowiednich komunikatow +
// odczyt z bufora  elementu o  indeksie odczyt (pam. dzielona)
//modyfikacja indeksu do odczytu
 

}

