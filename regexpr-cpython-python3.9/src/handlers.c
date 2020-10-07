#include "handlers.h"

char* default_handler(int n, ...)
{  
    char *phrase, *pattern; 
    size_t index;
    va_list valist;

    /* initialize valist for num number of arguments */
    va_start(valist, n);

    phrase = va_arg(valist, char*);
    pattern = va_arg(valist, char*);
    index = va_arg(valist, size_t);

    /* clean memory reserved for valist */
    va_end(valist);

    /*if (pattern[index] == 'r' || pattern[index] == 'd')
    {
             
    }*/
    
    if (index != 0)
    {
        if (pattern[index - 1] == '/')
        {
            if ((strlen(pattern) - index) == 1 && pattern[index] == 'd')
            {
                /*
                    Delete command
                 */
            }            
        }        
    }

    /*
        It is an ordinary character, not part of regular expression specific character and symbol set 
     */
    
    return (char*)0;
}

char* slash_handler(int n, ...)
{          
    va_list valist;

    /* initialize valist for num number of arguments */
    va_start(valist, n);


    /* clean memory reserved for valist */
    va_end(valist);
    
    return (char*)0;
}



