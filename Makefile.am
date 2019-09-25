lib_LTLIBRARIES=libfastset.la

CSTD_CFLAGS=-std=c89
#DEBUG_CFLAGS=-ggdb -O0
DEBUG_CFLAGS=-ggdb -O3 -DNDEBUG -Wno-unused-parameter -fomit-frame-pointer
NOISY_CFLAGS=-Wall -Wextra -pedantic -Werror
AM_CFLAGS=$(CSTD_CFLAGS) $(DEBUG_CFLAGS) $(NOISY_CFLAGS) -pipe

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

libfastset_la_SOURCES=src/fastset.c

include_HEADERS=src/fastset.h

ACLOCAL_AMFLAGS=-I m4 --install
EXTRA_DIST=COPYING.GPL3

check_PROGRAMS=\
 test_fastset_create\
 test_fastset_add_size_contains\
 test_fastset_remove\
 test_fastset_clear\
 test_fastset_foreach\
 test_fastset_clone\
 test_fastset_intersect\
 test_fastset_union\
 test_fastset_minus\
 test_fastset_unique\
 test_fastset_equal\
 test_fastset_disjoint\
 test_fastset_subset_superset

TESTS=$(check_PROGRAMS)

valgrind: $(check_PROGRAMS)
	libtool --mode=execute valgrind -q ./test_fastset_create 1
	libtool --mode=execute valgrind -q ./test_fastset_add_size_contains 1
	libtool --mode=execute valgrind -q ./test_fastset_remove 1
	libtool --mode=execute valgrind -q ./test_fastset_clear 1
	libtool --mode=execute valgrind -q ./test_fastset_foreach 1
	libtool --mode=execute valgrind -q ./test_fastset_clone 1
	libtool --mode=execute valgrind -q ./test_fastset_intersect 1
	libtool --mode=execute valgrind -q ./test_fastset_union 1
	libtool --mode=execute valgrind -q ./test_fastset_minus 1
	libtool --mode=execute valgrind -q ./test_fastset_unique 1
	libtool --mode=execute valgrind -q ./test_fastset_equal 1
	libtool --mode=execute valgrind -q ./test_fastset_disjoint 1
	libtool --mode=execute valgrind -q ./test_fastset_subset_superset 1

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T fastset_s \
		`find src tests -name '*.h' -o -name '*.c'`

spotless:
	rm -rf `cat .gitignore | sed -e 's/#.*//'`
	pushd src && rm -rf `cat ../.gitignore | sed -e 's/#.*//'` && popd
	pushd tests && rm -rf `cat ../.gitignore | sed -e 's/#.*//'` && popd

COMMON_TEST_SOURCES=tests/echeck.h tests/echeck.c \
	tests/test-fastset.h src/fastset.h
COMMON_TEST_LDADD=libfastset.la

test_fastset_create_SOURCES=tests/test_fastset_create.c\
 $(COMMON_TEST_SOURCES)
test_fastset_create_LDADD=$(COMMON_TEST_LDADD)

test_fastset_add_size_contains_SOURCES=tests/test_fastset_add_size_contains.c\
 $(COMMON_TEST_SOURCES)
test_fastset_add_size_contains_LDADD=$(COMMON_TEST_LDADD)

test_fastset_remove_SOURCES=tests/test_fastset_remove.c\
 $(COMMON_TEST_SOURCES)
test_fastset_remove_LDADD=$(COMMON_TEST_LDADD)

test_fastset_clear_SOURCES=tests/test_fastset_clear.c\
 $(COMMON_TEST_SOURCES)
test_fastset_clear_LDADD=$(COMMON_TEST_LDADD)

test_fastset_foreach_SOURCES=tests/test_fastset_foreach.c\
 $(COMMON_TEST_SOURCES)
test_fastset_foreach_LDADD=$(COMMON_TEST_LDADD)

test_fastset_clone_SOURCES=tests/test_fastset_clone.c\
 $(COMMON_TEST_SOURCES)
test_fastset_clone_LDADD=$(COMMON_TEST_LDADD)

test_fastset_intersect_SOURCES=tests/test_fastset_intersect.c\
 $(COMMON_TEST_SOURCES)
test_fastset_intersect_LDADD=$(COMMON_TEST_LDADD)

test_fastset_union_SOURCES=tests/test_fastset_union.c\
 $(COMMON_TEST_SOURCES)
test_fastset_union_LDADD=$(COMMON_TEST_LDADD)

test_fastset_minus_SOURCES=tests/test_fastset_minus.c\
 $(COMMON_TEST_SOURCES)
test_fastset_minus_LDADD=$(COMMON_TEST_LDADD)

test_fastset_unique_SOURCES=tests/test_fastset_unique.c\
 $(COMMON_TEST_SOURCES)
test_fastset_unique_LDADD=$(COMMON_TEST_LDADD)

test_fastset_equal_SOURCES=tests/test_fastset_equal.c\
 $(COMMON_TEST_SOURCES)
test_fastset_equal_LDADD=$(COMMON_TEST_LDADD)

test_fastset_disjoint_SOURCES=tests/test_fastset_disjoint.c\
 $(COMMON_TEST_SOURCES)
test_fastset_disjoint_LDADD=$(COMMON_TEST_LDADD)

test_fastset_subset_superset_SOURCES=tests/test_fastset_subset_superset.c\
 $(COMMON_TEST_SOURCES)
test_fastset_subset_superset_LDADD=$(COMMON_TEST_LDADD)

