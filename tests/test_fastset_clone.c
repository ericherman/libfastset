/* test_fastset_clone.c
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
