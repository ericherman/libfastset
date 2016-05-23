#include "test-fastset.h"

int test_fastset_clone(int full)
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs, *clone;

	msg = "test_fastset_clone";
	fs = create_a_fastset(full ? 3 : 0, msg);

	fastset_add(fs, 0);
	fastset_add(fs, 1);
	fastset_add(fs, 2);
	fastset_add(fs, 3);

	clone = fastset_clone(fs);

	msg = "test_fastset_clone (A)";
	failures += check_size_t_m(fastset_max(fs), fastset_max(clone), msg);

	msg = "test_fastset_clone (B)";
	failures += check_size_t_m(fastset_size(fs), fastset_size(clone), msg);

	msg = "test_fastset_clone (C)";
	failures += check_int_m(fastset_contains(clone, 0), 1, msg);
	msg = "test_fastset_clone (D)";
	failures += check_int_m(fastset_contains(clone, 1), 1, msg);
	msg = "test_fastset_clone (E)";
	failures += check_int_m(fastset_contains(clone, 2), 1, msg);
	msg = "test_fastset_clone (F)";
	failures += check_int_m(fastset_contains(clone, 3), 1, msg);

	fastset_remove(clone, 2);
	msg = "test_fastset_clone (G)";
	failures +=
	    check_size_t_m(fastset_size(fs) - 1, fastset_size(clone), msg);
	msg = "test_fastset_clone (H)";
	failures += check_int_m(fastset_contains(fs, 2), 1, msg);

	fastset_free(clone);
	fastset_free(fs);
	return failures;
}

TEST_FASTSET_MAIN2(test_fastset_clone(0), test_fastset_clone(1))
