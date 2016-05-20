#include <stdio.h>
#include <echeck.h>

#include "../src/fastset.h"

int global_make_valgrind_happy = 0;

struct param_s {
	size_t values[10];
	size_t filled;
};

void fill_array(size_t each, void *arg)
{
	struct param_s *param = (struct param_s *)arg;
	param->values[param->filled++] = each;
}

struct fastset_s *create_a_fastset(size_t max_value, char *msg)
{
	struct fastset_s *fs;

	if (max_value == 0) {
		max_value = 1024 * 1024;
	};

	fs = fastset_create(max_value, global_make_valgrind_happy);
	if (!fs) {
		fprintf(stderr, "%s could not allocate fastset_s (%lu)\n", msg,
			(unsigned long)max_value);
		exit(EXIT_FAILURE);
	}

	return fs;
}

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

int test_fastset_remove()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs;

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

int test_fastset_intersect()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2, *result;

	msg = "test_fastset_intersect";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	fastset_add(fs1, 0);
	fastset_add(fs1, 1);
	fastset_add(fs1, 2);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	fastset_add(fs1, 5);
	fastset_add(fs1, 6);

	fastset_add(fs2, 2);
	fastset_add(fs2, 3);
	fastset_add(fs2, 5);
	fastset_add(fs2, 7);

	result = fastset_intersect(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't intersect");
		exit(EXIT_FAILURE);
	}

	msg = "test_fastset_intersect (A)";
	failures += check_int_m(fastset_contains(result, 2), 1, msg);
	msg = "test_fastset_intersect (B)";
	failures += check_int_m(fastset_contains(result, 3), 1, msg);
	msg = "test_fastset_intersect (C)";
	failures += check_int_m(fastset_contains(result, 5), 1, msg);
	msg = "test_fastset_intersect (D)";
	failures += check_int_m(fastset_size(result), 3, msg);

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

