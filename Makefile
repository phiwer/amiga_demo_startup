all: main.c test.o
	vc -lamiga -sc -sd -O2 test.o main.c -o main

test.o:
	vasmm68k_mot -Fhunk -o test.o -nosym test.s

