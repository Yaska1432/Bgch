CFLAGS = -O3
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

a01.out: main1.o f1.o matrix.o
	gcc main1.o f1.o matrix.o -o a01.out
main1.o: main1.c matrix.h
	gcc -c $(CFLAGS) main1.c
f1.o: f1.c matrix.h
	gcc -c $(CFLAGS) f1.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a02.out: main2.o f2.o matrix.o
	gcc main2.o f2.o matrix.o -o a02.out
main2.o: main2.c matrix.h
	gcc -c $(CFLAGS) main2.c
f2.o: f2.c matrix.h
	gcc -c $(CFLAGS) f2.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a03.out: main3.o f3.o matrix.o
	gcc main3.o f3.o matrix.o -o a03.out
main3.o: main3.c matrix.h
	gcc -c $(CFLAGS) main3.c
f3.o: f3.c matrix.h
	gcc -c $(CFLAGS) f3.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a04.out: main4.o f4.o matrix.o
	gcc main4.o f4.o matrix.o -o a04.out
main4.o: main4.c matrix.h
	gcc -c $(CFLAGS) main4.c
f4.o: f4.c matrix.h
	gcc -c $(CFLAGS) f4.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

pa05.out: main5.o f5.o matrix.o
	gcc main5.o f5.o matrix.o -o a05.out
main5.o: main5.c matrix.h
	gcc -c $(CFLAGS) main5.c
f5.o: f5.c matrix.h
	gcc -c $(CFLAGS) f5.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a06.out: main6.o f6.o matrix.o
	gcc main6.o f6.o matrix.o -o a06.out
main6.o: main6.c matrix.h
	gcc -c $(CFLAGS) main6.c
f6.o: f6.c matrix.h
	gcc -c $(CFLAGS) f6.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a07.out: main7.o f7.o matrix.o
	gcc main7.o f7.o matrix.o -o a07.out
main7.o: main7.c matrix.h
	gcc -c $(CFLAGS) main7.c
f7.o: f7.c matrix.h
	gcc -c $(CFLAGS) f7.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a08.out: main8.o f8.o matrix.o
	gcc main8.o f8.o matrix.o -o a08.out
main8.o: main8.c matrix.h
	gcc -c $(CFLAGS) main8.c
f8.o: f8.c matrix.h
	gcc -c $(CFLAGS) f8.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a09.out: main9.o f9.o matrix.o
	gcc main9.o f9.o matrix.o -o a09.out
main9.o: main9.c matrix.h
	gcc -c $(CFLAGS) main9.c
f9.o: f9.c matrix.h
	gcc -c $(CFLAGS) f9.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 

a10.out: main10.o f10.o matrix.o
	gcc main10.o f10.o matrix.o -o a10.out
main10.o: main10.c matrix.h
	gcc -c $(CFLAGS) main10.c
f10.o: f10.c matrix.h
	gcc -c $(CFLAGS) f10.c
matrix.o: matrix.c matrix.h
	gcc -c $(CFLAGS) matrix.c 


clean:
	rm -f *.o
	rm -f *.out
	rm -f b.txt
