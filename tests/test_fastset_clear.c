/* test_fastset_clear.c
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
