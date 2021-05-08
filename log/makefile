CXX = gcc


all: main

main: main.o log.o
	 $(CXX) main.o log.o -o main

main.o: main.c
	 $(CXX) -c main.c

tensor.o: log.c
	 $(CXX) -c log.c

clean:
	rm -rf *.o

