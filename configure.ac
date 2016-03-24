AC_INIT([libuhp], [1.0], [franck.rupin@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 subdir-objects -Wall -Werror foreign])
AC_PROG_CC

AM_PROG_AR([act-if-fail])
LT_INIT

PKG_CHECK_MODULES([libevent], [libevent])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([crypto], [libcrypto])
PKG_CHECK_MODULES([ssl], [libssl])

AC_CONFIG_SRCDIR([src/test.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT