all: main.c
	vc -c99 -sc -sd -O2 -lamiga test.s main.c -o main

test.o:
	vasmm68k_mot -Fhunk -o test.o -nosym test.s

