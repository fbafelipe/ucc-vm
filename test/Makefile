CPPFLAGS=-O0 -g -Wall -I../include -I../../libparser/include
LDFLAGS=-L../build -L../../libparser/build -lucc-vm -lparser

all: link run

link: link.o
	g++ $< -o $@ $(LDFLAGS)

run: run.o
	g++ $< -o $@ $(LDFLAGS)

%.o: %.cpp
	g++ $< -o $@ -c $(CPPFLAGS)

clean:
	rm -f link
	rm -f run
	rm -f *.o
