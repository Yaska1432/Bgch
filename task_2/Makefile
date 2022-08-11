CFLAGS = -O3 -std=c++14 -mfpmath=sse -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs

a.out: main.o f.o matrix.o
	gcc main.o f.o matrix.o -o a.out
main.o: 
	gcc -c $(CFLAGS) main.c f.c
f.o: f.c matrix.h
	gcc -c $(CFLAGS) f.c
matrix.o:
	gcc -c $(CFLAGS) matrix.c 

clean:
	rm -f *.o
	rm -f *.out
