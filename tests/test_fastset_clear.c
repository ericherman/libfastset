/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test_fastset_clear.c */
/* Copyright (C) 2016, 2018, 2019 Eric Herman <eric@freesa.org> */

#include "test-fastset.h"

int test_fastset_clear()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs;

	msg = "test_fastset_clear";
	fs = create_a_fastset(0, msg);

	fastset_add(fs, 5);
	fastset_add(fs, 9);
	fastset_add(fs, 4211);
	fastset_add(fs, 2);

	msg = "test_fastset_clear fastset_size (A)";
	failures += check_size_t_m(fastset_size(fs), 4, msg);

	fastset_clear(fs);

	msg = "test_fastset_clear fastset_size (B)";
	failures += check_size_t_m(fastset_size(fs), 0, msg);

	fastset_free(fs);
	return failures;
}

/* constant time function */
TEST_FASTSET_MAIN(test_fastset_clear())
