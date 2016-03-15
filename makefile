hello: mymalloc test
mymalloc: mymalloc.c mymalloc.h
	gcc -o mymalloc mymalloc.c   
test: test.c
	gcc -o test test.c mymalloc.h -I$(HOME)/local/include/ -L$(HOME)/local/lib -lcunit
