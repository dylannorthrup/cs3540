all: program_name 

testprog: program_name
	./test.sh

program_name: program_name.o
	gcc -o program_name program_name.o

program_name.o: program_name.c
	gcc -g -Wall -c program_name.c

clean:
	rm -f *o fname program_name 

