/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test_fastset_foreach.c */
/* Copyright (C) 2016, 2018, 2019 Eric Herman <eric@freesa.org> */

#include "test-fastset.h"

struct param_s {
	size_t values[10];
	size_t filled;
};

void fill_array(size_t each, void *arg)
{
	struct param_s *param = (struct param_s *)arg;
	param->values[param->filled++] = each;
}

int test_fastset_foreach()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs;
	size_t i;
	struct param_s *params;
	size_t expected[3] = { 3, 7, 1 };

	params = calloc(1, sizeof(struct param_s));
	if (!params) {
		fprintf(stderr, "woops, could not allocate param_s\n");
		return 1;
	}

	msg = "test_fastset_foreach";
	fs = create_a_fastset(0, msg);

	for (i = 0; i < 3; i++) {
		fastset_add(fs, expected[i]);
	}

	fastset_foreach(fs, fill_array, (void *)params);

	failures +=
	    check_byte_array((unsigned char *)expected, sizeof(size_t) * 3,
			     (unsigned char *)params->values,
			     sizeof(size_t) * params->filled);

	free(params);
	fastset_free(fs);
	return failures;
}

TEST_FASTSET_MAIN(test_fastset_foreach())
