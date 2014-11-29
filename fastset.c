#include "fastset.h"

struct fastset_t;

struct fastset_t {
	size_t max_value;
	size_t size;
	size_t *sparse;
} fastset_t;

struct fastset_t *fastset_create(size_t max_value)
{
	return NULL;
}

void fastset_free(struct fastset_t *fastset)
{
}

void fastset_add(struct fastset_t *fastset, size_t value)
{
}

int fastset_contains(struct fastset_t *fastset, size_t value)
{
	return 0;
}

void fastset_remove(struct fastset_t *fastset, size_t value)
{
}

size_t fastset_size(struct fastset_t *fastset) {
	return 0;
}

size_t fastset_max(struct fastset_t *fastset) {
	return 0;
}

void fastset_clear(struct fastset_t *fastset)
{
}

void fastset_foreach(struct fastset_t *fastset, void (*pt2Func) (size_t each))
{
}
