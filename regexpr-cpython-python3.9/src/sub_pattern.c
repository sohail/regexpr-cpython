#include "sub_pattern.h"

static int sub_pattern_PyTypeObject_initproc(sub_pattern_object *self, PyObject *args, PyObject *keywords)
{ 
    return 0;
}

static PyObject* sub_pattern_PyTypeObject_newfunc(PyTypeObject *ptr_argsv, PyObject *args, PyObject *keywords)
{
    return NULL;
}

PyTypeObject sub_pattern = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "regexpr.sub_pattern",                        /* tp_name */
    sizeof(sub_pattern_object),                   /* tp_basicsize */
    0,                        /* tp_itemsize */
    (destructor)0,                   /* tp_dealloc */
    0,      /* tp_vectorcall_offset */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_as_async */
    (reprfunc)0,                        /* tp_repr */
    0,                            /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    (ternaryfunc)0,                     /* tp_call */
    0,                                          /* tp_str */
    (getattrofunc)0,                /* tp_getattro */
    (setattrofunc)0,                /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC |
    Py_TPFLAGS_BASETYPE | Py_TPFLAGS_TYPE_SUBCLASS,                 /* tp_flags */
    sub_pattern_doc,                                   /* tp_doc */
    (traverseproc)0,                /* tp_traverse */
    (inquiry)0,                        /* tp_clear */
    0,                                          /* tp_richcompare */
    0,        /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                               /* tp_methods */
    0,                               /* tp_members */
    0,                               /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,            /* tp_dictoffset */
    sub_pattern_PyTypeObject_initproc,                                  /* tp_init */
    0,                                          /* tp_alloc */
    sub_pattern_PyTypeObject_newfunc,                                   /* tp_new */
    PyObject_GC_Del,                            /* tp_free */
    (inquiry)0,                        /* tp_is_gc */
};