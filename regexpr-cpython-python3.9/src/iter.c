/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/iter.c
 * Written by, sohail.github.io
 */

#include "iter.h"

PyObject *RegExprCompileFlag;
PyObject *RegExprFooFlag;

extern PyObject *Err_Regexpr;

static int pattern_PyTypeObject_initproc(pattern_object *self, PyObject *args, PyObject *keywords) {
 
   return 0;
}

static PyObject* pattern_PyTypeObject_newfunc(PyTypeObject *ptr_argsv, PyObject *args, PyObject *keywords)
{
    pattern_object* self;

    /* A GENERAL COMMENT */ 
    /* PyType_Ready(PyTypeObject *) does lot of things and lot it does not do, 
       one of the later things is not initializing tp_new and tp_init. If you 
       explicitly not do that then a runtime exception will be thrown at this 
       next statement. 
       The exception statement is... cannot create 'module.class' instance 
       'module.class' is taken from PyTypeObject::tp_name */ 
    self = PyObject_New(pattern_object, &pattern);

    if (self == NULL)
    {
        return NULL;
    }

    /* First check if two of these arguments are given */  
    if (!PyArg_ParseTuple(args, "si", &(self->expr), &(self->flags))) 
    {
        PyErr_Clear();

        /* No two arguments were not given, check if one argument is given */
        if (!PyArg_ParseTuple(args, "s", &(self->expr)))
        {
            /* No arguments were given */
            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), atleast one argument was expected by this method");
            return NULL;
        }

        /* Here set flags to default values, if there are any */
        /* But flags is not modifiable, cast it as such that it becomes modifiable */
        *((unsigned int*)&(self->flags)) = 0;        
    }

    self->dict = PyDict_New();

    if (self->dict == NULL)
    {
        PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), unable to initialize self->dict");
        return NULL;        
    }

    /* The self->dict is constructed, though it is empty. The self->expr and self->flags are assigned values to */

    /* User has explicitly asked us to compile the regular expression, we'll compile the regular expression and but it is never returned individually */
    if (self->flags & REGEXPR_COMPILE_FLAG)
    {
    }

    return self;
}


/* Include/object.h, Objects/typeobject.c */
/* A new class, this class will inherit from class object. The function 
 * PyType_Ready()(Objects/typeobject.c) will assign the address of 
 * PyBaseObject_Type(an instance of PyTypeObject Objects/typeobject.c) 
 * to PyTypeObject::tp_base. The PyTypeObject PyBaseObject { }; is our class
 * named object
 * The above detail can be summerised as following Python statements... 
 *    class argsv(object):
 *       def __init__(self):
 *          print "Hello World" */
PyTypeObject pattern = {
       
   /* Include/object.h */	
   /*PyObject_HEAD_INIT(NULL)*/
   PyVarObject_HEAD_INIT(NULL, 0)
   /*0,*/						/* ob_size */
   "iter.pattern",              /* tp_name, module.typename */ 
   sizeof(pattern_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)0 /*pattern_PyTypeObject_destructor*/,	/* tp_dealloc */
   (printfunc)0, 				/* tp_print */
   0, 						/* tp_getattr */
   0, 						/* tp_setattr */
   0,						/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   0 /*&pattern_as_sequence*/, 			/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   0,						/* tp_hash */
   (ternaryfunc)0, 				/* tp_call */
   (reprfunc)0,					/* tp_str */
   0,						/* tp_getattro */
   0,						/* tp_setattro */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT /*| Py_TPFLAGS_HAVE_CLASS*/,	/* tp_flags */
   pattern_doc,					/* tp_doc, document string */
   /* Assigned meaning in 2.0 */
   /* a call function for all accessible objects(Include/object.h) */
   0,						/* tp_traverse */
   /* delete refrences to the contained objects(Include/object.h) */
   0,						/* tp_clear */
   /* Assigned meaning in release 2.1 */
   /* rich comparisons(Include/object.h) */
   0,						/* tp_richcompare */
   /* weak reference enabler */
   0,						/* tp_weaklistoffset */
   /* Addes in release 2.2 */
   /* Iterators */
   (getiterfunc)0/*pattern_PyTypeObject_getiterfunc*/, /* tp_iter */
   (iternextfunc)0, 				  /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   0/*pattern_methods*/,				/* tp_methods, PyMethodDef* */
   0/*pattern_object_members*/,			/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   0,						/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)pattern_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   (newfunc)pattern_PyTypeObject_newfunc,	/* tp_new */
   (freefunc)0/*pattern_PyTypeObject_freefunc*/,	/* tp_free, Low-Level \
						   free-memory routine */
   0,						/* tp_is_gc, For \
						   PyObject_IS_GC */
   0,						/* tp_bases, PyObject* */
   0,						/* tp_mro, method resolution \
						   order. PyObject* */
   0,						/* tp_cache, PyObject* */
   0,						/* tp_subclasses, PyObject* */
   0,						/* tp_weaklist, PyObject* */
   (destructor)0,				/* tp_del */  
};