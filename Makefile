all: main.o merkle_tree.o node.o 
	g++ merkle_tree.o node.o main.o -lcrypto -o main.x

main.o: main.cc
	g++ -c main.cc

merkle_tree.o: merkle_tree.cc merkle_tree.hh
	g++ -c merkle_tree.cc

node.o: node.cc node.hh
	g++ -c node.cc

clean: utils.o main.o merkle_tree.o node.o
	rm *.o ./nodes/* 