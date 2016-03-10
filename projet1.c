#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)
int taille_heap = 4000000;
void *base = NULL;
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
	if(size <=0){
		return NULL;
	}
	
	if(!(*base)){
		base = sbrk(0);
		sbrk(taille_heap+4);
		struct block_header *first;
		first->size = taille_heap;
		first->alloc =0;
	}
	size = size + (4 - (size % 4));
	//#define ALIGNEMENT 8
	//#define ALIGN(size) (((size) + (ALIGNEMENT-1)) & ~(ALIGNEMENT-1))
}

int main(int argc, int *argv[]){

}
