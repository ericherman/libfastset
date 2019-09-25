/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* fastset.h */
/* Copyright (C) 2016, 2018, 2019 Eric Herman <eric@freesa.org> */
#ifndef FASTSET_H
#define FASTSET_H

#include <stddef.h>

#ifdef __cplusplus
#define Fastset_begin_C_functions extern "C" {
#define Fastset_end_C_functions }
#else
#define Fastset_begin_C_functions
#define Fastset_end_C_functions
#endif

struct fastset_s;

Fastset_begin_C_functions
#undef Fastset_begin_C_functions
/* ------------ */
/* constructor  */
/* ------------ */
/*
 * The "max_value" argument is the largest legal value this set will be
 * prepared to handle.
 *
 * The "zero_mem" argument can be enabled to replace malloc calls with calloc.
 * This is safe to leave at zero, however tools like valgrind will complain
 * unless memory is initialized before being read.
 *
 * Mmemory allocated is approximately: 2 * max_value * sizeof(size_t).
 */
struct fastset_s *fastset_create(size_t max_value, int zero_mem);

/* ----------- */
/* destructor  */
/* ----------- */
/* must be called for destruction to avoid leaking memory */
void fastset_free(struct fastset_s *fastset);

/* ------------------------ */
/* constant time operations */
/* ------------------------ */
/* fastset_add will return 0 if the value is too large for the set */
int fastset_add(struct fastset_s *fastset, size_t value);

/* fastset_contains returns 0 if the value is not contained in the set */
int fastset_contains(struct fastset_s *fastset, size_t value);

/*
 * The fastset_remove operation removes the value from the set.
 * Value removal changes the iteration order.
 */
void fastset_remove(struct fastset_s *fastset, size_t value);

/* fastset_size returns the current number of values in the set */
size_t fastset_size(struct fastset_s *fastset);

/* fastset_clear resets to an empty set */
void fastset_clear(struct fastset_s *fastset);

/* ---------------- */
/* O(n) operations  */
/* ---------------- */
/*
 * If no fastset_remove() operations have occured, iteration will
 * be in element insertion order.
 */
void fastset_foreach(struct fastset_s *fastset,
		     void (*func)(size_t each, void *arg), void *arg);

/* allocates a new set which is a deep-copy of this set */
struct fastset_s *fastset_clone(struct fastset_s *fastset);

/* allocates a new set which contains the intersection of the sets */
struct fastset_s *fastset_intersect(struct fastset_s *s1, struct fastset_s *s2);

/* allocates a new set which contains the union of the sets */
struct fastset_s *fastset_union(struct fastset_s *s1, struct fastset_s *s2);

/* allocates a new set which contains the values of s1 which are not in s2 */
struct fastset_s *fastset_minus(struct fastset_s *s1, struct fastset_s *s2);

/* allocates a new set which contains the of s1 and s2 which are not in both */
struct fastset_s *fastset_unique(struct fastset_s *s1, struct fastset_s *s2);

/* return 1 if sets contain same values, otherwise returns 0 */
int fastset_equal(struct fastset_s *s1, struct fastset_s *s2);

/* return 1 if sets contain none of the same values,
 * otherwise returns 0 */
int fastset_disjoint(struct fastset_s *s1, struct fastset_s *s2);

/* return 1 if all values of s2 are present in s1,
 * int strict ensures sets are not equal,
 * otherwise returns 0 */
int fastset_subset(struct fastset_s *s1, struct fastset_s *s2, int strict);

/* return 1 if all values of s1 are present in s2,
 * if strict ensures sets are not equal,
 * otherwise returns 0 */
int fastset_superset(struct fastset_s *s1, struct fastset_s *s2, int strict);

/* ----- */
/* misc  */
/* ----- */
/* the maxium legal value this set is prepared to handle */
size_t fastset_max(struct fastset_s *fastset);

Fastset_end_C_functions
#undef Fastset_end_C_functions
#endif /* FASTSET_H */
