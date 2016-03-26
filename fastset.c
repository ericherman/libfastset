#include "fastset.h"
#include <stdlib.h>
#include <string.h>

struct fastset_s {
	size_t max_value;
	size_t size;
	size_t *sparse;
	size_t *dense;
	char calloc_flag;
} fastset_s;

struct fastset_s *fastset_create(size_t max_value, int zero_mem)
{
	struct fastset_s *fastset;

	fastset = malloc(sizeof(struct fastset_s));
	if (!fastset) {
		return NULL;
	}

	fastset->max_value = max_value;
	fastset->size = 0;
	fastset->calloc_flag = (zero_mem) ? 1 : 0;

	if (fastset->calloc_flag) {
		fastset->sparse = calloc(1 + max_value, (sizeof(size_t)));
	} else {
		fastset->sparse = malloc((1 + max_value) * (sizeof(size_t)));
	}
	if (!fastset->sparse) {
		free(fastset);
		return NULL;
	}

	if (fastset->calloc_flag) {
		fastset->dense = calloc(1 + max_value, (sizeof(size_t)));
	} else {
		fastset->dense = malloc((1 + max_value) * (sizeof(size_t)));
	}
	if (!fastset->dense) {
		free(fastset->sparse);
		free(fastset);
		return NULL;
	}

	return fastset;
}

void fastset_free(struct fastset_s *fastset)
{
	free(fastset->dense);
	free(fastset->sparse);
	free(fastset);
}

int fastset_add(struct fastset_s *fastset, size_t value)
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

int fastset_contains(struct fastset_s *fastset, size_t value)
{
	if (value > fastset->max_value) {
		return 0;
	}
	if (fastset->sparse[value] >= fastset->size) {
		return 0;
	}
	return fastset->dense[fastset->sparse[value]] == value;
}

void fastset_remove(struct fastset_s *fastset, size_t value)
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

size_t fastset_size(struct fastset_s *fastset)
{
	return fastset->size;
}

size_t fastset_max(struct fastset_s *fastset)
{
	return fastset->max_value;
}

void fastset_clear(struct fastset_s *fastset)
{
	fastset->size = 0;
}

void fastset_foreach(struct fastset_s *fastset,
		     void (*func) (size_t each, void *arg), void *arg)
{
	size_t i;

	for (i = 0; i < fastset->size; i++) {
		(*func) (fastset->dense[i], arg);
	}
}

struct fastset_s *fastset_clone(struct fastset_s *fastset)
{
	struct fastset_s *clone;
	size_t i;

	clone = fastset_create(fastset->max_value, fastset->calloc_flag);
	if (!clone) {
		return NULL;
	}

	/* if the set is close to full, just memcpy */
	if ((fastset->max_value / fastset->size) < 4) {
		clone->size = fastset->size;
		memcpy(clone->dense, fastset->dense,
		       sizeof(size_t) * fastset->size);
		memcpy(clone->sparse, fastset->sparse,
		       sizeof(size_t) * (1 + fastset->max_value));
	} else {
		for (i = 0; i < fastset->size; i++) {
			fastset_add(clone, fastset->dense[i]);
		}
	}
	return clone;
}

struct fastset_s *fastset_intersect(struct fastset_s *s1, struct fastset_s *s2)
{
	struct fastset_s *result, *tmp;
	size_t i;

	result = fastset_create(s1->max_value, s1->calloc_flag);
	if (!result) {
		return NULL;
	}

	if (s1->size > s2->size) {
		tmp = s1;
		s1 = s2;
		s2 = tmp;
	}

	for (i = 0; i < s1->size; i++) {
		if (fastset_contains(s2, s1->dense[i])) {
			fastset_add(result, s1->dense[i]);
		}
	}

	return result;
}

struct fastset_s *fastset_union(struct fastset_s *s1, struct fastset_s *s2)
{
	struct fastset_s *result;
	size_t i, max_value;
	int zero_mem;

	max_value =
	    (s1->max_value < s2->max_value) ? s2->max_value : s1->max_value;
	zero_mem = (s1->calloc_flag || s2->calloc_flag);

	result = fastset_create(max_value, zero_mem);
	if (!result) {
		return NULL;
	}

	for (i = 0; i < s1->size; i++) {
		fastset_add(result, s1->dense[i]);
	}
	for (i = 0; i < s2->size; i++) {
		fastset_add(result, s2->dense[i]);
	}

	return result;
}

struct fastset_s *fastset_minus(struct fastset_s *s1, struct fastset_s *s2)
{
	struct fastset_s *result;
	size_t i;

	result = fastset_create(s1->max_value, s1->calloc_flag);
	if (!result) {
		return NULL;
	}

	for (i = 0; i < s1->size; i++) {
		if (!fastset_contains(s2, s1->dense[i])) {
			fastset_add(result, s1->dense[i]);
		}
	}

	return result;
}

struct fastset_s *fastset_unique(struct fastset_s *s1, struct fastset_s *s2)
{
	struct fastset_s *result;
	size_t i, max_value;
	int zero_mem;

	max_value =
	    (s1->max_value < s2->max_value) ? s2->max_value : s1->max_value;
	zero_mem = (s1->calloc_flag || s2->calloc_flag);

	result = fastset_create(max_value, zero_mem);
	if (!result) {
		return NULL;
	}

	for (i = 0; i < s1->size; i++) {
		if (!fastset_contains(s2, s1->dense[i])) {
			fastset_add(result, s1->dense[i]);
		}
	}
	for (i = 0; i < s2->size; i++) {
		if (!fastset_contains(s1, s2->dense[i])) {
			fastset_add(result, s2->dense[i]);
		}
	}

	return result;
}

int fastset_equal(struct fastset_s *s1, struct fastset_s *s2)
{
	size_t i;

	if (s1->size != s2->size) {
		return 0;
	}

	for (i = 0; i < s1->size; i++) {
		if (!fastset_contains(s2, s1->dense[i])) {
			return 0;
		}
	}
	return 1;
}

int fastset_disjoint(struct fastset_s *s1, struct fastset_s *s2)
{
	size_t i;
	struct fastset_s *tmp;

	if (!s1->size && !s2->size) {
		return 1;
	}
	if (s1->size > s2->size) {
		tmp = s2;
		s2 = s1;
		s1 = tmp;
	}

	for (i = 0; i < s1->size; i++) {
		if (fastset_contains(s2, s1->dense[i])) {
			return 0;
		}
	}
	return 1;
}

int fastset_subset(struct fastset_s *s1, struct fastset_s *s2, int strict)
{
	size_t i;

	if (s1->size < s2->size) {
		return 0;
	}

	for (i = 0; i < s2->size; i++) {
		if (!fastset_contains(s1, s2->dense[i])) {
			return 0;
		}
	}
	return (strict && (s1->size == s2->size)) ? 0 : 1;
}

int fastset_superset(struct fastset_s *s1, struct fastset_s *s2, int strict)
{
	return fastset_subset(s2, s1, strict);
}
