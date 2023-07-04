all: main.o cw_all_func.o  read_and_err.o sent_changes.o structs.o
	gcc main.o cw_all_func.o read_and_err.o sent_changes.o structs.o -o main
main.o: main.c structs.h sent_changes.h read_and_err.h cw_all_func.h
	gcc -c -std=c99 main.c
structs.o: structs.c structs.h
	gcc -c -std=c99 structs.c
sent_changes.o: sent_changes.c sent_changes.h
	gcc -c -std=c99 sent_changes.c sent_changes.h
read_and_err.o: read_and_err.c read_and_err.h
	gcc -c -std=c99 read_and_err.c read_and_err.h
cw_all_func.o: cw_all_func.c cw_all_func.h
	gcc -c -std=c99 cw_all_func.c cw_all_func.h

