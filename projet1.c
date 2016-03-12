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
int memsize = 40000;


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
	printf("test\n");
	if(size <= 0){
		return NULL;
	}
	
	int sizeTot = size + (4 - (size % 4)) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	printf("sizeTot : %d", sizeTot);
	if(!(first)){
		printf("test 2/n");
		first = sbrk(0);
		sbrk(memsize);
		first->size = memsize;
		first->alloc = 0;
		printf("%d/n", (sbrk(0)-(void *)first));
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
	struct block_header *remov = ptr-4;
	remov-> alloc = 0;
}

void flattenheap(){
	struct block_header *current = first;
  	while (!(current + (current->size))) {
  		if(!(current->alloc && (current+(current->size))->alloc)){
  			current->size = (current->size)+ (current+(current->size))->size;
  		}
    		current = current + current->size;
  	}
}

int main(int argc, int *argv[]){
int *p = (int *)mymalloc(sizeof(int));
printf("adresse int: %p\n",p);
}
