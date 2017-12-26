# src/Makefile
# sohail.github.io


all		: regexpr.h regexpr.c iter.h iter.c keys.h keys.c regexpr.py
		python regexpr.py build


install		:
		cp ./build/lib*/regexpr.so ./../../

clean		:
		rm -rf build
