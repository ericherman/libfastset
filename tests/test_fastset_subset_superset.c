#include "test-fastset.h"

int test_fastset_subset_superset()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2;

	msg = "test_fastset_subset";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	msg = "test_fastset_subset [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);

	fastset_add(fs1, 1);
	msg = "test_fastset_subset [1],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [1],[]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_subset strict [1],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 1, msg);
	msg = "test_fastset_superset strict [1],[]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_subset [],[1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 0), 0, msg);
	msg = "test_fastset_superset [],[1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 0), 1, msg);
	msg = "test_fastset_subset strict [],[1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 1), 0, msg);
	msg = "test_fastset_superset strict [],[1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 1), 1, msg);

	fastset_add(fs2, 1);
	msg = "test_fastset_subset [1],[1]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [1],[1]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [1],[1]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [1],[1]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);

	fastset_add(fs2, 2);
	msg = "test_fastset_subset [1],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_superset [1],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [1],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [1],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 1, msg);
	msg = "test_fastset_subset [1,2], [1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 0), 1, msg);
	msg = "test_fastset_superset [1,2], [1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 0), 0, msg);
	msg = "test_fastset_subset strict [1,2], [1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 1), 1, msg);
	msg = "test_fastset_superset strict [1,2], [1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 1), 0, msg);

	fastset_clear(fs1);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	msg = "test_fastset_subset [3,4],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_superset [3,4],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_subset strict [3,4],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [3,4],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);

	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_subset_superset())
