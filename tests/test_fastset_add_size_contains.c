/* test_fastset_add_size_contains.c
   Copyright (C) 2016, 2018 Eric Herman <eric@freesa.org>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

	https://www.gnu.org/licenses/lgpl-3.0.txt
	https://www.gnu.org/licenses/gpl-3.0.txt
 */
#include "test-fastset.h"

int test_fastset_add_size_contains()
{
	int failures = 0;
	char *msg, buf[80];
	struct fastset_s *fs;
	size_t i, max_value = 35;

	msg = "test_fastset_add_size_contains";
	fs = create_a_fastset(max_value, msg);

	msg = "test_fastset_add_size_contains (A)";
	failures += check_size_t_m(fastset_max(fs), max_value, msg);

	/* adding */
	msg = "test_fastset_add_size_contains (B)";
	failures += check_int_m(fastset_add(fs, 3), 1, msg);
	msg = "test_fastset_add_size_contains (C)";
	failures += check_int_m(fastset_add(fs, max_value + 1), 0, msg);

	msg = "test_fastset_add_size_contains (D)";
	failures += check_int_m(fastset_add(fs, 3), 1, msg);
	msg = "test_fastset_add_size_contains (E)";
	failures += check_int_m(fastset_add(fs, 7), 1, msg);
	msg = "test_fastset_add_size_contains (F)";
	failures += check_int_m(fastset_add(fs, 1), 1, msg);

	/* size */
	msg = "test_fastset_add_size_contains (G)";
	failures += check_size_t_m(fastset_size(fs), 3, msg);
	msg = "test_fastset_add_size_contains (H)";
	failures += check_size_t_m(fastset_max(fs), max_value, msg);

	/* contains */
	msg = "test_fastset_add_size_contains (I)";
	failures += check_int_m(fastset_contains(fs, 1), 1, msg);
	msg = "test_fastset_add_size_contains (J)";
	failures += check_int_m(fastset_contains(fs, 2), 0, msg);
	msg = "test_fastset_add_size_contains (K)";
	failures += check_int_m(fastset_contains(fs, 3), 1, msg);
	msg = "test_fastset_add_size_contains (L)";
	failures += check_int_m(fastset_contains(fs, 4), 0, msg);
	msg = "test_fastset_add_size_contains (M)";
	failures += check_int_m(fastset_contains(fs, 7), 1, msg);
	msg = "test_fastset_add_size_contains (N)";
	failures += check_int_m(fastset_contains(fs, 8), 0, msg);

	for (i = max_value + 1; i < max_value + 100000; i++) {
		sprintf(buf, "test_fastset_contains (%lu)", (unsigned long)i);
		failures += check_int_m(fastset_contains(fs, i), 0, msg);
	}

	fastset_free(fs);
	return failures;
}

/* constant time function */
TEST_FASTSET_MAIN(test_fastset_add_size_contains())
