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
