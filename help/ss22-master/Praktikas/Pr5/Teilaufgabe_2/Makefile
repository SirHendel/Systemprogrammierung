APPNAME=out

$(APPNAME): softlink.o test.o
	gcc -o $(APPNAME) softlink.o test.o

softlink.o: softlink.c
	gcc -c softlink.c

test.o: test.c
	gcc -c test.c

clean:
	rm -f *.o *~ $(APPNAME)
