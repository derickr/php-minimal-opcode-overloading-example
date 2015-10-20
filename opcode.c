/*
   +----------------------------------------------------------------------+
   | Xdebug                                                               |
   +----------------------------------------------------------------------+
   | Copyright (c) 2015 Derick Rethans                                    |
   +----------------------------------------------------------------------+
   | This source file is subject to version 1.0 of the Xdebug license,    |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://xdebug.derickrethans.nl/license.php                           |
   | If you did not receive a copy of the Xdebug license and are unable   |
   | to obtain it through the world-wide-web, please send a note to       |
   | xdebug@derickrethans.nl so we can mail you a copy immediately.       |
   +----------------------------------------------------------------------+
   | Authors:  Derick Rethans <derick@xdebug.org>                         |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "main/php_version.h"

#if HAVE_OPCODE

#include "php_opcode.h"


zend_function_entry opcode_functions[] = {
	{NULL, NULL, 0, 0, 0}
};

zend_module_entry opcode_module_entry = {
	STANDARD_MODULE_HEADER,
	"opcode",
	opcode_functions,
	PHP_MINIT(opcode),
	PHP_MSHUTDOWN(opcode),
	NULL,
	NULL,
	NULL,
	"0.0.1",
	NO_MODULE_GLOBALS,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#if COMPILE_DL_OPCODE
ZEND_GET_MODULE(opcode)
#if PHP_VERSION_ID >= 70000
#	ifdef ZTS
		ZEND_TSRMLS_CACHE_DEFINE();
#	endif
#endif
#endif

static int opcode_print_handler(zend_execute_data *execute_data)
{
	return ZEND_USER_OPCODE_DISPATCH;
}


PHP_MINIT_FUNCTION(opcode)
{
	int i;

	for (i = 0; i < 256; i++) {
		if (zend_get_user_opcode_handler(i) == NULL) {
			if (i == ZEND_HANDLE_EXCEPTION) {
				continue;
			}
			zend_set_user_opcode_handler(i, opcode_print_handler);
		}
	}

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(opcode)
{
	int i;

	/* cleanup handlers set in MINIT to opcode_check_branch_entry_handler */
	for (i = 0; i < 256; i++) {
		if (zend_get_user_opcode_handler(i) == opcode_print_handler) {
			zend_set_user_opcode_handler(i, NULL);
		}
	}

	return SUCCESS;
}

#endif
