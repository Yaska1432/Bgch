CFLAGS = -g -O3 -std=c++17 -W -Werror -fsanitize=address -mfpmath=sse -fstack-protector-all -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual

all: a.out

main.o: main.cpp
record.o: record.cpp
command.o: commands.cpp
data.o: data.cpp

a.out: main.o record.o commands.o data.o
	g++ $(CFLAGS) $^ -o $@
	rm -f *.o
%.o: %.cpp
	g++ -c $(CFLAGS) $< -o $@


clean:
	rm -f *.o
	rm -f *.out
