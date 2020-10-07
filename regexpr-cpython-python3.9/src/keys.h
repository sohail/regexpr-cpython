/* src/keys.h 
   Written by, sohail.github.io */

#include <Python.h>
#include <structmember.h>

#include "handlers.h"

#ifndef 	REGEDIT_KEYS_H
#define	REGEDIT_KEYS_H

/* Will go in keys_object::type. The numeric equivalent of what ever is in keys_object::type_str */
#define 	ORDINARY_CHARACTER_N	1
#define  SLASH_CHARACTER_N 2

/* Will go/(be copied) in keys_object::type_str and its numeric equivalent is in keys_object::type */
#define		ORDINARY_CHARACTER	"ordinary_character"
#define     SLASH_CHARACTER   "slash_character"

PyDoc_STRVAR(keys_doc, "keys\n");

typedef struct {

   PyObject_HEAD

   /* type specific members go here */
   /* size_t, unsigned int, signed counter part is ssize_t, [-Wformat=] */
   /*Py_ssize_t*/ size_t index; /* Dict is unorderd, we need an order and we need dict. We'll keep the order by evaluating a key the lower idx means the value should be used earlier than any other value which comes later in terms of idx. Programmers we just push the ugly around */
   const int type; /* Type of the key in number */
   const char *type_str; /* Name of the key */
   char* (*handler)(int, ...);

} keys_object;

#endif
