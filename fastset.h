/* fastset.h */
#ifndef _FASTSET_H_
#define _FASTSET_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct fastset_t;

struct fastset_t *fastset_create(size_t max_value);
void fastset_free(struct fastset_t *fastset);

void fastset_add(struct fastset_t *fastset, size_t value);
int fastset_contains(struct fastset_t *fastset, size_t value);
void fastset_remove(struct fastset_t *fastset, size_t value);
void fastset_clear(struct fastset_t *fastset);

void fastset_foreach(struct fastset_t *fastset, void (*pt2Func) (size_t each));

#ifdef __cplusplus
}
#endif

#endif /* _FASTSET_H_ */
