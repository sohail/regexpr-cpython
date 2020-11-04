/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/iter.c
 * Written by, sohail.github.io
 */

#include "pattern.h"

PyObject *RegExprCompileFlag;
PyObject *RegExprFooFlag;

extern PyObject *Err_Regexpr;
extern PyTypeObject keys;

/* Forward declaration, you know in olden days this was called a "function prototype"*/
PyObject* pattern_methods_compile(pattern_object*, PyObject*, PyObject*);

static PyMethodDef pattern_methods[] = { 
	{"compile", (PyCFunction)pattern_methods_compile, METH_VARARGS, "compile a regular expression, returning a dict"},
	{NULL, NULL, 0, NULL},
};

static int pattern_PyTypeObject_initproc(pattern_object *self, PyObject *args, PyObject *keywords) {
 
   return 0;
}

static PyObject* pattern_PyTypeObject_newfunc(PyTypeObject *ptr_argsv, PyObject *args, PyObject *keywords)
{
    pattern_object* self;
    PyObject *func, *func_args, *func_ret, *expr_func_arg, *flags_func_arg;

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
        Py_XDECREF(self);

        PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), unable to initialize self->dict");
        return NULL;        
    }

    /* The self->dict is constructed, though it is empty. The self->expr and self->flags are assigned values to */

    /* User has explicitly asked us to compile the regular expression, we'll compile the regular expression and but it is never returned individually */
    if (self->flags & REGEXPR_COMPILE_FLAG)
    {
        /* Compile regular expression */
        //func = Py_FindMethod(pattern_methods, (PyObject *)self, "compile");
        if (!PyObject_HasAttrString((PyObject*)self, "compile"))
        {
            Py_XDECREF(self->dict);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), unable to find method \"compile\" to compile the pattern as \"REGEXPR_COMPILE_FLAG\" was used");
            return NULL;
        }

        func = PyObject_GetAttrString((PyObject*)self, "compile");

        if (func == NULL)
        {
            Py_XDECREF(self->dict);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), instanxce of pattern class does not have an attribute by the name of \"compile\" to compile the pattern as \"REGEXPR_COMPILE_FLAG\" was used");
            return NULL;
        }

        func_args =  PyTuple_New(2);

        if (func_args == NULL)
        {
            Py_XDECREF(func);
	        Py_XDECREF(self->dict);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), call to function \"PyTuple_New()\" failed");
            return NULL;
        }

        expr_func_arg = Py_BuildValue("s", self->expr);

        if (expr_func_arg == NULL)
        {
            Py_XDECREF(func);
	        Py_XDECREF(self->dict);
            Py_XDECREF(func_args);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), call to function \"Py_BuildValue()\" failed");
            return NULL;
        }

        flags_func_arg = Py_BuildValue("i", self->flags);

        if (flags_func_arg == NULL)
        {
            Py_XDECREF(func);
	        Py_XDECREF(self->dict);
            Py_XDECREF(func_args);
            Py_XDECREF(expr_func_arg);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), call to function \"Py_BuildValue()\" failed");
            return NULL;
        }

        /* On success it returns 0 */
        if (PyTuple_SetItem(func_args, 0, expr_func_arg) || PyTuple_SetItem(func_args, 1, flags_func_arg))
        {
            PyErr_Clear();

            Py_XDECREF(func);
	        Py_XDECREF(self->dict);
            Py_XDECREF(func_args);
            Py_XDECREF(expr_func_arg);
            Py_XDECREF(flags_func_arg);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), call to function \"PyTuple_SetItem()\" failed");
            return NULL;
        }

        /* 
           Though the arguments to this function are optional but we are explicitly providing them. 
           At this point the self->dict has been constructed and self->expr and self->flags have been passed to the compile function as arguments
         */

        /*
            TODO
            PyCFunction_Call is deprecated in 3.9
            https://stackoverflow.com/questions/26716711/documentation-for-pycfunction-new-pycfunction-newex
         */    
        //func_ret = PyCFunction_Call(func, func_args, NULL);
        /* 
            https://stackoverflow.com/questions/3789881/create-and-call-python-function-from-string-via-c-api
         */
        func_ret = PyObject_CallObject(func, func_args);        
        if (func_ret == NULL)
        {
            Py_XDECREF(func);
	        Py_XDECREF(self->dict);
            Py_XDECREF(func_args);
            Py_XDECREF(expr_func_arg);
            Py_XDECREF(flags_func_arg);
            Py_XDECREF(self);

            PyErr_SetString(Err_Regexpr, "iter.c, in pattern_PyTypeObject_newfunc(), call to function \"PyCFunction_Call()\" failed");
            return NULL;
        }
    }
    
    return (PyObject*)self;
}

