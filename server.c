// Server-Program

#include  <stdio.h>

#include  <stdlib.h>

#include  <sys/types.h>

#include  <sys/ipc.h>

#include  <sys/shm.h>

#include  <unistd.h>



#include  "shared.h"



void  main(void)

{

     key_t          ShmKEY;

     int            ShmID;

     struct Memory  *ShmPTR;

     //creates a unique key based on the path of the current directory and id used in the shmget()

    ShmKEY = ftok(".", 'x');

     //returns identifier for the shared memory segment

     ShmID = shmget(ShmKEY, sizeof(struct Memory), IPC_CREAT | 0666);

     //shmget() error check

     if (ShmID < 0) {

          printf("*** shmget error (server) ***\n");

          exit(1);

     }

     printf("Server has received a shared memory of four integers...\n");

     //attaches struct Memory in the shared memory segment created





     ShmPTR = (struct Memory *) shmat(ShmID, NULL, 0);

     if (ShmPTR == (void*)-1) {

          printf("*** shmat error (server) ***\n");

          exit(EXIT_FAILURE);

     }



     ShmPTR->status  = NOT_READY;

     printf("Server has attached the shared memory...\n");

     ShmPTR->status = FILLED;

     printf("Please start the client in another window...\n");

     //waits for client to take the data from the server

     while (ShmPTR->status != TAKEN)

          sleep(1);

     //server process completes once client process enters data

      printf("   Server found the data is ready...\n");

     printf("Server has found %d %d %d %d to shared memory...\n",

            ShmPTR->data[0], ShmPTR->data[1], 

            ShmPTR->data[2], ShmPTR->data[3]);

     printf("Server has detected the completion of its client...\n");

     //detach shared memory segment

     shmdt((void *) ShmPTR);

     printf("Server has detached its shared memory...\n");

     //destroy the shared memory segment using IPC_RMID

     shmctl(ShmID, IPC_RMID, NULL);

     printf("Server has removed its shared memory...\n");

     printf("Server exits...\n");

     exit(EXIT_SUCCESS); }
     
