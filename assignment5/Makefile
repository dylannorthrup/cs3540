all: reverse_copy last_occurance double_space

reverse_copy.o: reverse_copy.c
	gcc -g -Wall -c reverse_copy.c

reverse_copy: reverse_copy.o 
	gcc -o reverse_copy reverse_copy.o
	rm -f outfile.txt

last_occurance.o: last_occurance.c
	gcc -g -Wall -c last_occurance.c

last_occurance: last_occurance.o 
	gcc -o last_occurance last_occurance.o

double_space.o: double_space.c
	gcc -g -Wall -c double_space.c

double_space: double_space.o 
	gcc -o double_space double_space.o
	rm -f doubleout.txt

clean:
	rm -f *.o reverse_copy last_occurance double_space outfile.txt doubleout.txt
