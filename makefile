# makefile

all: main

main: main.o logging.o
	gcc -o main main.o logging.o

main.o: main.c logging.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic -std=gnu11

logging.o: logging.c logging.h
	gcc -o logging.o logging.c -c -W -Wall -ansi -pedantic -std=gnu11

clean:
	rm -rf *.o *~ main
