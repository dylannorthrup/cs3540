all: program_name test_read test_write

test_read: test_read.o
	gcc -o test_read test_read.o

test_read.o: test_read.c
	gcc -g -Wall -c test_read.c

test_write: test_write.o
	gcc -o test_write test_write.o

test_write.o: test_write.c
	gcc -g -Wall -c test_write.c

program_name: program_name.o
	gcc -o program_name program_name.o

program_name.o: program_name.c
	gcc -g -Wall -c program_name.c

clean:
	rm -f *o program_name test_read test_write

