# ipc_shared_memory
Steps to proceed:
# server-program
gcc -o s.out server.c
./s.out
Server attaches shared memory segment.
Start client in new window(terminal)
# client-program
gcc -o c.out client.c
./c.out (give four arguments of integer type)
# result
The server program receives the data passed as arguments to the client program.(Since they share the same memory segment)