static PyObject* pattern_methods_compile(pattern_object* self, PyObject* args, PyObject* keywords)
{
    const unsigned int flags;	
    const char* expr; /* This holds pointer to converted Python string to C pointer to character string which is null terminated */
    PyObject *dict, *value;

    size_t len, i = 0;

    /* _PyObject_New() of Objects/object.c */
    keys_object* key;
    
    if (!PyArg_ParseTuple(args, "si", &expr, &flags))
    {
        PyErr_Clear();

        /* At least at this point it is clear that it is not an internal call. The internal call always gives both of the optional arguments */

        if (!PyArg_ParseTuple(args, "s", &expr))
        {
            PyErr_Clear(); 	      
          
            /* It is an external command, we're requesting to compile the previously provided pattern */
            if (!PyDict_Size(self->dict))
            {          
                Py_XINCREF(self->dict);

                dict = self->dict;
	            expr = self->expr;
	            *((int *)&flags) = (self->flags | REGEXPR_COMPILE_FLAG);
            }
	        else
            {
                Py_XINCREF(self->dict);
	            dict = self->dict;

	            goto out;
            }		 
        } 
        else
        {
             /* This was an external call with one required argument */  
	         dict = PyDict_New();
	         if (dict == NULL)
             {
                 goto out;
             }

             *((int *)&flags) = REGEXPR_COMPILE_FLAG;	      
        }	      
    }
    else
    {
         /* The both optional arguments are given. Check if compile() is explicitly called(externally) by the user or compile() is called internally */

         if (!strcmp(expr, self->expr) && flags == self->flags)
         { 
             /* compile() is called internally */
             if (PyDict_Size(self->dict))
             {
                 /* Internal call asks for the recompile of expr(pattern). compile() does not do the recompile */
                 dict = self->dict;
	             Py_XINCREF(dict);

                 goto out;
             }
	        else if (flags & REGEXPR_COMPILE_FLAG)
            {
                /* This is an internal call, request to call the pattern which is still not compiled */

                dict = self->dict;
                Py_XINCREF(dict);
            }
            else
            {
                /* Very bad Internal call, an exception should be raised here */
                Py_XINCREF(Py_None);
	            dict = Py_None;

                goto out;	    
            }		 		 
        }
        else
        {
            /* It is an external call, we'll not use the self->dict and construct a new dict */
            dict = PyDict_New();
	        if (dict == NULL)
            {
                goto out;
            }            

            Py_XINCREF(dict); 
        }	      
   } 	   
      		     
    /* Finaly compile the pattern. The variables expr, flags and dict are all valid live and working well */

    while (expr[i] != '\0')
    {
        switch (expr[i] & 0xff)
        {
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
            case '/':
                key = PyObject_New(keys_object, &keys);
	            if (key != NULL)
                { 
                    key->sub_pattern_object_ptr = NULL;
                    key->handler = slash_handler;                                  
	                len = strlen(SLASH_CHARACTER);
	                /* size_t */
	                //*(int *)(&key->index) = i;                    
	                key->index = i;
	                *(int *)(&key->type) = SLASH_CHARACTER_N;
	                key->type_str = malloc(len + 1);
	                if (key->type_str != NULL)
                    {
                        strcpy((char *)key->type_str, SLASH_CHARACTER);
		                *((char *)key->type_str + len) = '\0';
		                //value = PyString_FromStringAndSize(expr + i, 1);
                        value = PyUnicode_FromStringAndSize(expr + i, 1);
                        //value = PyUnicode_New(1, expr + i);

		                if (value != NULL)
                        {                               
                            Py_XINCREF(key);
		                    Py_XINCREF(value);

		                    if (PyDict_SetItem(dict, (PyObject *)key, value) < 0)
                            {                                
		                        Py_XDECREF(key);
		                        Py_XDECREF(value);
		                        PyErr_Clear();
                            }   	
                    	}
                    }
                }                    
                else
                {
	                 PyErr_Clear();     
                }
            break;
	        default:                                
	            key = PyObject_New(keys_object, &keys);
	            if (key != NULL)
                { 
                    key->sub_pattern_object_ptr = NULL;  
                    key->handler = default_handler;                 
	                len = strlen(ORDINARY_CHARACTER);
	                /* size_t */
	                //*(int *)(&key->index) = i;
	                key->index = i;
	                *(int *)(&key->type) = ORDINARY_CHARACTER_N;
	                key->type_str = malloc(len + 1);
	                if (key->type_str != NULL)
                    {
                        strcpy((char *)key->type_str, ORDINARY_CHARACTER);
		                *((char *)key->type_str + len) = '\0';
		                //value = PyString_FromStringAndSize(expr + i, 1);
                        value = PyUnicode_FromStringAndSize(expr + i, 1);
                        //value = PyUnicode_New(1, expr + i);

		                if (value != NULL)
                        {                               
                            Py_XINCREF(key);
		                    Py_XINCREF(value);

		                    if (PyDict_SetItem(dict, (PyObject *)key, value) < 0)
                            {                                
		                        Py_XDECREF(key);
		                        Py_XDECREF(value);
		                        PyErr_Clear();
                            }   			   		   
                        }
		                else 
                        {                            
                            PyErr_Clear();
                        }
                    }
                }
	            else
                {
	                 PyErr_Clear();     
                }
	        break;
        }

        i++;
    }

out:        
    return (PyObject*)self;
}

