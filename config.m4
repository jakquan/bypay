dnl $Id$
dnl config.m4 for extension bypay

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bypay, for bypay support,
dnl Make sure that the comment is aligned:
dnl [  --with-bypay             Include bypay support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(bypay, whether to enable bypay support,
dnl Make sure that the comment is aligned:
[  --enable-bypay           Enable bypay support])

if test "$PHP_BYPAY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-bypay -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/bypay.h"  # you most likely want to change this
  dnl if test -r $PHP_BYPAY/$SEARCH_FOR; then # path given as parameter
  dnl   BYPAY_DIR=$PHP_BYPAY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for bypay files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BYPAY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BYPAY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the bypay distribution])
  dnl fi

  dnl # --with-bypay -> add include path
  dnl PHP_ADD_INCLUDE($BYPAY_DIR/include)

  dnl # --with-bypay -> check for lib and symbol presence
  dnl LIBNAME=bypay # you may want to change this
  dnl LIBSYMBOL=bypay # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BYPAY_DIR/lib, BYPAY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BYPAYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong bypay lib version or lib not found])
  dnl ],[
  dnl   -L$BYPAY_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BYPAY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bypay, bypay.c, $ext_shared)
fi
