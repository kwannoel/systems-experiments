#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
  int shmid, i, input, *shm;

  // See from stdout the shmid from master
  printf("Shared memory id for attachment: ");
  scanf("%d", &shmid);

  // attach
  shm = (int*) shmat( shmid, NULL, 0 );
  if (shm == (int*)-1) {
    printf("Error: Cannot attach!\n");
    exit(1);
  }

  // Write values
  for (i = 0; i < 3; i++) {
    scanf("%d", &input);
    shm[i + 1] = input;
  }

  // READY
  shm[0] = 1;

  // detach memory
  shmdt( (char*)shm );
  return 0;
}
