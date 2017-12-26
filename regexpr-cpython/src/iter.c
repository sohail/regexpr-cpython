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
extern PyTypeObject keys;

/* Forward declaration */
static PyMethodDef pattern_methods[];

static void pattern_PyTypeObject_destructor(pattern_object *self) {

   Py_XDECREF(self->dict);	

   PyObject_Del(self);	
}

/*  
 *  It will return an instance of sub_pattern, sub_pattern has dict  
 *  dict is unorganised. The dict uses an intance of keys as a key 
 *  of key/value pair
 *  each key of dict has idx property. The iteration provides a way to
 *  organize the key/value pairs
 **/
static PyObject *pattern_PyTypeObject_getiterfunc(pattern_object *self) {

   sub_pattern_object *reference = PyObject_New(sub_pattern_object, &sub_pattern);

   if (reference != NULL) {

      reference->index = 0;    
  
      if (self->flags & REGEXPR_COMPILE_FLAG) {

         Py_XINCREF(self->dict);
         reference->dict = self->dict;
      }      
      else
      {
         reference->dict = NULL;
      }
   }

   return (PyObject *)reference;
}

static int pattern_PyTypeObject_initproc(pattern_object *self, PyObject *args, PyObject *keywords) {

 
   return 0;
}	

static PyObject *pattern_PyTypeObject_newfunc(PyTypeObject *ptr_argsv, \
					PyObject *args, PyObject *keywords) {

   pattern_object *self;
   PyObject *func, *func_args,*func_ret, *func_built_arg_expr, *func_built_arg_flags;

   if (PyType_Ready(&sub_pattern) < 0)
      return NULL;

   if (PyType_Ready(&keys) < 0)
      return NULL; 	   
          
   /* A GENERAL COMMENT */ 
   /* PyType_Ready(PyTypeObject *) does lot of things and lot it does not do, 
     one of the later things is not initializing tp_new and tp_init. If you 
     explicitly not do that then a runtime exception will be thrown at this 
     next statement. 
     The exception statement is... cannot create 'module.class' instance 
     'module.class' is taken from PyTypeObject::tp_name */ 

   self = PyObject_New(pattern_object, &pattern);

   if (self == NULL)
      return NULL;	   

   if (!PyArg_ParseTuple(args, "si", &(self->expr), &(self->flags))) {

      PyErr_Clear();

      /* */
      if (!PyArg_ParseTuple(args, "s", &(self->expr)))
         return NULL;

      /* Set default flags here */
      /* Casting away the const, I've my reasons */
      *((unsigned int *)&(self->flags)) = 0;
   }

   /* At this point The dict has been constructed and self->expr and self->flags are assined values */

   self->dict = PyDict_New();
   
   if (self->dict == NULL)
      goto fail;

   /* The self->dict is constructed, though it is empty. The self->expr and self->flags are assigned values to */

   /* User has explicitly asked us to compile the regular expression, we'll compile the regular expression and but it is never returned individually */
   if (self->flags & REGEXPR_COMPILE_FLAG) {
 
      /* Compile regular expression */
      func = Py_FindMethod(pattern_methods, (PyObject *)self, "compile");

      if (func == NULL) { 

         Py_XDECREF(self->dict);

         goto fail;
      }

      func_args =  PyTuple_New(2);

      if (func_args == NULL) { 
  
	  Py_XDECREF(func);
	  Py_XDECREF(self->dict);

	  goto fail;
      }

      func_built_arg_expr = Py_BuildValue("s", self->expr);

      /* PyTuple_SET_ITEM(func_args, 0, func_built_arg_expr); */

      if (func_built_arg_expr == NULL) {
          
         Py_XDECREF(func);
	 Py_XDECREF(func_args);
	 Py_XDECREF(self->dict);

	 goto fail;
      }

      PyTuple_SET_ITEM(func_args, 0, func_built_arg_expr);

      func_built_arg_flags = Py_BuildValue("i", self->flags);

      if (func_built_arg_flags == NULL) {

         Py_XDECREF(func);
	 Py_XDECREF(func_args);
	 Py_XDECREF(self->dict);
	 Py_XDECREF(func_built_arg_expr);

	 goto fail;
      }

      PyTuple_SET_ITEM(func_args, 1, func_built_arg_flags);
     
      /* Though the arguments to this function are optional but we are explicitly providing them. So at this point the self->dict has been constructed and self->expr and self->flags have been passed to the compile function as arguments */
      func_ret = PyCFunction_Call(func, func_args, NULL);

      if (func_ret == NULL) {

         Py_XDECREF(func);
	 Py_XDECREF(func_args);
	 Py_XDECREF(self->dict);
	 Py_XDECREF(func_built_arg_expr);
	 Py_XDECREF(func_built_arg_flags);

         goto fail;
      }	      

      /* Every thing happend with sucess */
      Py_XDECREF(func);
      Py_XDECREF(func_args);
      Py_XDECREF(func_ret);
      Py_XDECREF(func_built_arg_expr);
      Py_XDECREF(func_built_arg_flags);
   }	   

   return (PyObject *)self;

fail:
   Py_XDECREF(self);
   return NULL;
}

