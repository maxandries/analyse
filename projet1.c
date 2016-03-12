#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)
#define align4(x) (((((x) -1)>>2)<<2)+4)
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
	printf("test\n");//debug
	if(size <= 0){
		printf("null");//debug
		return NULL;
		
	}
	
	int sizeTot = align4(size) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	printf("sizeTot : %d\n", sizeTot);//debug
	if(!first){
		printf("test 2 test test test/n");//debug
		first = sbrk(0);
		sbrk(memsize);
		first->size = memsize;
		first->alloc = 0;
		printf("%d/n", (sbrk(0)-(void *)first));
	}
	printf("not null at first call?");//debug
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
