#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

  int id, rc;

  printf("This program is needed to remove semaphores!\n");
  id = atoi(argv[1]);

  printf("Enter semaphore id=%d\n", id);
  rc = semctl(id, 1, IPC_RMID);
  if (rc < 0) {
    perror("semctl");
    exit(1);
  }

  exit(0);
}
