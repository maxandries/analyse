#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mymalloc.h"

#define SIZE_HEADER sizeof(struct block_header)
#define align4(x) (((((x)-1)>>2)<<2)+4) //fonction permettant l'aligment sur 4bits de la taille.
//test
struct block_header *first = NULL;//structure permettant la creation du premier (premier appel a mymalloc/mycalloc)
int memsize = 100;//taille du heap

//fonction permettant de trouver un bloc libre et le cas echeant retourne null
struct block_header *findFree(size_t size) {
	struct block_header *current = first; //premier bloc du heap
	while ((current->alloc == 1 && (current->size != size || (current->size)-size < 4))) {
		if (current+(current->size)/4 == sbrk(0)){
			return NULL;
		}
		current = current + (current->size)/4; // size/4 car lorsqu'on fait +1, on avance d'une fois la taille de la structure
	}
	return current;
}


void* mymalloc(size_t size){
	if ((int)size < 0){
		return NULL;
	}
	int sizeTot = align4(size) + SIZE_HEADER; //alignement sur 32bits et ajouts de la taille de la structure
	if(!first){ //si first == NULL, premier appel de malloc on initialise le heap
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
	int sizeAl = align4(size);
	char *p = mymalloc(sizeAl);
	int i = 0;
	while(i<size){
		*p++ = 0;
		i++;
	}
	int j= 0;
	p = p-sizeAl;
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

