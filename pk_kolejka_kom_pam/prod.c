#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct bufor{
	int mtype;
	int mvalue;
};

int produkcja(int min, int max)
{
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ? (rand() % max + min) : min;
}

int *pam;

#define MAX 10
#define MAX2 12
#define PELNY 2
#define PUSTY 1
#define WOLNY 3
#define odczyt pam[MAX]
#define zapis pam[MAX+1]
int main()
{
   key_t klucz, kluczm;
   int msgID;
   int shmID;
   int i; // to, co ma trafic do bufora 
   int wyprodukowana;
   int pamm[12];
	
   struct bufor komunikat;

    if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   msgID=msgget(klucz,IPC_EXCL|0666);                                //uzyskanie dostepu do kolejki komunikatow
   if (msgID==-1) {printf("blad kolejki komunikatow\n"); exit(1);}

   kluczm=ftok(".",'B');                                             //uzyskanie dostepu do pamieci dzielonej
   shmID=shmget(kluczm, MAX2*sizeof(int), IPC_EXCL|0666);
	

	if((pam = shmat(shmID, NULL, 0)) == (int *)-1)                    //przylaczenie pamieci dzielonej
   {printf("Blad pamieci wspoldzielonej\n");exit(EXIT_FAILURE);}
	//printf("Adres: %d\n",*pam);

    msgrcv(msgID, &komunikat, sizeof(int), PUSTY, 0);                //wysylanie/odbieranie odpowiednich komunikatow
    msgrcv(msgID, &komunikat, sizeof(int), WOLNY, 0);//sk
        pam[zapis++] = time(NULL)%100000;
    komunikat.mtype = PELNY;
    msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0);
    if(zapis == MAX)
        zapis = 0;

    printf("------producent------\n");
    komunikat.mtype = WOLNY;
        msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0);


//uzyskanie dostepu do kolejki komunikatow
//uzyskanie dostepu do pamieci dzielonej
//przylaczenie pamieci dzielonej
//wysylanie/odbieranie odpowiednich komunikatow
//produkcja - dodanie rekordu do puli buforow liczby int 2-cyfrowej pod indeks - zapis 
//np. z wykorzystaniem: ---  time(&czas);
//modyfikacja indeksu do zapisu
}
