CFLAGS = -g -O3 -std=c++17 -W -Werror -fsanitize=address -mfpmath=sse -fstack-protector-all -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=2 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual
REPORT = report
all: a.out $(REPORT)

%.o: %.cpp
	g++ -c $(C++FLAGS) $<
%.out: %.o
	g++ $(C++FLAGS) $^ -o $@

a.out: a.o
a.o: a.cpp

$(REPORT): $(REPORT).tex
	pdflatex $<
	pdflatex $<

clean:
	rm  $(REPORT).aux $(REPORT).log $(REPORT).out $(REPORT).pdf $(REPORT).toc -f *.out *.o -v
