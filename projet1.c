#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)
size_t taille_heap = 4000000;
struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};


struct block_meta *find_free_block(size_t size) {

}

struct block_header* splitBlock(struct block_header name){
	
}

void* malloc(size_t size){
	size = size + (4 - (size % 4));
}

int main(int argc, int *argv[]){

}
