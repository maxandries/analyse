hello: mymalloc test
mymalloc: mymalloc.c mymalloc.h
	gcc -o mymalloc mymalloc.c   
test: test.c
	gcc -o test test.c -L$(HOME)/local/lib -I$(HOME)/local/include -lcunit
