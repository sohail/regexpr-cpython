/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/iter.h
 * Written by, sohail.github.io
 */

#include <Python.h>
#include <structmember.h>

#include "keys.h"

#ifndef		REGEDIT_ITER_H
#define		REGEDIT_ITER_H

/* Py_XDECREF and Py_DECREF, Py_XDECREF is called when refernced object could be NULL. When reference is not NULL it then apply the macro Py_DECREF on the
 refered to object, see file Include/object.h */

#define		REGEXPR_COMPILE_FLAG		1
#define		REGEXPR_FOO_FLAG	        2	

/* Forward declarations */
PyTypeObject pattern;
static PyTypeObject sub_pattern;
static PySequenceMethods sub_pattern_as_sequence;

PyDoc_STRVAR(pattern_doc, "pattern\n");
PyDoc_STRVAR(sub_pattern_doc, "sub_pattern\n");

typedef struct {

   PyObject_HEAD

   /* Type specific members go here */
   /* size_t, unsigned int, signed int counter part is ssize_t [-Wformat=] */
   /*Py_ssize_t*/ size_t index;
   PyObject *dict; /* Here it is referenced, it is built in pattern_object */

} sub_pattern_object;	

/* Instance which deligates to the class(PyObjectType *ob_type) */
typedef struct {

   /* 
    * Macro PyObject_HEAD expands into...
    * struct _object *_ob_next;
    * struct _object *_ob_prev;
    * Py_ssize_t ob_refcnt;
    * struct _typeobject *ob_type;
    *
    * And the PyObject is declared as...
    *    typedef struct {   
    *       PyObject_HEAD
    *    }PyObject;   
    */	
   PyObject_HEAD

   /* Type specific members go here */
   const char *expr;
   const unsigned int flags;
   PyObject *dict; /* Here it is built from scratch */
		   
}pattern_object;

#endif
