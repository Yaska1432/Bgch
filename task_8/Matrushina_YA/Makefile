CFLAGS = -g -O3 -std=c++17 -W -Werror -fsanitize=address -mfpmath=sse -fstack-protector-all -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual

all: record.o command.o list2.o database.o a.out
%.o: %.cpp
	g++ -c $(CFLAGS) $<
%.out: %.o
	g++ $(CFLAGS) $^ -o $@
	

a.out: a.o record.o command.o database.o list2.o

record.o: record.cpp record.h
command.o: command.cpp command.h
list2.o: list2.cpp list2.h
database.o: database.cpp database.h

a.o: a.cpp record.h command.h condition.h list.h list_node.h list2.h list_node2.h command_type.h ordering.h operation.h database.h hash_list_node.h hash_list.h hash.h container.h              

clean:
	rm -f *.o *.out