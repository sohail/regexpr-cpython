/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/keys.c
 * Written by, sohail.github.io
 */

#include "keys.h"

extern PyObject *Err_Regexpr;

static void keys_PyTypeObject_destructor(keys_object *self) {

   if (self->type_str != NULL)
      free((char *)self->type_str);

   PyObject_Del(self);	
}

static int keys_PyTypeObject_printfunc(keys_object *self, FILE *fp, int flags) {

   size_t i;

   for (i = 0; i < strlen(self->type_str); i++)
      fprintf(fp, "%c", self->type_str[i]); 	   

   return 0;	
}	

/*
static int keys_PyTypeObject_compfunc(PyObject *a, PyObject *b) {

   return 1; 	
}
*/	

static long keys_PyTypeObject_hashfunc(keys_object *self) {

   return 1;	
}

/* tp_call, currently working here */
static PyObject *keys_PyTypeObject_ternaryfunc(keys_object *self, PyObject *args, PyObject *keywords)
{    
    char *phrase, *pattern;

    /* The last entry should be NULL, I know the source code of PyArg_ParseTupleAndKeywords() very well but even then I remain an Ass and suffered. For the rest of your life(a note to me) put NULL in the lists like this one */
    static char *kwlist[] = {"phrase", "pattern", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywords, "ss", kwlist, &phrase, &pattern))
    {
        return NULL;
    }

    switch (self->type)
    {
        case ORDINARY_CHARACTER_N:    
            if (self->handler(3, phrase, pattern, self->index, self) == NULL)
            {
                PyErr_SetString(Err_Regexpr, "keys.c, in keys_PyTypeObject_ternaryfunc(): call to default_handler() failed");
                return NULL;
            }
        break;
        case SLASH_CHARACTER_N:            
            if (self->handler(3, phrase, pattern, self->index, self) == NULL)
            {
                PyErr_SetString(Err_Regexpr, "keys.c, in keys_PyTypeObject_ternaryfunc(): call to slash_handler() failed");
                return NULL;
            }
        break;        
    }
    
    return PyUnicode_FromString(phrase);    
}

static PyObject *keys_PyTypeObject_getiterfunc(keys_object *self) {


   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}

static PyObject *keys_PyTypeObject_richcmpfunc(PyObject *a, PyObject *b, int num) {

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}	

static int keys_PyTypeObject_initproc(keys_object *self, PyObject *args, PyObject *keywords) {

 
   return 0;
}	

static PyObject* keys_PyTypeObject_newfunc(PyTypeObject* ptr_keys, PyObject* args, PyObject* keywords) {

   /*keys_object* self;*/
      
   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}

static void keys_PyTypeObject_freefunc(void *p) {

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
PyTypeObject keys = {
   
   /* Include/object.h */	
   /*PyObject_HEAD_INIT(NULL)*/
   PyVarObject_HEAD_INIT(NULL, 0)
   /*0,*/						/* ob_size */
   "regexpr.keys",                            	/* tp_name, module.typename */ 
   sizeof(keys_object),				/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)keys_PyTypeObject_destructor,	/* tp_dealloc */
   (printfunc)keys_PyTypeObject_printfunc, 	/* tp_print */
   0, 						/* tp_getattr */
   0, 						/* tp_setattr */
   (PyAsyncMethods*)0,			/* not tp_compare but the tp_as_sync */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   0, 						/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   (hashfunc)keys_PyTypeObject_hashfunc,	/* tp_hash */
   (ternaryfunc)keys_PyTypeObject_ternaryfunc, /* tp_call */      
   (reprfunc)0,					/* tp_str */
   0,						/* tp_getattro */
   0,						/* tp_setattro */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT /*| Py_TPFLAGS_HAVE_CLASS | Py_TPFLAGS_HAVE_RICHCOMPARE*/,	/* tp_flags */
   keys_doc,					/* tp_doc, document string */
   /* Assigned meaning in 2.0 */
   /* a call function for all accessible objects(Include/object.h) */
   0,						/* tp_traverse */
   /* delete refrences to the contained objects(Include/object.h) */
   0,						/* tp_clear */
   /* Assigned meaning in release 2.1 */
   /* rich comparisons(Include/object.h) */
   keys_PyTypeObject_richcmpfunc,		/* tp_richcompare */
   /* weak reference enabler */
   0,						/* tp_weaklistoffset */
   /* Addes in release 2.2 */
   /* Iterators */
   (getiterfunc)keys_PyTypeObject_getiterfunc, /* tp_iter */
   (iternextfunc)0, 				  /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   (PyMethodDef *)0,				/* tp_methods, PyMethodDef* */
   (PyMemberDef *)0,				/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   0,						/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)keys_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   (newfunc)keys_PyTypeObject_newfunc,		/* tp_new */
   (freefunc)keys_PyTypeObject_freefunc,	/* tp_free, Low-Level \
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

