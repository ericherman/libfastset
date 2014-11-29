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

int fastset_add(struct fastset_t *fastset, size_t value)
{
	if (value > fastset->max_value) {
		return 0;
	}
	if (fastset_contains(fastset, value)) {
		return 1;
	}
	fastset->dense[fastset->size] = value;
	fastset->sparse[value] = fastset->size;
	fastset->size++;
	return 1;
}

int fastset_contains(struct fastset_t *fastset, size_t value)
{
	if (fastset->sparse[value] >= fastset->size) {
		return 0;
	}
	return fastset->dense[fastset->sparse[value]] == value;
}

void fastset_remove(struct fastset_t *fastset, size_t value)
{
	size_t tmp;

	if (!fastset_contains(fastset, value)) {
		return;
	}

	tmp = fastset->dense[fastset->size - 1];
	fastset->dense[fastset->sparse[value]] = tmp;
	fastset->sparse[tmp] = fastset->sparse[value];
	fastset->size--;
}

size_t fastset_size(struct fastset_t *fastset)
{
	return fastset->size;
}

size_t fastset_max(struct fastset_t *fastset)
{
	return fastset->max_value;
}

void fastset_clear(struct fastset_t *fastset)
{
	fastset->size = 0;
}

void fastset_foreach(struct fastset_t *fastset,
		     void (*func) (size_t each, void *arg))
{
}
