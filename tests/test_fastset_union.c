#include "test-fastset.h"

int test_fastset_union()
{
	int failures = 0;
	char *msg;
	char buf[80];
	struct fastset_s *fs1, *fs2, *result;
	size_t i;

	msg = "test_fastset_intersect";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	fastset_add(fs1, 0);
	fastset_add(fs1, 1);
	fastset_add(fs1, 2);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	fastset_add(fs1, 5);
	fastset_add(fs1, 6);

	fastset_add(fs2, 2);
	fastset_add(fs2, 3);
	fastset_add(fs2, 5);
	fastset_add(fs2, 7);

	result = fastset_union(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't union");
		exit(EXIT_FAILURE);
	}
	msg = "test_fastset_union size";
	failures += check_size_t_m(fastset_size(result), 8, msg);

	for (i = 0; i < 8; i++) {
		sprintf(buf, "test_fastset_union (%lu)", (unsigned long)i);
		failures += check_int_m(fastset_contains(result, i), 1, msg);
	}

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_union())