static void pattern_PyTypeObject_freefunc(void *p) {

}

static PyObject *pattern_methods_compile(pattern_object *self, PyObject *args, PyObject *keywords) {

   const unsigned int flags;	
   const char *expr; /* This holds pointer to converted Python string to C pointer to character string which is null terminated */
   PyObject *dict, *value;

   size_t len, i = 0;

   /* _PyObject_New() of Objects/object.c */
   keys_object *key;

   if (!PyArg_ParseTuple(args, "si", &expr, &flags)) {

      PyErr_Clear();

      /* At least at this point it is clear that it is not an internal call. The internal call always gives both of the optional arguments */

      if (!PyArg_ParseTuple(args, "s", &expr)) {

          PyErr_Clear(); 	      
          
         /* It is an external command, we're requesting to compile the previously provided pattern */
         if (!PyDict_Size(self->dict)) {
          
            Py_XINCREF(self->dict);

            dict = self->dict;
	    expr = self->expr;
	    *((int *)&flags) = (self->flags | REGEXPR_COMPILE_FLAG);
         }
	 else {

            Py_XINCREF(self->dict);

	    dict = self->dict;

	    goto out;
         }		 
      }
      else {
	 /* This was an external call with one required argument */  
	 dict = PyDict_New();
	 if (dict == NULL)
            goto out;

         *((int *)&flags) = REGEXPR_COMPILE_FLAG;	      
      }	      
   }
   else {

      /* The both optional arguments are given. Check if compile() is explicitly called(externally) by the user or compile() is called internally */

      if (!strcmp(expr, self->expr) && flags == self->flags) { 
         /* compile() is called internally */
         if (PyDict_Size(self->dict)) {
            /* Internal call asks for the recompile of expr(pattern). compile() does not do the recompile */
            dict = self->dict;
	    Py_XINCREF(dict);

            goto out;
         }
	 else if (flags & REGEXPR_COMPILE_FLAG) {

            /* This is an internal call, request to call the pattern which is still not compiled */

            dict = self->dict;
            Py_XINCREF(dict);
         }
	 else {

            /* Very bad Internal call, an exception should be raised here */
            Py_XINCREF(Py_None);
	    dict = Py_None;

            goto out;	    
         }		 		 
      }
      else {
         /* It is an external call, we'll not use the self->dict and construct a new dict */
         dict = PyDict_New();
	 if (dict == NULL)
            goto out;

         Py_XINCREF(dict); 
      }	      
   } 	   
      		     
   /* Finaly compile the pattern. The variables expr, flags and dict are all valid live and working well */

   while (expr[i] != '\0') {

      switch (expr[i] & 0xff) {

         case '^':
         break;
	 case '.':
	 break;
	 case '*':
	 break;
	 case '\\':
	 break;
	 case '[':
	 break;
	 case '+':
	 break;
	 case '$':
	 break;
	 default:
	    key = PyObject_New(keys_object, &keys);
	    if (key != NULL) {
	       len = strlen(ORDINARY_CHARACTER);
	       /* size_t */
	       //*(int *)(&key->index) = i;
	       key->index = i;
	       *(int *)(&key->type) = ORDINARY_CHARACTER_N;
	       key->type_str = malloc(len + 1);
	       if (key->type_str != NULL) {

                  strcpy((char *)key->type_str, ORDINARY_CHARACTER);
		  *((char *)key->type_str + len) = '\0';
		  value = PyString_FromStringAndSize(expr + i, 1);

		  if (value != NULL) {

                     Py_XINCREF(key);
		     Py_XINCREF(value);

		     if (PyDict_SetItem(dict, (PyObject *)key, value) < 0) {

		        Py_XDECREF(key);
		        Py_XDECREF(value);
		        PyErr_Clear();
                     }   			   		   
                  }
		  else 
                     PyErr_Clear(); 			
               }
            }
	    else
	       PyErr_Clear();     
	 break;
      }

      i++;
   }

out:
   return (PyObject *)dict;      
}	

