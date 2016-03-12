#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)
struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};
struct block_header *first = NULL;
int memsize = 4000;


struct block_header *findFree(size_t size) {
  struct block_header *current = first;
  while (!(current->alloc && (current->size == size || current->size - size > 4))) {
  	if ((current+current->size) == sbrk(0)){
  		return NULL;
  		
  	}
    current = current + current->size;
  }
  return current;
}


void* mymalloc(size_t size){
	if(size <= 0){
		return NULL;
	}
	
	int sizeTot = size + (4 - (size % 4)) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	
	if(!(first)){
		first = sbrk(0);
		sbrk(memsize);
		first->size = memsize;
		first->alloc = 0;
	}
	struct block_header *freeOne = findFree(sizeTot);
	if(!freeOne){
		return NULL; //pas de place libre
	}
	if(freeOne->size == sizeTot){
		return (void *)(freeOne+4);
	}
	if(sizeTot<freeOne->size){
		freeOne->size = (freeOne->size)-sizeTot;
		struct block_header *newBlock = freeOne+freeOne->size;
		newBlock->size = sizeTot;
		newBlock->alloc = 1;
		return (void *)(newBlock+4);
	}
	return NULL;
	
}

void myfree(void *ptr){
	
}

int main(int argc, int *argv[]){

}
