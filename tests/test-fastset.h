/* test-fastset.h
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
#include <stdio.h>
#include <echeck.h>

#include "../src/fastset.h"

int global_make_valgrind_happy = 0;

struct fastset_s *create_a_fastset(size_t max_value, char *msg)
{
	struct fastset_s *fs;
	int zero_memory_before_use;

	if (max_value == 0) {
		max_value = 1024 * 1024;
	};

	zero_memory_before_use = global_make_valgrind_happy;
	fs = fastset_create(max_value, zero_memory_before_use);
	if (!fs) {
		fprintf(stderr, "%s could not allocate fastset_s (%lu)\n", msg,
			(unsigned long)max_value);
		exit(EXIT_FAILURE);
	}

	return fs;
}

#define TEST_FASTSET_MAIN(func) \
int main(int argc, char **argv) \
{ \
        int failures = 0; \
        if (argc > 1) { \
                global_make_valgrind_happy = atoi(argv[1]); \
        } \
        failures += func; \
        if (failures) { \
                fprintf(stderr, "%d failures in %s \n", failures, __FILE__);\
        } \
        return failures ? 1 : 0; \
}

#define TEST_FASTSET_MAIN2(func1, func2) \
int main(int argc, char **argv) \
{ \
        int failures = 0; \
        if (argc > 1) { \
                global_make_valgrind_happy = atoi(argv[1]); \
        } \
        failures += func1; \
        failures += func2; \
        if (failures) { \
                fprintf(stderr, "%d failures in %s \n", failures, __FILE__);\
        } \
        return failures ? 1 : 0; \
}