static PyMethodDef pattern_methods[] = { 
	{"compile", (PyCFunction)pattern_methods_compile, METH_VARARGS, "compile a regular expression, returning a dict"},
	{NULL, NULL, 0, NULL},
};

static PyMemberDef pattern_object_members[] = {
   {"expr", T_STRING, offsetof(pattern_object, expr), 0, "const char argv[]"},
   {"flags", T_INT, offsetof(pattern_object, flags), 0, "const unsigned int flags"},
   {NULL},
};

static Py_ssize_t pattern_as_sequence_length(pattern_object *self)
{
    return 0;
}

static PyObject* pattern_as_sequence_concat(pattern_object *self, PyObject *b)
{
    Py_XINCREF(Py_None);	
    return (PyObject*)Py_None;   
}

static PyObject* pattern_as_sequence_repeat(pattern_object *self, Py_ssize_t n)
{
    Py_XINCREF(Py_None);
    return (PyObject*)Py_None;
}

static PyObject* pattern_as_sequence_item(pattern_object *self, Py_ssize_t i)
{
    Py_XINCREF(Py_None);
    return (PyObject*)Py_None;
}

static PyObject* pattern_as_sequence_slice(pattern_object *self, Py_ssize_t i, Py_ssize_t j)
{
    Py_XINCREF(Py_None);
    return (PyObject*)Py_None;
}

int pattern_as_sequence_contains(pattern_object *self, PyObject *value)
{
     /*
        If error occures then it returns -1. If value is contained in self then 1 is returned, if it does not then 0 is returned. If I return -1 without...
	PyErr_Format(Err_Regexpr, "%.012s", "Any string 12 bytes or more long can come here, 12 simply means that Null terminator character if not present may cause segmentation faults"); then, I would get "SystemError: error return without exeception set"
     */ 
    return 1;
}

static PySequenceMethods pattern_as_sequence = {
    (lenfunc)pattern_as_sequence_length, /* sq_length, used by len() sugar */
    (binaryfunc)pattern_as_sequence_concat, /* sq_concat used by + sugar */
    (ssizeargfunc)pattern_as_sequence_repeat, /* sq_repeat, used by * sugar(as in multiplication) */
    (ssizeargfunc)pattern_as_sequence_item, /* sq_item, used by PySequence_GetItem() and other detail */
    (ssizessizeargfunc)pattern_as_sequence_slice, /* sq_slice */
    (ssizeobjargproc)NULL, /* sq_ass_item */
    (ssizessizeobjargproc)NULL, /* sq_ass_slice */
    (objobjproc)pattern_as_sequence_contains, /* sq_contains */

    /* Added in release 2.0 */
    (binaryfunc)NULL, /* sq_inplace_concat */
    (ssizeargfunc)NULL, /* sq_inplace_repeat */
};

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
   PyObject_HEAD_INIT(NULL)
   0,						/* ob_size */
   "iter.pattern",                            	/* tp_name, module.typename */ 
   sizeof(pattern_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)pattern_PyTypeObject_destructor,	/* tp_dealloc */
   (printfunc)0, 				/* tp_print */
   0, 						/* tp_getattr */
   0, 						/* tp_setattr */
   0,						/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   &pattern_as_sequence, 			/* tp_as_sequence, 
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
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_CLASS,	/* tp_flags */
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
   (getiterfunc)pattern_PyTypeObject_getiterfunc, /* tp_iter */
   (iternextfunc)0, 				  /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   pattern_methods,				/* tp_methods, PyMethodDef* */
   pattern_object_members,			/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   0,						/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)pattern_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   (newfunc)pattern_PyTypeObject_newfunc,	/* tp_new */
   (freefunc)pattern_PyTypeObject_freefunc,	/* tp_free, Low-Level \
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

static Py_ssize_t expr_length(sub_pattern_object *self) {

   /* What if string is not null terminated? */	 
   /* return strlen(self->expr); */
   return 0;	
}

static PyObject *expr_concat(sub_pattern_object *self, PyObject *b) {

   if (!PyObject_TypeCheck(b, &pattern)) { 

      PyErr_Format(PyExc_TypeError, "expected a \"%.200s\" Object instead had \"%.200s\"", self->ob_type->tp_name, b->ob_type->tp_name);
      return NULL; 
   }     

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;	
}

