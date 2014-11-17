all: stopwatch 

testprog: stopwatch
	./test.sh

stopwatch: stopwatch.o
	gcc -o stopwatch stopwatch.o

stopwatch.o: stopwatch.c
	gcc -g -Wall -c stopwatch.c

clean:
	rm -f *o stopwatch 