static Py_ssize_t pattern_as_sequence_length(pattern_object* self)
{
    Py_ssize_t ret = 0;

    if (self->dict)
    {
        ret = PyDict_Size(self->dict);
    }
    return ret;
}

static PyMemberDef pattern_object_members[] = {
   {"expr", T_STRING, offsetof(pattern_object, expr), 0, "const char argv[]"},
   {"flags", T_INT, offsetof(pattern_object, flags), 0, "const unsigned int flags"},
   {NULL},
};

static PyObject* pattern_as_sequence_item(pattern_object *self, Py_ssize_t i)
{
    PyObject *key = NULL, *value = NULL, *list = PyList_New(4);
    Py_ssize_t n = 0, pos = 0;

    if (self->dict)
    {
        n = PyDict_Size(self->dict);
    }

    if (!n)
    {
        PyErr_SetString(Err_Regexpr, "iter.c, in pattern_as_sequence_item(): dictionary is empty");
        return NULL; 
    }

    if (i < 0)
    {
        PyErr_SetString(Err_Regexpr, "iter.c, in pattern_as_sequence_item(): whole number was expected as an inedx(or subscript), negative integer was provided instead");
        return NULL; 
    }

    if (i > n)
    {        
        PyErr_SetString(Err_Regexpr, "iter.c, in pattern_as_sequence_item(): index(or subscript) out of range");
        return NULL;
    }

    while (PyDict_Next(self->dict, &pos, &key, &value))
    {
        if (((keys_object*)key)->index == i)
        {   
            PyList_SetItem(list, 0, PyLong_FromLong(((keys_object*)key)->type));
            PyList_SetItem(list, 1, PyUnicode_FromString(((keys_object*)key)->type_str));

            Py_XINCREF(value);
            PyList_SetItem(list, 2, value);
            Py_XINCREF(key);
            PyList_SetItem(list, 3, key);

            return list;
        }
    }    

    Py_XINCREF(Py_None);
    return (PyObject *)Py_None;
}

static PySequenceMethods pattern_as_sequence = {
    (lenfunc)pattern_as_sequence_length, /* sq_length, used by len() sugar */
    (binaryfunc)NULL, /* sq_concat used by + sugar */
    (ssizeargfunc)NULL, /* sq_repeat, used by * sugar(as in multiplication) */
    (ssizeargfunc)pattern_as_sequence_item, /* sq_item, used by PySequence_GetItem() and other detail */
    (ssizessizeargfunc)NULL, /* sq_slice */
    (ssizeobjargproc)NULL, /* sq_ass_item */
    (ssizessizeobjargproc)NULL, /* sq_ass_slice */
    (objobjproc)NULL, /* sq_contains */

    /* Added in release 2.0 */
    (binaryfunc)NULL, /* sq_inplace_concat */
    (ssizeargfunc)NULL, /* sq_inplace_repeat */
};

/*
static PyMethodDef pattern_methods[] = { 
	{"compile", (PyCFunction)pattern_methods_compile, METH_VARARGS, "compile a regular expression, returning a dict"},
	{NULL, NULL, 0, NULL},
};
*/

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
   "regexpr.pattern",              /* tp_name, module.typename */ 
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
   (PyMethodDef*)pattern_methods,				      /* tp_methods, PyMethodDef* */
   (PyMemberDef*)pattern_object_members,	/* tp_members, PyMemeberDef* */
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