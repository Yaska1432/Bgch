#CFLAGS = -O3 -g -pthread -std=c++14 -mfpmath=sse -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -fsanitize=address
#LFLAGS = -fsanitize=address
CFLAGS = -O3 -pthread -std=c++14 -mfpmath=sse -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
LFLAGS =
all: a.out

a.out: main.o matrix.o synchronize.o
	   gcc $(LFLAGS) $^ -o a.out
main.o: main.c f.h
	   gcc -c $(CFLAGS) $<
matrix.o: matrix.c f.h synchronize.h
	   gcc -c $(CFLAGS) $<
synchronize.o: synchronize.c synchronize.h
	   gcc -c $(CFLAGS) $<

clean:
	rm -f *.o *.out


