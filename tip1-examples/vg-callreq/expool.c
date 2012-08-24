#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <valgrind/valgrind.h>

/* dummy mem pool, only linear alloc supported */
typedef struct {
	char *start;
	char *free;
	int alloc;
	int size;
} expool;

/* forbidden zone size before and after malloc'd space */
#define REDZONE_SIZE 1

expool *create_pool(int size)
{
	expool *pool = malloc(sizeof(expool) + size);
	VALGRIND_CREATE_MEMPOOL(pool, REDZONE_SIZE, 0);
	pool->start = (char*)pool + sizeof(expool);
	pool->free = pool->start;
	pool->alloc = 0;
	pool->size = size;
	return pool;
}

void destroy_pool(expool *pool)
{
	free(pool);
	VALGRIND_DESTROY_MEMPOOL(pool);
}

void *malloc_pool(expool *pool, int size)
{
	char *p;
	if (pool->alloc + size > pool->size) {
		return NULL;
	}
	p = pool->free + REDZONE_SIZE;
	VALGRIND_MEMPOOL_ALLOC(pool, p, size);
	/* uncomment the following line if you want find unreleased mempool
	 * allocation */
//	VALGRIND_MALLOCLIKE_BLOCK(p, size, REDZONE_SIZE, 0);
	pool->free += size + 2*REDZONE_SIZE;
	pool->alloc += size + 2*REDZONE_SIZE;
	return p;
}

int main()
{
	expool *pool = create_pool(256);
	char *buf = malloc_pool(pool, 5);
#define MSG1 "hello"
#define MSG2 "hello,world"
	memcpy(buf, MSG1, sizeof(MSG1)-1);	/* Good */
	memcpy(buf, MSG2, sizeof(MSG2)-1);	/* Oops...should detect OOB access! */
	buf = malloc_pool(pool, 10);
	destroy_pool(pool);
	return 0;
}

