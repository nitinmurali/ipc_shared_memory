# ipc_shared_memory
Steps to proceed:
# server-program
gcc -o s.out server.c </br>
./s.out </br>
Server attaches shared memory segment. </br>
Start client in new window(terminal) </br>
# client-program
gcc -o c.out client.c </br>
./c.out (give four arguments of integer type) </br>
# result
The server program receives the data passed as arguments to the client program.(Since they share the same memory segment)
