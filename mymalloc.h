
struct block_header {
	unsigned int size : 29,
		     zero: 2,
		     alloc: 1;
};

struct block_header *findFree(size_t size);
void* mymalloc(size_t size);
void *mycalloc(size_t size);
void myfree(void *ptr);

