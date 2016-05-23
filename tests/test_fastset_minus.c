#include "test-fastset.h"

int test_fastset_minus()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2, *result;
	size_t i;
	char buf[80];
	size_t expected[4] = { 0, 1, 4, 6 };

	msg = "test_fastset_minus";
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

	result = fastset_minus(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't minus");
		exit(EXIT_FAILURE);
	}

	msg = "test_fastset_minus size";
	failures += check_size_t_m(fastset_size(result), 4, msg);

	for (i = 0; i < 4; i++) {
		sprintf(buf, "test_fastset_minus (%lu)", (unsigned long)i);
		failures +=
		    check_int_m(fastset_contains(result, expected[i]), 1, msg);
	}

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_minus())
