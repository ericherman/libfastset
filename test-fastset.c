#include <stdio.h>
#include <echeck.h>

#include "fastset.h"

/* int main(int argc, char *argv[]) */
int main(void)
{
	int failures = 0;
	struct fastset_t *fs;
	size_t max_value = 1024 * 1024;

	fs = fastset_create(max_value);
	if (!fs) {
		fprintf(stderr, "woops, could not allocate fastset_t\n");
		return 1;
	}

	failures += check_size_t(fastset_size(fs), 0);
	failures += check_size_t(fastset_max(fs), max_value);

	failures += check_int(fastset_add(fs, 3), 1);
	failures += check_int(fastset_add(fs, max_value + 1), 0);
	fastset_add(fs, 7);
	fastset_add(fs, 1);
	fastset_add(fs, 3);

	failures += check_size_t(fastset_size(fs), 3);
	failures += check_size_t(fastset_max(fs), max_value);

	failures += check_int(fastset_contains(fs, 1), 1);
	failures += check_int(fastset_contains(fs, 2), 0);
	failures += check_int(fastset_contains(fs, 3), 1);
	failures += check_int(fastset_contains(fs, 4), 0);
	failures += check_int(fastset_contains(fs, 7), 1);
	failures += check_int(fastset_contains(fs, 8), 0);

	fastset_remove(fs, 3);

	failures += check_size_t(fastset_size(fs), 2);
	failures += check_int(fastset_contains(fs, 1), 1);
	failures += check_int(fastset_contains(fs, 3), 0);
	failures += check_int(fastset_contains(fs, 7), 1);

	fastset_clear(fs);
	failures += check_size_t(fastset_size(fs), 0);
	failures += check_size_t(fastset_max(fs), max_value);

	fastset_free(fs);

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
