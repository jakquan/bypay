/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_BYPAY_H
#define PHP_BYPAY_H

extern zend_module_entry bypay_module_entry;
#define phpext_bypay_ptr &bypay_module_entry

#define PHP_BYPAY_VERSION "0.2" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_BYPAY_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BYPAY_API __attribute__ ((visibility("default")))
#else
#	define PHP_BYPAY_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(bypay);
PHP_MSHUTDOWN_FUNCTION(bypay);
PHP_RINIT_FUNCTION(bypay);
PHP_RSHUTDOWN_FUNCTION(bypay);
PHP_MINFO_FUNCTION(bypay);

PHP_FUNCTION(bypay_version);
PHP_FUNCTION(bypay_cfg_get);

ZEND_BEGIN_MODULE_GLOBALS(bypay)
	char *cfg_path;
ZEND_END_MODULE_GLOBALS(bypay)

ZEND_EXTERN_MODULE_GLOBALS(bypay)

/* In every utility function you add that needs to use variables 
   in php_bypay_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BYPAY_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BYPAY_G(v) TSRMG(bypay_globals_id, zend_bypay_globals *, v)
#else
#define BYPAY_G(v) (bypay_globals.v)
#endif

#endif	/* PHP_BYPAY_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