int test_fastset_union()
{
	int failures = 0;
	char *msg;
	char buf[80];
	struct fastset_s *fs1, *fs2, *result;
	size_t i;

	msg = "test_fastset_intersect";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	fastset_add(fs1, 0);
	fastset_add(fs1, 1);
	fastset_add(fs1, 2);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	fastset_add(fs1, 5);
	fastset_add(fs1, 6);

	fastset_add(fs2, 2);
	fastset_add(fs2, 3);
	fastset_add(fs2, 5);
	fastset_add(fs2, 7);

	result = fastset_union(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't union");
		exit(EXIT_FAILURE);
	}
	msg = "test_fastset_union size";
	failures += check_size_t_m(fastset_size(result), 8, msg);

	for (i = 0; i < 8; i++) {
		sprintf(buf, "test_fastset_union (%lu)", (unsigned long)i);
		failures += check_int_m(fastset_contains(result, i), 1, msg);
	}

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

int test_fastset_minus()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2, *result;
	size_t i;
	char buf[80];
	size_t expected[4] = { 0, 1, 4, 6 };

	msg = "test_fastset_minus";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	fastset_add(fs1, 0);
	fastset_add(fs1, 1);
	fastset_add(fs1, 2);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	fastset_add(fs1, 5);
	fastset_add(fs1, 6);

	fastset_add(fs2, 2);
	fastset_add(fs2, 3);
	fastset_add(fs2, 5);
	fastset_add(fs2, 7);

	result = fastset_minus(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't minus");
		exit(EXIT_FAILURE);
	}

	msg = "test_fastset_minus size";
	failures += check_size_t_m(fastset_size(result), 4, msg);

	for (i = 0; i < 4; i++) {
		sprintf(buf, "test_fastset_minus (%lu)", (unsigned long)i);
		failures +=
		    check_int_m(fastset_contains(result, expected[i]), 1, msg);
	}

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

int test_fastset_unique()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2, *result;
	size_t i;
	char buf[80];
	size_t expected[5] = { 0, 1, 4, 6, 7 };

	msg = "test_fastset_minus";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	fastset_add(fs1, 0);
	fastset_add(fs1, 1);
	fastset_add(fs1, 2);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	fastset_add(fs1, 5);
	fastset_add(fs1, 6);

	fastset_add(fs2, 2);
	fastset_add(fs2, 3);
	fastset_add(fs2, 5);
	fastset_add(fs2, 7);

	result = fastset_unique(fs1, fs2);
	if (!result) {
		fprintf(stderr, "whoah, couldn't unique");
		exit(EXIT_FAILURE);
	}
	msg = "test_fastset_unique size";
	failures += check_size_t_m(fastset_size(result), 5, msg);

	for (i = 0; i < 5; i++) {
		sprintf(buf, "test_fastset_unique (%lu)", (unsigned long)i);
		failures +=
		    check_int_m(fastset_contains(result, expected[i]), 1, msg);
	}

	fastset_free(result);
	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

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

int test_fastset_disjoint()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2;

	msg = "test_fastset_disjoint";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_add(fs1, 1);
	msg = "test_fastset_disjoint [1],[]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_add(fs2, 1);
	msg = "test_fastset_disjoint [1],[1]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 0, msg);

	fastset_add(fs2, 2);
	msg = "test_fastset_disjoint [1],[1,2]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 0, msg);

	fastset_clear(fs1);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	msg = "test_fastset_disjoint [3,4],[1,2]";
	failures += check_int_m(fastset_disjoint(fs1, fs2), 1, msg);

	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

int test_fastset_subset_superset()
{
	int failures = 0;
	char *msg;
	struct fastset_s *fs1, *fs2;

	msg = "test_fastset_subset";
	fs1 = create_a_fastset(10, msg);
	fs2 = create_a_fastset(10, msg);

	msg = "test_fastset_subset [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);

	fastset_add(fs1, 1);
	msg = "test_fastset_subset [1],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [1],[]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_subset strict [1],[]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 1, msg);
	msg = "test_fastset_superset strict [1],[]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_subset [],[1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 0), 0, msg);
	msg = "test_fastset_superset [],[1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 0), 1, msg);
	msg = "test_fastset_subset strict [],[1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 1), 0, msg);
	msg = "test_fastset_superset strict [],[1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 1), 1, msg);

	fastset_add(fs2, 1);
	msg = "test_fastset_subset [1],[1]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_superset [1],[1]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [1],[1]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [1],[1]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);

	fastset_add(fs2, 2);
	msg = "test_fastset_subset [1],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_superset [1],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 1, msg);
	msg = "test_fastset_subset strict [1],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [1],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 1, msg);
	msg = "test_fastset_subset [1,2], [1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 0), 1, msg);
	msg = "test_fastset_superset [1,2], [1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 0), 0, msg);
	msg = "test_fastset_subset strict [1,2], [1]";
	failures += check_int_m(fastset_subset(fs2, fs1, 1), 1, msg);
	msg = "test_fastset_superset strict [1,2], [1]";
	failures += check_int_m(fastset_superset(fs2, fs1, 1), 0, msg);

	fastset_clear(fs1);
	fastset_add(fs1, 3);
	fastset_add(fs1, 4);
	msg = "test_fastset_subset [3,4],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_superset [3,4],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 0), 0, msg);
	msg = "test_fastset_subset strict [3,4],[1,2]";
	failures += check_int_m(fastset_subset(fs1, fs2, 1), 0, msg);
	msg = "test_fastset_superset strict [3,4],[1,2]";
	failures += check_int_m(fastset_superset(fs1, fs2, 1), 0, msg);

	fastset_free(fs2);
	fastset_free(fs1);
	return failures;
}

int main(int argc, char *argv[])
{
	int failures = 0;

	if (argc > 1) {
		global_make_valgrind_happy = atoi(argv[1]);
	}

	/* constant time functions */
	failures += test_fastset_create();
	failures += test_fastset_add_size_contains();
	failures += test_fastset_remove();
	failures += test_fastset_clear();

	/* O(n) functions */
	failures += test_fastset_foreach();
	failures += test_fastset_clone(0);
	failures += test_fastset_clone(1);
	failures += test_fastset_intersect();
	failures += test_fastset_union();
	failures += test_fastset_minus();
	failures += test_fastset_unique();
	failures += test_fastset_equal();
	failures += test_fastset_disjoint();
	failures += test_fastset_subset_superset();

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
