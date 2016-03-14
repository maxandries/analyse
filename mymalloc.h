#ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME

struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};

struct block_header *findFree(size_t size);
void* mymalloc(size_t size);
void *mycalloc(size_t size);
void myfree(void *ptr);

#endif
