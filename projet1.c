#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_HEADER sizeof(struct block_header)

struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};

static struct block *base;
base->size = sbrk(0)-(&base+4);
base->alloc = 0;


struct block_meta *find_free_block(size_t size) {
  struct block_header *current = global_base;
  while (current && !(current->alloc && current->size >= size)) {
    current = (current + 4 + current->size);
  }
  return current;
}

struct block_header* splitBlock(struct block_header name){
	
}

void* malloc(size_t size){
	size = size + (4 - (size % 4));
}

int main(int argc, int *argv[]){

}