static PyObject *expr_repeat(sub_pattern_object *self, Py_ssize_t n) {

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}

static PyObject *expr_item(sub_pattern_object *self, Py_ssize_t i) {

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}	

/* Implementation of sequence protocol */
/* Include/object.h, also see Objects/stringobject.c but most probably read the documentation */
static PySequenceMethods sub_pattern_as_sequence = {
   (lenfunc)expr_length, /* sq_length, used by len() sugar */
   (binaryfunc)expr_concat, /* sq_concat, used + */
   (ssizeargfunc)expr_repeat, /* sq_repeat, used by *(as in multiplication) */
   (ssizeargfunc)expr_item, /* sq_item, used by PySequence_GetItem() and \
		       some other detail */
   (ssizessizeargfunc)0, /* sq_slice */
   (ssizeobjargproc)0, /* sq_ass_item */
   (ssizessizeobjargproc)0, /* sq_ass_slice */
   (objobjproc)0, /* sq_contains */

   /* Added in release 2.0 */
   (binaryfunc)0, /* sq_inplace_concat */
   (ssizeargfunc)0, /* sq_inplace_repeat */
};	


static void sub_pattern_PyTypeObject_destructor(sub_pattern_object *self) {

   PyObject_Del(self);	
}

static PyObject *sub_pattern_PyTypeObject_ternaryfunc(sub_pattern_object *self, PyObject *args, PyObject *keywords) {

   char *phrase, *pattern;

   /* The last entry should be NULL, I know the source code of PyArg_ParseTupleAndKeywords() very well but even then I remain an Ass and suffered. For the rest of your life(a note to me) put NULL in the lists like this one */
   static char *kwlist[] = {"phrase", "pattern", NULL};

   if (!PyArg_ParseTupleAndKeywords(args, keywords, "ss", kwlist, &phrase, &pattern))
      return NULL;

   /*printf("PHRASE = %s, PATTERN = %s\n", phrase, pattern);*/

   return (PyObject *)self;	
}

/*
 * The sub_pattern object has dict instance, dict is unorganised
 * organize dict on property idx
 */
static PyObject *sub_pattern_PyTypeObject_iternextfunc(sub_pattern_object *self)
{
   Py_ssize_t pos = 0;
   PyObject *key = NULL, *value = NULL;

   if (self->dict == NULL)
   {
       return (PyObject *)NULL;
   }

   while (PyDict_Next(self->dict, &pos, &key, &value))
   {
       // printf("%d\n", self->index); [-Wformat=] 
       if (((keys_object *)key)->index == self->index) 
       {
	   self->index = self->index + 1;
           return key;  
       }
   }

   self->index = 0;

   /* Return NULL and iteration stops, in sugar of Python */
   return (PyObject *)NULL;

   //Py_XINCREF(self);
   /* Return NULL and iteration will stop(in sugar of Python) */
   //return (PyObject *)self;
   //return key;
}	

static PyTypeObject sub_pattern = {
   
   /* Include/object.h */	
   PyObject_HEAD_INIT(NULL)
   0,						/* ob_size */
   "iter.sub_pattern",                   	/* tp_name, module.typename */ 
   sizeof(sub_pattern_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)sub_pattern_PyTypeObject_destructor, /* tp_dealloc */
   (printfunc)0, 				/* tp_print */
   0,				        	/* tp_getattr */
   0,				         	/* tp_setattr */
   0,						/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   &sub_pattern_as_sequence,			/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   0,						/* tp_hash */
   (ternaryfunc)sub_pattern_PyTypeObject_ternaryfunc, /* tp_call */
   (reprfunc)0,					/* tp_str */
   0,						/* tp_getattro */ /* o is obj */
   0,						/* tp_setattro */ /* o is obj */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_CLASS,	/* tp_flags */
   sub_pattern_doc,			        /* tp_doc, document string */
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
   (getiterfunc)0, 				/* tp_iter */
   (iternextfunc)sub_pattern_PyTypeObject_iternextfunc, /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   0,						/* tp_methods, PyMethodDef* */
   0,						/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   (descrgetfunc)0,				/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)0, 				/* tp_init */
   0,						/* tp_alloc */
   (newfunc)0,					/* tp_new */
   (freefunc)0,					/* tp_free, Low-Level \
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

