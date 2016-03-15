mymalloc: mymalloc.c mymalloc.h
	gcc -o mymalloc mymalloc.c                          
test: test.c
	gcc -o test test.c -lcunit -L$(HOME)/local/lib -I$(HOME)/local/include
