test: test.c
	gcc -o test test.c -lcunit -L$(HOME)/local/lib -I$(HOME)/local/include
