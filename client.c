// Client-Program

#include  <stdio.h>

#include  <stdlib.h>

#include  <sys/types.h>

#include  <sys/ipc.h>

#include  <sys/shm.h>

#include  <unistd.h>



#include  "shared.h"



void  main(int  argc, char *argv[])

{

     key_t          ShmKEY;

     int            ShmID;

     struct Memory  *ShmPTR;

     //the client takes array of 4 integers as an arguments

      if (argc != 5) {

          printf("Use: %s #1 #2 #3 #4\n", argv[0]);

          exit(EXIT_FAILURE);

     }

     //creates a unique key based on the path of the current directory and id used in the shmget()

     ShmKEY = ftok(".", 'x');

     //returns identifier for the shared memory segment

     ShmID = shmget(ShmKEY, sizeof(struct Memory), 0666);

     //shmget() error check

     if (ShmID < 0) {

          printf("*** shmget error (client) ***\n");

          exit(1);

     }

     printf("   Client has received a shared memory of four integers...\n");

     //attaches struct Memory in the shared memory segment created

     ShmPTR = (struct Memory *) shmat(ShmID, NULL, 0);

     if (ShmPTR == (void*)-1) {

          printf("*** shmat error (client) ***\n");

          exit(1);

     }

     printf("   Client has attached the shared memory...\n");

     //atoi() converts string argument to integer type

     ShmPTR->data[0] = atoi(argv[1]);

     ShmPTR->data[1] = atoi(argv[2]);

     ShmPTR->data[2] = atoi(argv[3]);

     ShmPTR->data[3] = atoi(argv[4]);

     //waits for server to get filled

     while (ShmPTR->status != FILLED)

          ;

     //Once server gets filled with the data passed the client receives it from the shared memory  

     printf("   Client filled %d %d %d %d in shared memory...\n",

                ShmPTR->data[0], ShmPTR->data[1], 

                ShmPTR->data[2], ShmPTR->data[3]);



     ShmPTR->status = TAKEN;

      printf("   Client has informed server data have been filled...\n");

     //detach shared memory segment

     shmdt((void *) ShmPTR);

     printf("   Client has detached its shared memory...\n");

     printf("   Client exits...\n");

     exit(EXIT_SUCCESS); }
