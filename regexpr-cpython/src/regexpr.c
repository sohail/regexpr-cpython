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

static void regexpr_PyTypeObject_destructor(regexpr_object *self) {

   if (self->dict != NULL) {

      /* Remember dict has its own class, the destructor of its class will 
       * deallocte it(not us, httpheaders class) */	
      Py_XDECREF(self->dict);
   }

   PyObject_Del(self);	
}

static PyObject *regexpr_PyTypeObject_ternaryfunc(regexpr_object *self, \
		                        PyObject *args, PyObject *keywords) {

    return (PyObject *)self;	
}
/* 
 * The message body start after a line 
 * \r\n
 * message body
 * This function does not deal with the message body
 */
/*
 * \n = 0x0a, \r = 0x0d, ' ' = 0x20
 * Get / HTTP/1.1
 * Connection: Keep-Alive \r\n
 * ---------------------------------
 * begin_ptr will be at 'C'(In the case of above line), end_ptr will be at '\n'
 * In the case of an empty line the begin_ptr is at '\r' and end_ptr is at
 * '\n' and end_ptr - begin_ptr will always be 1 
 * -------------------------------------------------------------------------
 */
static PyObject *regexpr_PyTypeObject_descrgetfunc(regexpr_object \
		        *self, PyObject *instance, PyObject *instance_type) {

   Py_INCREF(self->dict);
   return (PyObject *)self->dict;	
}

static int regexpr_PyTypeObject_initproc(regexpr_object *self, \
		                          PyObject *args, PyObject *keywords) {

   int ret = 0;  	

   /* "Os|i" is better but for now I'll stick to the following code block */
   if (!PyArg_ParseTuple(args, "Osi", &(self->expr_obj), &(self->str), \
			                                  &(self->flags))) {

      PyErr_Clear();

      /* Set default flags here */

      if (!PyArg_ParseTuple(args, "Os", &(self->expr_obj), &(self->str))) {  
	   
         Py_XDECREF(self);	      
         ret = -1;	   
      }	 
   }

   /* Sanity checks... check if pattern is sane enough. When pattern is 
      insane, throw an exception(Err_Regexpr) and ret being -1 */

   return ret;	
}	

static PyObject *regexpr_PyTypeObject_newfunc(PyTypeObject *ptr_re, \
		                       PyObject *args, PyObject *keywords) {

   regexpr_object *self;

  /*  
     PyType_Ready(PyTypeObject *) does lot of things and lot it does not do, 
     one of the later things is, not initializing tp_new and tp_init. If you 
     explicitly not do that then a runtime exception will be thrown at this 
     next statement. 
     The exception statement is... cannot create 'module.class' instance 
     'module.class' is taken from PyTypeObject::tp_name 
   */     
   self = PyObject_New(regexpr_object, &re);

   if (self == NULL)
      return NULL;

   self->dict = PyDict_New();

   if (self->dict == NULL) 
      goto fail; /* I most of the time go there too; its sad, but true */ 
    
   return (PyObject *)self;

fail:
   Py_XDECREF(self);
   return NULL;
}

static void regexpr_PyTypeObject_freefunc(void *p) {

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
   PyObject_HEAD_INIT(NULL)
   0,						/* ob_size */
   "regexpr.re",                   		/* tp_name, module.typename */ 
   sizeof(regexpr_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)regexpr_PyTypeObject_destructor,	/* tp_dealloc */
   (printfunc)0, 				/* tp_print */
   0,				        	/* tp_getattr */
   0,				         	/* tp_setattr */
   0,						/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   0, 						/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   0,						/* tp_hash */
   (ternaryfunc)regexpr_PyTypeObject_ternaryfunc, /* tp_call */
   (reprfunc)0,					/* tp_str */
   0,						/* tp_getattro */ /* o is obj */
   0,						/* tp_setattro */ /* o is obj */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_CLASS,	/* tp_flags */
   re_doc,			        	/* tp_doc, document string */
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
   (getiterfunc)0,	  			/* tp_iter */
   (iternextfunc)0, 				/* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   0,						/* tp_methods, PyMethodDef* */
   0,						/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   (descrgetfunc)regexpr_PyTypeObject_descrgetfunc,	/* tp_descr_get */
   0, 						/* tp_descr_set */
   offsetof(regexpr_object, dict),		/* tp_dictoffset, Py_ssize_t */
   (initproc)regexpr_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   regexpr_PyTypeObject_newfunc,		/* tp_new */
   regexpr_PyTypeObject_freefunc,		/* tp_free, Low-Level \
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

static PyMethodDef regexprMethods[] = { NULL, NULL, 0, NULL };

PyMODINIT_FUNC initregexpr(void) {

   PyObject *module_regexpr;
   extern PyObject *RegExprCompileFlag, *RegExprFooFlag;

   if ((RegExprCompileFlag = Py_BuildValue("i", REGEXPR_COMPILE_FLAG)) == NULL)
      return;

   if ((RegExprFooFlag = Py_BuildValue("i", REGEXPR_FOO_FLAG)) == NULL) {

      Py_XDECREF(RegExprCompileFlag);	   
      return;	   
   }    

   if (PyType_Ready(&re) < 0)
      return;

   if (PyType_Ready(&pattern) < 0)
      return;	    
    
   module_regexpr = Py_InitModule3("regexpr", regexprMethods, \
		                                     REGEXPR_VERSION_DOC);
   if (module_regexpr == NULL) {

      Py_XDECREF(RegExprCompileFlag);
      Py_XDECREF(RegExprFooFlag);
	   
      return;
   }    

   /* PyObject_Call()(Objects/abstract.c) will call the PyType_Type.tp_call.
      The PyType_Type is defined in file Objects/typeobject.c */
   /* The name must be module.class token, we creating new class and this 
      token will go in PyTypeObject::tp_name */
   Err_Regexpr = PyErr_NewException("regexpr.error", NULL, NULL);
   if (Err_Regexpr == NULL) {
	
      Py_XDECREF(RegExprCompileFlag);
      Py_XDECREF(RegExprFooFlag);
      Py_XDECREF(module_regexpr);

      return;
   }	   

   PyModule_AddObject(module_regexpr, "re", (PyObject *)&re);
   PyModule_AddObject(module_regexpr, "expr", (PyObject *)&pattern);
   PyModule_AddObject(module_regexpr, "error", Err_Regexpr); 

   /* Will appear under heading DATA */
   PyModule_AddObject(module_regexpr, "REGEXPR_COMPILE_FLAG", RegExprCompileFlag);
   PyModule_AddObject(module_regexpr, "REGEXPR_FOO_FLAG", RegExprFooFlag);
}	
