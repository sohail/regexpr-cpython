#!/usr/bin/python -O

""" Allah, The ONE and The ONLY ONE 
    Who created Hydrogen and Hellium
    and made Energy and Matter commutative(E=MC^2) """ 
    

""" 
          regexpr, edit a file with regular expression[s] 
                Written by, soni@sharingeconomy.pk
  --------------------------------------------------------------
    ----------------------------------------------------------
      ------------------------------------------------------

    A general purpose script to clean text files from what ever qualifies as nasty.
    The nastiness of text is determined by one or more regular expressions

    Example usage:- ...
          $ regedit file [file ...] reg exp [exp ...]
          $ regedit foo bar baz reg '/b//' '/ar/bar/g' text 
"""

def main():    
    try:        
        """
            expr is a class, it understands the regular expressions very well. 
            Either the expr class will compile the regular experssion or else... 
            provides the set of methods, which others would use and compile the regular expression. 
            The regexpr.re class uses the regexpr.expr class to find the sub string. 
            The regexpr.REGEXPR_COMPILE_FLAG makes it compile the pattern. 
            Here o is an instance of pattern(a.k.a regexpr.expr) class

            The regexpr.REGEXPR_FOO_FLAG is dummy, does nothing flag; implemented just for study purposes
        """
        o = regexpr.expr("^/foo/d", regexpr.REGEXPR_COMPILE_FLAG | regexpr.REGEXPR_FOO_FLAG)

        # Supports sq_length(). Returns Py_ssize_t
        print (len(o))
        print (o[1])               
    except (regexpr.error) as e:
        print (e)	 


"""
Every module has a name and statements in a module can find out the name of its
module. This is specially handy in one particular situation - when a module is
imported for the first time, the main block in that module is run. What if we 
want to run the block only if the program was used by itself and not when it 
was imported from another module? This can be achieved using the __name__ 
attribute of the module.
"""
if __name__ == "__main__":

   import sys

   try:
      import regexpr

      # single exit point, main()'s return value will be our exit status
      sys.exit(main())
   except (ImportError) as e:
      print (e)	   
	
