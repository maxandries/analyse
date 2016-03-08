#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};

void* malloc(size_t size){
	struct block_header *a;
	struct block *b;
	a->size = size;
	a->alloc = 1;
	
}

int main(int argc, int *argv[]){
printf("test 1 :%d\n test 2:%d\n", sizeof(struct block), sizeof(block_header2));
}
