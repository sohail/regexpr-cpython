# src/regexpr.py
# sohail.github.io

from distutils.core import setup, Extension

# regexpr, module name
setup(name="regexpr", version="0.1", 
		ext_modules=[
	           # Take help on Extension module		
	           # To toggle between cross compilation comment or uncomment
		   # the following lines
		   Extension("regexpr", ["regexpr.c", "iter.c", "keys.c"])])
		   #Extension("regexpr", ["regexpr.c", "iter.c", "keys.c"], extra_compile_args=["-m32"], extra_link_args=["--format=elf32-i386", "-m elf-i386", "-oformat elf32-i386"])])


