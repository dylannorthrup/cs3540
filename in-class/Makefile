all: test_student

test_student: student.o test_student.o
	gcc -o test_student student.o test_student.o

student.o: student.c student.h
	gcc -g -Wall -c student.c

test_student.o: test_student.c student.h
	gcc -g -Wall -c test_student.c

clean:
	rm *o test_student

