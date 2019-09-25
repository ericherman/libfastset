/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test_fastset_create.c */
/* Copyright (C) 2016, 2018, 2019 Eric Herman <eric@freesa.org> */

#include "test-fastset.h"

int test_fastset_create()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs;
	size_t max_value = 42;

	msg = "test_fastset_create";
	fs = create_a_fastset(max_value, msg);

	msg = "test_fastset_create fastset_size";
	failures += check_size_t_m(fastset_size(fs), 0, msg);

	msg = "test_fastset_create fastset_max";
	failures += check_size_t_m(fastset_max(fs), max_value, msg);

	fastset_free(fs);
	return failures;
}

/* constant time function */
TEST_FASTSET_MAIN(test_fastset_create())
