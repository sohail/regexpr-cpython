# regexpr/Makefile
# sohail.github.io

all		: argsv regexpr

argsv		:
		make -C argsv-cpython

regexpr		:
		make -C regexpr-cpython

install		:
		make -C argsv-cpython install
		make -C regexpr-cpython install

clean		:
		make -C argsv-cpython clean
		make -C regexpr-cpython clean

