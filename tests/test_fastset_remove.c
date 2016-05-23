#include "test-fastset.h"

int test_fastset_remove()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs;

	msg = "test_fastset_remove";
	fs = create_a_fastset(0, msg);

	fastset_add(fs, 1);
	fastset_add(fs, 3);
	fastset_add(fs, 7);

	fastset_remove(fs, 3);

	msg = "test_fastset_remove fastset_size";
	failures += check_size_t_m(fastset_size(fs), 2, msg);

	msg = "test_fastset_remove fastset_contains (A)";
	failures += check_int_m(fastset_contains(fs, 1), 1, msg);
	msg = "test_fastset_remove fastset_contains (B)";
	failures += check_int_m(fastset_contains(fs, 3), 0, msg);
	msg = "test_fastset_remove fastset_contains (C)";
	failures += check_int_m(fastset_contains(fs, 7), 1, msg);

	fastset_free(fs);
	return failures;
}

/* constant time function */
TEST_FASTSET_MAIN(test_fastset_remove())
