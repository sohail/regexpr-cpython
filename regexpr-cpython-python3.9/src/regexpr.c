/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/regexpr.c
 * Written by, sohail.github.io
 */

/*
 * Programmers just push the ugly around
 */

#include "regexpr.h"

static int regexpr_PyTypeObject_initproc(regexpr_object *self, PyObject *args, PyObject *keywords)
{

   int ret = 0;  	

   return ret;	
}

static PyObject *regexpr_PyTypeObject_newfunc(PyTypeObject *ptr_re, PyObject *args, PyObject *keywords)
{
    return NULL;
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

static PyTypeObject re = {
   
   /* Include/object.h */	
   /*PyObject_HEAD_INIT(NULL)*/
   PyVarObject_HEAD_INIT(NULL, 0)
   /*0,*/						/* ob_size */
   "regexpr.re",                            	/* tp_name, module.typename */ 
   sizeof(regexpr_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)0,	/* tp_dealloc */
   (printfunc)0, 	/* tp_print */
   0, 						/* tp_getattr */
   0, 						/* tp_setattr */
   0,						/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,				/* tp_as_number, \
						       PyNumberMethods* */
   0, 						/* tp_as_sequence, 
						       PySequenceMethods* */
   0,				/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   0,						/* tp_hash */
   (ternaryfunc)0, /* tp_call */
   (reprfunc)0,	/* tp_str */
   0,						/* tp_getattro */
   0,						/* tp_setattro */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT,				/* tp_flags */
   re_doc,					/* tp_doc, document string */
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
   (getiterfunc)0,	  /* tp_iter */
   (iternextfunc)0, /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   0,						/* tp_methods, PyMethodDef* */
   0,						/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   0,						/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)regexpr_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   regexpr_PyTypeObject_newfunc,			/* tp_new */
   0,						/* tp_free, Low-Level \
						   free-memory routine */
   0,						/* tp_is_gc, For \
						   PyObject_IS_GC */
   0,						/* tp_bases, PyObject* */
   0,						/* tp_mro, method resolution \
						   order. PyObject* */
   0,						/* tp_cache, PyObject* */
   0,						/* tp_subclasses, PyObject* */
   0,						/* tp_weaklist, PyObject* */
   0,						/* tp_del */  
};

static PyMethodDef regexprMethods [] = {
   {NULL},	
};	

static struct PyModuleDef regexprmodule = {
    PyModuleDef_HEAD_INIT,
    "regexpr",
    re_doc, 
    -1, 
    regexprMethods,
    NULL,
    NULL,
    NULL,
    NULL    
};

PyMODINIT_FUNC PyInit_regexpr(void)
{
    /* This module */
   PyObject *module_re;

   /*if (PyType_Ready(&re) < 0)
      return NULL;*/	   

   /*
    * The name of the module, the module methods and any document string 
    * There is a one to one corresspondence between the name of the module,
    * the initialization function's name and finally the name of this file
    */    
   module_re = PyModule_Create(&regexprmodule);
   if (module_re == NULL)
       return NULL;

   /* Add the instance of TypeObject to the module dict */
   /*PyModule_AddObject(module_re, "regexpr", (PyObject *)&re);*/    

   /* Add the instance of TypeObject to the module dict */
   //PyModule_AddObject(module_re, "regexpr", (PyObject *)&argsv);

    /*PyObject *dict;
    PyObject *module = PyModule_Create(&argsvmodule);
    if (module == NULL)
        return NULL;
    dict = PyModule_GetDict(module);*/

    /*ADD_DEFINE(SND_ASYNC);
    ADD_DEFINE(SND_NODEFAULT);
    ADD_DEFINE(SND_NOSTOP);
    ADD_DEFINE(SND_NOWAIT);
    ADD_DEFINE(SND_ALIAS);
    ADD_DEFINE(SND_FILENAME);
    ADD_DEFINE(SND_MEMORY);
    ADD_DEFINE(SND_PURGE);
    ADD_DEFINE(SND_LOOP);
    ADD_DEFINE(SND_APPLICATION);

    ADD_DEFINE(MB_OK);
    ADD_DEFINE(MB_ICONASTERISK);
    ADD_DEFINE(MB_ICONEXCLAMATION);
    ADD_DEFINE(MB_ICONHAND);
    ADD_DEFINE(MB_ICONQUESTION);*/

    //PyModule_AddObject(module, "argsv", (PyObject *)&argsv);

    return module_re;
}
