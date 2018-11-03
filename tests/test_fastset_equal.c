/* test_fastset_equal.c
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
