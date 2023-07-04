all: menu.o abs_max.o abs_min.o diff.o sum.o
        gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu
menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
        gcc -c -std=c99 menu.c
abs_max.o: abs_max.c abs_max.h
        gcc -c -std=c99 abs_max.c
abs_min.o: abs_min.c abs_min.h
        gcc -c -std=c99 abs_min.c
diff.o: diff.c diff.h
        gcc -c -std=c99 diff.c
sum.o: sum.c sum.h
        gcc -c -std=c99 sum.c
