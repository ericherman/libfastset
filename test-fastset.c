#include <stdio.h>
#include <echeck.h>

#include "fastset.h"

/* int main(int argc, char *argv[]) */
int main(void)
{
	int failures = 0;
	struct fastset_t *fs;
	size_t max_value = 100;

	fs = fastset_create(max_value);
	if (!fs) {
		fprintf(stderr, "woops, could not allocate fastset_t\n");
		return 1;
	}

	fastset_free(fs);

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
