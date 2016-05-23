#include "test-fastset.h"

int test_fastset_intersect()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2, *result;

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

	result = fastset_intersect(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't intersect");
		exit(EXIT_FAILURE);
	}

	msg = "test_fastset_intersect (A)";
	failures += check_int_m(fastset_contains(result, 2), 1, msg);
	msg = "test_fastset_intersect (B)";
	failures += check_int_m(fastset_contains(result, 3), 1, msg);
	msg = "test_fastset_intersect (C)";
	failures += check_int_m(fastset_contains(result, 5), 1, msg);
	msg = "test_fastset_intersect (D)";
	failures += check_int_m(fastset_size(result), 3, msg);

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_intersect())
