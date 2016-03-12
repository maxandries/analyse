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
int memsize = 4000000;

struct block_header *findFree(size_t size) {
	printf("test find\n");
	struct block_header *current = first;
	printf("current OK \n");
	int i =1;
	while (!(current->alloc == 0 && (current->size == size || (current->size)-size > 4))) {
		printf("test : %d\n", i);
		i++;
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
		printf("test 2\n");//debug
		first = sbrk(0);
		sbrk(memsize);
		first->size = memsize;
		first->alloc = 0;
		printf("%d \n", (sbrk(0)-(void *)first));
	}
	printf("not null at first call?\n");//debug
	struct block_header *freeOne = findFree(sizeTot);
	if(!freeOne){
		printf("findfree null\n");
		return NULL; //pas de place libre
	}
	printf("findfree ok\n");
	if(freeOne->size == sizeTot){
		
		return (void *)(freeOne+1);
	}
	if(sizeTot<freeOne->size){
		printf("test size : %d \n", freeOne->size);
		freeOne->size = (freeOne->size)-sizeTot;
		printf("test size 2: %d\n", freeOne->size);
		printf("adresse : %p\n",(freeOne+(freeOne->size)));
		printf("limite heap : %p\n",sbrk(0));
		struct block_header *newBlock = (freeOne->size)/4+freeOne;
		printf("struct created: %p \n", newBlock);
		printf("size: %d\n", sizeTot);
		printf("difference :%d\n", sbrk(0)-(void *)newBlock);
		printf("sizeTot: %d\n", newBlock->size);
		newBlock->size = sizeTot;
		printf("size allocated\n");
		newBlock->alloc = 1;
		return (void *)(newBlock+1);
	}
	return NULL;
	
}

void myfree(void *ptr){
	printf("adresse pointeur : %p\n", ptr);
	struct block_header *remov = ptr-1;
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
long *a = (long *)mymalloc(sizeof(long));
printf("adresse long: %p\n",a);
free(p);

}
