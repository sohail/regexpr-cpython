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

/* Objects/exceptions.c, Doc/ext/extending.tex */
PyObject *Err_Regexpr;

static int regexpr_PyTypeObject_initproc(regexpr_object *self, PyObject *args, PyObject *keywords)
{
    int ret = 0; 

    /* "Os|i" is better but for now I'll stick to the following code block */
    if (!PyArg_ParseTuple(args, "si", &(self->str), &(self->flags)))
    {
        //PyErr_Print();                                                
        PyErr_Clear();
        //PyErr_Format(Err_Regexpr, "%0.12s", "Any string 12 bytes or more long can come here, 12 simply means that Null terminator character if not present may cause segmentation faults");
        PyErr_SetString(Err_Regexpr, "regexpr.c, in regexpr_PyTypeObject_initproc(), 2 arguments were expected by this method");
        ret = -1;
    }

    /*printf("--> %s\n", self->str);*/ 	

    return ret;	
}

static PyObject *regexpr_PyTypeObject_newfunc(PyTypeObject *ptr_re, PyObject *args, PyObject *keywords)
{
    regexpr_object *self;

   /*  
     TODO   
     The following behavior was valid for 2.7.* I still've to find if it is still valid
     -----------------------------------------------------------------------------------  
     PyType_Ready(PyTypeObject *) does lot of things and lot it does not do, 
     one of the later things is, not initializing tp_new and tp_init. If you 
     explicitly not do that then a runtime exception will be thrown at this 
     next statement. 
     The exception statement is... cannot create 'module.class' instance 
     'module.class' is taken from PyTypeObject::tp_name 
    */
    self = PyObject_New(regexpr_object, &re);

    if (self == NULL)
    {
        return NULL;
    }

    self->dict = PyDict_New();

    if (self->dict == NULL)
    {
        Py_XDECREF(self);
        return NULL; 
    }

    return (PyObject *)self;        
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
   (initproc)regexpr_PyTypeObject_initproc, /* tp_init */
   0,						/* tp_alloc */
   (newfunc)regexpr_PyTypeObject_newfunc,	/* tp_new */
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
    extern PyObject *RegExprCompileFlag, *RegExprFooFlag;

    if ((RegExprCompileFlag = Py_BuildValue("i", REGEXPR_COMPILE_FLAG)) == NULL)
    {
        return NULL;
    }
    if ((RegExprFooFlag = Py_BuildValue("i", REGEXPR_FOO_FLAG)) == NULL)
    {
        Py_XDECREF(RegExprCompileFlag);	   
        return NULL;	   
    }

    if (PyType_Ready(&re) < 0)
    {
        Py_XDECREF(RegExprCompileFlag);
        Py_XDECREF(RegExprFooFlag);
        return NULL;
    }

    if (PyType_Ready(&pattern) < 0)
    {
        Py_XDECREF(RegExprCompileFlag);
        Py_XDECREF(RegExprFooFlag);
        return NULL;
    }

/*       
    if (PyType_Ready(&sub_pattern) < 0)
    {        
        Py_XDECREF(RegExprCompileFlag);
        Py_XDECREF(RegExprFooFlag);
        return NULL;
    }
 */    
  
    /*
     * The name of the module, the module methods and any document string 
     * There is a one to one corresspondence between the name of the module,
     * the initialization function's name and finally the name of this file
     */    
    module_re = PyModule_Create(&regexprmodule);
    if (module_re == NULL)
    {
        Py_XDECREF(RegExprCompileFlag);
        Py_XDECREF(RegExprFooFlag);
        return NULL;
    }

    /* Add the instance of TypeObject to the module dict */
    //PyModule_AddObject(module_re, "re", (PyObject *)&re);

    /* PyObject_Call()(Objects/abstract.c) will call the PyType_Type.tp_call.
      The PyType_Type is defined in file Objects/typeobject.c */
    /* The name must be module.class token, we creating new class and this 
      token will go in PyTypeObject::tp_name */
    Err_Regexpr = PyErr_NewException("regexpr.error", NULL, NULL);
    if (Err_Regexpr == NULL)
    {
        Py_XDECREF(RegExprCompileFlag);
        Py_XDECREF(RegExprFooFlag);
        Py_XDECREF(module_re);

        return NULL;
    }

    /* Add the instance of TypeObject to the module dict */
    PyModule_AddObject(module_re, "re", (PyObject *)&re);
    PyModule_AddObject(module_re, "expr", (PyObject *)&pattern);
/*    
    PyModule_AddObject(module_re, "sub_pattern", (PyObject *)&sub_pattern);
 */    
    PyModule_AddObject(module_re, "error", Err_Regexpr);

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

    /* Will appear under heading DATA */
    PyModule_AddObject(module_re, "REGEXPR_COMPILE_FLAG", RegExprCompileFlag);
    PyModule_AddObject(module_re, "REGEXPR_FOO_FLAG", RegExprFooFlag);

    return module_re;
}
