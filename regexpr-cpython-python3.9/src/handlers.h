#include <stdio.h>

#ifndef     REGEDIT_HANDLERS_H
#define	    REGEDIT_HANDLERS_H

/* 
    This is a default handler, the word default in the name came from the default case in switch statement
    The default in the name also signifies that it will handle all those places in a pattern which does not contain special symbols/characters e.g. + * . etc etc
    All these special symbols and characters have their own handlers...
    Now back to the topic of this default_handler...
    At the moment it is there to handle deletion or replacement of character/s
    The default_handler does "lot of work"(relative phrase) to find the right character in the phrase to delete or replace
    What I think should happen here...
    Each such function update an internal state as such that...
    When this default_handler is called with sub pattern r or/ad d it would treat them replace or delete commands...
    if it also manages to find '/' right before any one of them...
    and if it does not manage to find that special character '/' right before them, then r or/and d are just normal character/s and are there to get deleted or replaced or is part of replacing word/s
 */    
/*
    TODO,
    Because this function and all the other functions which will come before or after this function has to have the same signature list...
    so may be these functions should be made into functions accepting variable number of arguments       
 */
char* default_handler(char*, const char*, const char*);

#endif