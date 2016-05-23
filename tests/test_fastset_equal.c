#include "test-fastset.h"

int test_fastset_equal()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2;

	msg = "test_fastset_equal";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	failures += check_int_m(fastset_equal(fs1, fs2), 1, msg);

	fastset_add(fs1, 1);
	msg = "test_fastset_equal [1],[]";
	failures += check_int_m(fastset_equal(fs1, fs2), 0, msg);

	fastset_add(fs2, 1);
	msg = "test_fastset_equal [1],[1]";
	failures += check_int_m(fastset_equal(fs1, fs2), 1, msg);

	fastset_add(fs2, 2);
	msg = "test_fastset_equal [1],[1,2]";
	failures += check_int_m(fastset_equal(fs1, fs2), 0, msg);

	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_equal())
