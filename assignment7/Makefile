all: stopwatch stopwatch2

stopwatch: stopwatch.o
	gcc -o stopwatch stopwatch.o

stopwatch.o: stopwatch.c
	gcc -g -Wall -c stopwatch.c

stopwatch2: stopwatch2.o
	gcc -o stopwatch2 stopwatch2.o

stopwatch2.o: stopwatch2.c
	gcc -g -Wall -c stopwatch2.c

clean:
	rm -f *o stopwatch stopwatch2

