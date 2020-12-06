
.PHONY: all clean

all: test
	# do nothing

register.o: register.cpp register.hpp
	clang++ -c -o register.o register.cpp

instruction.o: instruction.cpp instruction.hpp
	clang++ -c -o instruction.o instruction.cpp

CPU.o: CPU.cpp CPU.hpp
	clang++ -c -o CPU.o CPU.cpp

test: test.cpp register.o instruction.o CPU.o
	clang++ -o test test.cpp register.o instruction.o CPU.o

#CPU.o: CPU.cpp CPU.hpp register.cpp register.hpp instruction.cpp instruction.hpp
#	clang++ -c -o CPU.o CPU.cpp register.cpp instruction.cpp

#test: test.cpp CPU.o
#	clang++ -o test test.cpp CPU.o

clean:
	rm -rf register.o instruction.o CPU.o test