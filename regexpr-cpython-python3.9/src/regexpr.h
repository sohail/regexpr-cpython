/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/regexpr.h
 * Written by, sohail.github.io
 */

#include <Python.h>
#include <structmember.h>

#include "iter.h"

#define		NEW_LINE	0x0a
#define		CARRIAGE_RETURN	0x0d
#define		SPACE_BAR	0x20
#define		COLON		0x3a

/* Py_XDECREF and Py_DECREF, Py_XDECREF is called when refernced object could be NULL. When reference is not NULL it then apply the macro Py_DECREF on the
 refered to object, see file Include/object.h */

/* A Python module initialization function. Module init functions outside the 
 * Python core must be exported(they should've external linkage) */
#ifndef		PyMODINIT_FUNC		
#define		PyMODINIT_FUNC		void
#endif

#define		REGEXPR_VERSION_DOC	"Version 0.1 - This module provides regular expression matching operations similar to those outlined in following document ... .\nWritten by, Sohail Qayum Malik<sohail@stupidcomputing.com>"

/* Forward declaration */
static PyTypeObject re;

PyDoc_STRVAR(re_doc, "re\n");

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
    const char *str;
    //pattern_object expr_obj;
    Py_ssize_t flags;

    PyObject *dict;
   	   		   
}regexpr_object;	
