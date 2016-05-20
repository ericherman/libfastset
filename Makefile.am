lib_LTLIBRARIES=libfastset.la
libfastset_la_SOURCES=src/fastset.c

include_HEADERS=src/fastset.h

TESTS=$(check_PROGRAMS)
check_PROGRAMS=test-fastset
test_fastset_SOURCES=tests/test-fastset.c src/fastset.h
test_fastset_LDADD=libfastset.la -lecheck

ACLOCAL_AMFLAGS=-I m4 --install

CSTD_CFLAGS=-std=c89
#DEBUG_CFLAGS=-ggdb -O0
DEBUG_CFLAGS=-ggdb -O3 -DNDEBUG -Wno-unused-parameter
NOISY_CFLAGS=-Wall -Wextra -pedantic -Werror
AM_CFLAGS=$(CSTD_CFLAGS) $(DEBUG_CFLAGS) $(NOISY_CFLAGS)

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

valgrind: test-fastset
	valgrind ./test-fastset

tidy:
	patch -Np1 -i pre-tidy.diff
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T fastset_s \
		`find src tests -name *.h -o -name *.c`
	patch -Rp1 -i pre-tidy.diff

spotless:
	rm -rf `cat .gitignore`
	( cd src; rm -rf `cat ../.gitignore`; cd .. )
	( cd tests; rm -rf `cat ../.gitignore`; cd .. )
