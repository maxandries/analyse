all : hello
mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c   
test.o: test.c mymalloc.h
	gcc -I$(HOME)/local/include/ -L$(HOME)/local/lib  -c test.c -lcunit
hello: mymalloc.o test.o
	gcc -I$(HOME)/local/include/ -L$(HOME)/local/lib  mymalloc.o test.o -o hello -lcunit
clean:
	rm -f *.o
./hello
