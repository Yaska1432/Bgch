CFLAGS = -O3
all: prog1.exe prog2.exe prog3.exe prog4.exe prog5.exe prog6.exe prog7.exe prog8.exe prog9.exe prog10.exe

prog1.exe: main1.o f1.o
	gcc main1.o f1.o -o prog1.exe
main1.o: main1.c f.h
	gcc -c $(CFLAGS) main1.c
f1.o: f1.c f.h
	gcc -c $(CFLAGS) f1.c 

prog2.exe: main2.o f2.o
	gcc main2.o f2.o -o prog2.exe
main2.o: main2.c f.h
	gcc -c $(CFLAGS) main2.c
f2.o: f2.c f.h
	gcc -c $(CFLAGS) f2.c 

prog3.exe: main3.o f3.o
	gcc main3.o f3.o -o prog3.exe
main3.o: main3.c f.h
	gcc -c $(CFLAGS) main3.c
f3.o: f3.c f.h
	gcc -c $(CFLAGS) f3.c 

prog4.exe: main4.o f4.o
	gcc main4.o f4.o -o prog4.exe
main4.o: main4.c f.h
	gcc -c $(CFLAGS) main4.c
f4.o: f4.c f.h
	gcc -c $(CFLAGS) f4.c 

prog5.exe: main5.o f5.o
	gcc main5.o f5.o -o prog5.exe
main5.o: main5.c f.h
	gcc -c $(CFLAGS) main5.c
f5.o: f5.c f.h
	gcc -c $(CFLAGS) f5.c 

prog6.exe: main6.o f6.o
	gcc main6.o f6.o -o prog6.exe
main6.o: main6.c f.h
	gcc -c $(CFLAGS) main6.c
f6.o: f6.c f.h
	gcc -c $(CFLAGS) f6.c 

prog7.exe: main7.o f7.o
	gcc main7.o f7.o -o prog7.exe
main7.o: main7.c f.h
	gcc -c $(CFLAGS) main7.c
f7.o: f7.c f.h
	gcc -c $(CFLAGS) f7.c 

prog8.exe: main8.o f8.o
	gcc main8.o f8.o -o prog8.exe
main8.o: main8.c f.h
	gcc -c $(CFLAGS) main8.c
f8.o: f8.c f.h
	gcc -c $(CFLAGS) f8.c
	
prog9.exe: main9.o f9.o
	gcc main9.o f9.o -o prog9.exe
main9.o: main9.c f.h
	gcc -c $(CFLAGS) main9.c
f9.o: f9.c f.h
	gcc -c $(CFLAGS) f9.c 
	
prog10.exe: main10.o f10.o
	gcc main10.o f10.o -o prog10.exe
main10.o: main10.c f.h
	gcc -c $(CFLAGS) main10.c
f10.o: f10.c f.h
	gcc -c $(CFLAGS) f10.c 

clean:
	rm -f *.o
	rm -f *.exe
	rm -f b.txt
