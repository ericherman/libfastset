#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libfastset], [1.0.0], [eric@freesa.org])
AC_CONFIG_SRCDIR([src/fastset.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_USE_SYSTEM_EXTENSIONS

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([echeck], [check_size_t_m])

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AM_INIT_AUTOMAKE([subdir-objects -Werror -Wall])
AM_PROG_AR
LT_INIT

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
