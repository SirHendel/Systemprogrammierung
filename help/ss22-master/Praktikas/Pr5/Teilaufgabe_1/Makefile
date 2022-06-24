APPNAME=copy

$(APPNAME): copy.o
	gcc -o $(APPNAME) copy.o

%.o: %.c
	gcc -c -Wall $<

clean:
	rm -f *~
	rm -f out
	rm -f *.o
