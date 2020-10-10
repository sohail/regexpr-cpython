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
            else if ((strlen(pattern) - index) == 1 && pattern[index] == 'r')
            {
                /*
                    Replace command
                 */
            }            
        }
        /* for situations like \/ etc */
        else if (pattern[index] == '\\')
        {            
        }        
    }
    /* index is zero */
    else 
    {
        if (pattern[index] == '/')
        {            
        }
    }

    /*
        It is an ordinary character, not part of regular expression specific character and symbol set 
     */
    
    return (char*)0;
}

char* slash_handler(int n, ...)
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
    
    /* remember that at index you have the slash itself and now you are looking for a situation like /d */
    if ((strlen(pattern) - index) == 2 && pattern[index + 1] == 'd')
    {
        /*
            Delete command
         */        
    }       
    else if (index != 0)
    {
        if (pattern[index - 1] == '^')
        {            
            /*
                Found this special control character 
             */
        }
        /* overriding the special character such as slash itself is */
        else if (pattern[index - 1] == '\\')
        {
            /*
                Default handler will handle thisas well
             */
        }    
        /* case of back to back slashes '//' */
        else if (pattern[index - 1] == '/')
        {
            /*
                Delete command
             */
        }
    }
    /* index is zero, this slash is the very first character of the pattern */
    else
    {
        /*
            Do nothing
         */
    }
                
    return (char*)0;
}



