#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
	struct block_header *next;
};

struct block{
	struct block_header header;
	struct block *next;
};

void* malloc(size_t size){
	struct block_header *a;
	struct block *b;
	a->size = size;
	a->alloc = 1;
	
}

int main(int argc, int *argv[]){
printf("%d\n", sizeof(struct block_header));
}
