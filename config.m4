dnl $Id: config.m4,v 1.28 2008-07-31 00:43:35 sniper Exp $
dnl config.m4 for extension opcode

PHP_ARG_ENABLE(opcode, whether to enable simple opcode overload test extension,
[  --enable-opcode         Enable opcode support])

if test "$PHP_OPCODE" != "no"; then
  AC_DEFINE(HAVE_OPCODE,1,[ ])

  PHP_NEW_EXTENSION(opcode, opcode.c, $ext_shared)
  PHP_SUBST(OPCODE_SHARED_LIBADD)
  PHP_ADD_MAKEFILE_FRAGMENT
fi
