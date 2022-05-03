#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    // Kulcs létrehozása
    key_t kulcs = ftok("shmfile",65);

    // Az shmget egy azonosítót ad vissza az shmid-vel
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);

    // shmat-al csatlakozunk a memóriaszegmensre
    char str = (char) shmat(shmid,(void*)0, 0);



    printf("A szegmensbol olvasott adat: %s\n",str);

    // Lecsatlakozás a memóriaszegmensről
    shmdt(str);

    // Memóriaszegmenst törlése
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
