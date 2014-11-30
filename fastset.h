/* fastset.h */
#ifndef _FASTSET_H_
#define _FASTSET_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct fastset_t;

/* ------------ */
/* constructor  */
/* ------------ */
/*
 * The "max_value" argument is the largest legal value this set will be
 * prepared to handle.
 *
 * Mmemory allocated is approximately: 2 * max_value * sizeof(size_t).
 */
struct fastset_t *fastset_create(size_t max_value);

/* ----------- */
/* destructor  */
/* ----------- */
/* must be called for destruction to avoid leaking memory */
void fastset_free(struct fastset_t *fastset);

/* ------------------------ */
/* constant time operations */
/* ------------------------ */
/* fastset_add will return 0 if the value is too large for the set */
int fastset_add(struct fastset_t *fastset, size_t value);

/* fastset_contains returns 0 if the value is not contained in the set */
int fastset_contains(struct fastset_t *fastset, size_t value);

/*
 * The fastset_remove operation removes the value from the set.
 * Value removal changes the iteration order.
 */
void fastset_remove(struct fastset_t *fastset, size_t value);

/* fastset_size returns the current number of values in the set */
size_t fastset_size(struct fastset_t *fastset);

/* fastset_clear resets to an empty set */
void fastset_clear(struct fastset_t *fastset);

/* ---------------- */
/* O(N) operations  */
/* ---------------- */
/*
 * If no fastset_remove() operations have occured, iteration will
 * be in element insertion order.
 */
void fastset_foreach(struct fastset_t *fastset,
		     void (*func) (size_t each, void *arg), void *arg);

/* allocates a new set which is a deep-copy of this set */
struct fastset_t *fastset_clone(struct fastset_t *fastset);

/* allocates a new set which contains the intersection of the sets */
struct fastset_t *fastset_intersect(struct fastset_t *s1, struct fastset_t *s2);

/* ----- */
/* misc  */
/* ----- */
/* the maxium legal value this set is prepared to handle */
size_t fastset_max(struct fastset_t *fastset);

#ifdef __cplusplus
}
#endif

#endif /* _FASTSET_H_ */
