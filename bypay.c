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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bypay.h"

/* If you declare any globals in php_bypay.h uncomment this:
   ZEND_DECLARE_MODULE_GLOBALS(bypay)
   */

/* True global resources - no need for thread safety here */
static int le_bypay;

/* {{{ bypay_functions[]
 *
 * Every user visible function must have an entry in bypay_functions[].
 */
const zend_function_entry bypay_functions[] = {
    PHP_FE(bypay_version, NULL)
    PHP_FE(bypay_cfg_get, NULL)
    PHP_FE_END
};
/* }}} */

/* {{{ bypay_module_entry
*/
zend_module_entry bypay_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  "bypay",
  bypay_functions,
  PHP_MINIT(bypay),
  PHP_MSHUTDOWN(bypay),
  PHP_RINIT(bypay),		/* Replace with NULL if there's nothing to do at request start */
  PHP_RSHUTDOWN(bypay),	/* Replace with NULL if there's nothing to do at request end */
  PHP_MINFO(bypay),
#if ZEND_MODULE_API_NO >= 20010901
  PHP_BYPAY_VERSION,
#endif
  STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BYPAY
ZEND_GET_MODULE(bypay)
#endif

ZEND_DECLARE_MODULE_GLOBALS(bypay)
  /* {{{ php_bypay_init_globals
  */
static void php_bypay_init_globals(zend_bypay_globals *bypay_globals TSRMLS_DC)
{
  bypay_globals->cfg_path = NULL;
}
/* }}} */

static void php_bypay_shutdown_globals(zend_bypay_globals* bypay_globals TSRMLS_DC) 
{
  /* nothing to do */
}

/* {{{ PHP_INI
*/
PHP_INI_BEGIN()
  STD_PHP_INI_ENTRY("bypay.cfg_path", (char*)NULL, PHP_INI_SYSTEM, OnUpdateString, cfg_path, zend_bypay_globals, bypay_globals)
PHP_INI_END()
  /* }}} */

  /* {{{ PHP_MINIT_FUNCTION
  */
PHP_MINIT_FUNCTION(bypay)
{
  ZEND_INIT_MODULE_GLOBALS(bypay, php_bypay_init_globals, php_bypay_shutdown_globals);
  REGISTER_INI_ENTRIES();
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(bypay)
{
#ifdef ZTS
  ts_free_id(bypay_globals_id);
#else
  php_bypay_shutdown_globals(&bypay_globals);
#endif
  UNREGISTER_INI_ENTRIES();
  return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
*/
PHP_RINIT_FUNCTION(bypay)
{
  return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
*/
PHP_RSHUTDOWN_FUNCTION(bypay)
{
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(bypay)
{
  php_info_print_table_start();
  php_info_print_table_row(2, "BYPAY support", "enabled");
  php_info_print_table_row(2, "version", PHP_BYPAY_VERSION );
  php_info_print_table_row(2, "author", "jakquan" );
  php_info_print_table_end();

// DISPLAY_INI_ENTRIES();
}
/* }}} */

PHP_FUNCTION(bypay_version){
  RETURN_STRING(PHP_BYPAY_VERSION,1); 
}

PHP_FUNCTION(bypay_cfg_get){
  char *cfg_path=NULL,*key=NULL;
  char *default_value=NULL;
  int key_len=0,default_value_len=0;
  HashTable *p_ini_ht;
  zval *p_value;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &key, &key_len, &default_value, &default_value_len) == FAILURE){
    zend_error(E_ERROR,"need key parameter at least!!");
  }

  if(BYPAY_G(cfg_path)){
    cfg_path = BYPAY_G(cfg_path);
  }else{
    cfg_path = "/usr/local/php/etc/default.ini";
  }

  if(NULL==default_value){
    default_value = "";
  }
  
  ALLOC_HASHTABLE(p_ini_ht);
  zend_hash_init(p_ini_ht, 100, NULL, NULL, 0);
  if( FAILURE==php_parse_user_ini_file("",cfg_path,p_ini_ht) ){
    zend_error(E_ERROR,"can not parse the ini file '%s'",cfg_path);
  }
  
  if( SUCCESS==zend_hash_exists(p_ini_ht,key,key_len+1) ){
    zend_error(E_ERROR,"config for key '%s' not found",key);
  }

  MAKE_STD_ZVAL(p_value);
  if( FAILURE==zend_hash_find(p_ini_ht,key,key_len+1,(void**)&p_value) ){
    zend_printf("cannot read key '%s'",key);
  }
  //int done = read_ini_file_for_key( section, key, value, BUF_SIZE, default_value, cfg_path );
  //zend_printf("ZEND DEBUG# cfg_path:%s,section:%s,key:%s value:%s \n",cfg_path,section,key,value);
  RETVAL_STRING(Z_STRVAL_P(p_value),1);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
