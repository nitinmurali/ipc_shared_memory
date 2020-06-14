// header file

#define  NOT_READY  -1

#define  FILLED     0

#define  TAKEN      1



struct Memory {

     int  status;

     int  data[4];

};

 /*NOT_READY=>if the data area has not yet been filled with data

FILLED=>if the server has filled data in the shared memory

TAKEN=>if the client has taken the data in the shared memory.*/
