#include "fastset.h"

#include <stdlib.h>

struct fastset_t;

struct fastset_t {
	size_t max_value;
	size_t size;
	size_t *sparse;
	size_t *dense;
} fastset_t;

struct fastset_t *fastset_create(size_t max_value)
{
	struct fastset_t *fastset;

	fastset = malloc(sizeof(struct fastset_t));
	if (!fastset) {
		return NULL;
	}

	fastset->max_value = max_value;
	fastset->size = 0;
	fastset->sparse = malloc(sizeof(size_t) * max_value);
	if (!fastset->sparse) {
		return NULL;
	}
	fastset->dense = malloc(sizeof(size_t) * max_value);
	if (!fastset->dense) {
		return NULL;
	}

	return fastset;
}

void fastset_free(struct fastset_t *fastset)
{
	free(fastset->dense);
	free(fastset->sparse);
	free(fastset);
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

size_t fastset_size(struct fastset_t *fastset)
{
	return 0;
}

size_t fastset_max(struct fastset_t *fastset)
{
	return 0;
}

void fastset_clear(struct fastset_t *fastset)
{
}

void fastset_foreach(struct fastset_t *fastset, void (*pt2Func) (size_t each))
{
}
