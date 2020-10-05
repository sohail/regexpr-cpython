#include "handlers.h"

char* default_handler(int n, ...)
{   
    va_list valist;

    /* initialize valist for num number of arguments */
    va_start(valist, n);

    /* clean memory reserved for valist */
    va_end(valist);
    
    return (char*)0;
}

