#include <stdio.h>
#include <echeck.h>

#include "fastset.h"

struct param_t {
	size_t values[10];
	size_t filled;
} param_t;

void fill_array(size_t each, void *arg)
{
	struct param_t *param = (struct param_t *)arg;
	param->values[param->filled++] = each;
}

struct fastset_t *create_a_fastset(size_t max_value, char *msg)
{
	struct fastset_t *fs;

	if (max_value == 0) {
		max_value = 1024 * 1024;
	};

	fs = fastset_create(max_value);
	if (!fs) {
		fprintf(stderr, "%s could not allocate fastset_t (%lu)\n", msg,
			(unsigned long)max_value);
		exit(EXIT_FAILURE);
	}

	return fs;
}

int test_fastset_create()
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs;
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

int test_fastset_add_size_contains()
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs;
	size_t max_value = 35;

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

	fastset_free(fs);
	return failures;
}

int test_fastset_remove()
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs;

	msg = "test_fastset_remove";
	fs = create_a_fastset(0, msg);

	fastset_add(fs, 1);
	fastset_add(fs, 3);
	fastset_add(fs, 7);

	fastset_remove(fs, 3);

	msg = "test_fastset_remove fastset_size";
	failures += check_size_t_m(fastset_size(fs), 2, msg);

	msg = "test_fastset_remove fastset_contains (A)";
	failures += check_int_m(fastset_contains(fs, 1), 1, msg);
	msg = "test_fastset_remove fastset_contains (B)";
	failures += check_int_m(fastset_contains(fs, 3), 0, msg);
	msg = "test_fastset_remove fastset_contains (C)";
	failures += check_int_m(fastset_contains(fs, 7), 1, msg);

	fastset_free(fs);
	return failures;
}

int test_fastset_clear()
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs;

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

int test_fastset_foreach()
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs;
	size_t i;
	struct param_t *params;
	size_t expected[3] = { 3, 7, 1 };

	params = malloc(sizeof(struct param_t));
	if (!params) {
		fprintf(stderr, "woops, could not allocate param_t\n");
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

int test_fastset_clone(int full)
{
	int failures = 0;
	char *msg;
	struct fastset_t *fs, *clone;

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

/* int main(int argc, char *argv[]) */
int main(void)
{
	int failures = 0;

	failures += test_fastset_create();
	failures += test_fastset_add_size_contains();
	failures += test_fastset_remove();
	failures += test_fastset_clear();
	failures += test_fastset_foreach();
	failures += test_fastset_clone(0);
	failures += test_fastset_clone(1);

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
