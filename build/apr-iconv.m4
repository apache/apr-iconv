
dnl
dnl custom autoconf rules for APRICONV
dnl

dnl
dnl APU_FIND_APR: figure out where APR is located
dnl that a copy from apr-util...
dnl
AC_DEFUN(APU_FIND_APR,[

AC_MSG_CHECKING(for APR)
AC_ARG_WITH(apr,
[  --with-apr=DIR          path to APR source or the APR includes],
[
    if test "$withval" = "yes"; then
        AC_MSG_ERROR(You need to specify a directory with --with-apr)
    fi
    absdir="`cd $withval ; pwd`"
    if test -f "$absdir/apr_pools.h"; then
	APR_INCLUDES="$absdir"
    elif test -f "$absdir/include/apr_pools.h"; then
	APR_SOURCE_DIR="$absdir"
    fi
],[
    dnl see if we can find APR
    if test -f "$srcdir/apr/include/apr_pools.h"; then
	APR_SOURCE_DIR="$srcdir/apr"
    elif test -f "$srcdir/../apr/include/apr_pools.h"; then
	APR_SOURCE_DIR="`cd $srcdir/../apr ; pwd`"
    fi
])
if test -n "$APR_SOURCE_DIR"; then
    APR_INCLUDES="$APR_SOURCE_DIR/include"
fi
if test -z "$APR_INCLUDES"; then
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(APR could not be located. Please use the --with-apr option.)
fi
AC_MSG_RESULT($APR_INCLUDES)

AC_SUBST(APR_SOURCE_DIR)
])
