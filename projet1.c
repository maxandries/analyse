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
int taille_heap = 4000000;


struct block_head *find_free_block(size_t size) {
  struct block_head *current = *first;
  while (!(current->free && current->size >= size)) {
    *current = &current + size;
  }
  return current;
}

struct block_header* splitBlock(struct block_header name){
	
}

void* malloc(size_t size){
	if(size <= 0){
		return NULL;
	}
	
	int sizeTot = size + (4 - (size % 4)) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	//#define ALIGNEMENT 8
	//#define ALIGN(size) (((size) + (ALIGNEMENT-1)) & ~(ALIGNEMENT-1))
	
	//if (sizeTot > 42)
	
	if(!(first)){
		first = sbrk(0);
		sbrk(taille_heap);
		first->size = taille_heap;
		first->alloc =0;
	}
	
}

int main(int argc, int *argv[]){

}
