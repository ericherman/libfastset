#include "test-fastset.h"

int test_fastset_disjoint()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2;

	msg = "test_fastset_disjoint";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_add(fs1, 1);
	msg = "test_fastset_disjoint [1],[]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_add(fs2, 1);
	msg = "test_fastset_disjoint [1],[1]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 0, msg);

	fastset_add(fs2, 2);
	msg = "test_fastset_disjoint [1],[1,2]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 0, msg);

	fastset_clear(fs1);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	msg = "test_fastset_disjoint [3,4],[1,2]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_disjoint())
