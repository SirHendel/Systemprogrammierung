all: libmylib
libmylib: function.o
	ar rcs libmylib.a function.o 

function.o: function.c 
	gcc -c function.c -o function.o 

libs: libmylib.ar

clean: 
	rm -f function *.o *.a 