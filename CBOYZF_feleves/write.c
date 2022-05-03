#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    // Kulcs létrehozása
    key_t kulcs = ftok("shmfile",65);
  
    // Az shmget egy azonosítót ad vissza az shmid-vel
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);
  
    // shmat-al csatlakozunk a memóriaszegmensre
    char* str = (char*) shmat(shmid,(void*)0,0);
  
  
  
	// Fájl megnyitása olvasásra
  
    FILE* ptr;
 
	if ((ptr=fopen("teszt.txt", "r")) == NULL){
       printf("Fajl megnyitasa sikertelen! A hiba oka:\n");
	   perror(0);
	   exit(1);
	}

	// Fájl tartalmának olvasása majd kiírása a memóriaszegmensbe, fájl pointer lezárása
	fgets(str, 256, ptr);
	fclose(ptr);
  
    printf("A szegmensbe irt adat: %s\n", str);
	
    // Lecsatlakozunk a memóriaszegmensről. 
    shmdt(str);
	
  
    return 0;
}
