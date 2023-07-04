all: main.o bmp_processing.o print.o cli.o cw_functions.o
	gcc main.o bmp_processing.o print.o cli.o cw_functions.o -lm -o main
main.o: main.c
	gcc -c -std=c99 main.c
bmp_processing.o: bmp_processing.c
	gcc -c -std=c99 bmp_processing.c
print.o: print.c
	gcc -c -std=c99 print.c
cli.o: cli.c
	gcc -c -std=c99 cli.c
cw_functions.o: cw_functions.c
		gcc -c -std=c99 cw_functions.c


