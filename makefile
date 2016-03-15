all : hello
mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c   
test.o: test.c mymalloc.h
	gcc -c test.c -I$(HOME)/local/include/ -L$(HOME)/local/lib -lcunit
hello: mymalloc.o test.o
	gcc -I$(HOME)/local/include/ -L$(HOME)/local/lib -lcunit -o hello mymalloc.o test.o
