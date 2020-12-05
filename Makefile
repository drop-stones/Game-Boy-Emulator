
.PHONY: all clean

all: test
	# do nothing

register.o: register.cpp register.hpp
	clang++ -c -o register.o register.cpp

CPU.o: CPU.cpp CPU.hpp
	clang++ -c -o CPU.o CPU.cpp

test: test.cpp register.o CPU.o
	clang++ -o test test.cpp register.o CPU.o

clean:
	rm -rf register.o CPU.o test