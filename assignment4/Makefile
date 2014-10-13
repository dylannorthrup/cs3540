all: test_list

list.o: list.c
	gcc -g -Wall -c list.c

test_list.o: test_list.c
	gcc -g -Wall -c test_list.c

test_list: test_list.o list.o
	gcc -o test_list test_list.o list.o

clean:
	rm -f *.o test_list
