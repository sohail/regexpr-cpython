#include <Python.h>
#include <structmember.h>

#ifndef		REGEDIT_SUB_PATTERN_H
#define		REGEDIT_SUB_PATTERN_H

PyDoc_STRVAR(sub_pattern_doc, "sub_pattern\n");

typedef struct {

   PyObject_HEAD

   /* Type specific members go here */
   /* size_t, unsigned int, signed int counter part is ssize_t [-Wformat=] */
   /*Py_ssize_t*/ size_t index;
   PyObject *dict; /* Here it is referenced, it is built in pattern_object */

} sub_pattern_object;	

#endif