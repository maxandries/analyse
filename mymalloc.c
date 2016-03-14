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
	struct block_header *current = first;
	while ((current->alloc == 1 && (current->size != size || (current->size)-size < 4))) {
		if ((current+current->size) == sbrk(0)){
			return NULL;
		}
		current = current + (current->size)/4;
	}
	return current;
}


void* mymalloc(size_t size){
	if(size <= 0){
		return NULL;
		
	}
	
	int sizeTot = align4(size) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	if(!first){
		first = sbrk(0);
		sbrk(memsize);
		first->size = memsize;
		first->alloc = 0;
	}
	struct block_header *newBlock = findFree(sizeTot);
	if(!newBlock){
		return NULL; //pas de place libre
	}
	if(newBlock->size == sizeTot){
		newBlock->alloc = 1;
		return (void *)(newBlock+1);
	}
	if(sizeTot<newBlock->size){
		int sizep = (newBlock->size)-sizeTot;
		newBlock->size = sizeTot;
		struct block_header *freeOne = (newBlock->size)/4+newBlock;
		freeOne->size = sizep;
		newBlock->alloc = 1;
		freeOne->alloc = 0;
		return (void *)(newBlock+1);
	}
	return NULL;
	
}


void *mycalloc(size_t size)
{
	char *p = mymalloc(size);
	int i = 0;
	while(i<size){
		*p++ = 0;
		i++;
	}
	p = p-size;
	return (void *)p;
}

void myfree(void *ptr){
	struct block_header *remov = ptr-4;
	struct block_header *current = first;
	if(remov==first){
		if((first+(first->size)/4)->alloc==0){
			remov->size = remov->size + (first+(first->size)/4)->size;
		}
		remov->alloc = 0;
	}
	else{
	remov->alloc =0;
	if((remov+(remov->size)/4)->alloc == 0){
		remov->size = remov->size +(remov+(remov->size)/4)->size; 
	}
	while((current+(current->size)/4)!=remov){
		current = (current+(current->size)/4);
	}
	if(current->alloc == 0){
		current->size = current->size + remov->size;
	}
	}
}

int main(int argc, char *argv[]){
	if(argc = 2){
		memsize = atoi(argv[1]);
	}
int *p = (int *)mymalloc(sizeof(int));
printf("adresse int: %p\n",p);
long *a = (long *)mymalloc(sizeof(long));
printf("adresse long: %p\n",a);
int *t = (int *)mymalloc(sizeof(int));
printf("adresse int2 : %p\n",t);
myfree(p);
myfree(a);
int *test = (int *)mymalloc(sizeof(int));
printf("adresse int3 : %p\n",test);
int *test1 = (int *)mycalloc(sizeof(int));
printf("adresse int4 : %p\n",test1);

}
