#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)

struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};

void* findFree(size_t size){
	
}

void* malloc(size_t size){
	
}

int main(int argc, int *argv[]){
printf("test 1 :%d\n test 2:%d\n", sizeof(struct block), sizeof(block_header2));
}
