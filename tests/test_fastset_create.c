/* test_fastset_create.c
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
