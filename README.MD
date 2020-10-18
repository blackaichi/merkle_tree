## Merkle Tree implementation in C++

To execute:
```console
foo@bar:~$ make all
g++ -c main.cc
g++ -c merkle_tree.cc
g++ -c node.cc
g++ merkle_tree.o node.o main.o -lcrypto -o main.x
foo@bar:~$ ./main.x
```
And follow steps

Also you can use:
```console
foo@bar:~$ make clean
rm *.o ./nodes/*
```
To clean all .o and the folder nodes.

### Output

The program will generate a report document in the directory where you execute the program and the nodes in the "./nodes" folder. Also the program can generate more docs in the folder "./docs"