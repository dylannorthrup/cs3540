all: fp_test tri_file appearance_locations

appearance_locations: appearance_locations.o
	gcc -o appearance_locations appearance_locations.o

appearance_locations.o: appearance_locations.c
	gcc -g -Wall -c appearance_locations.c

tri_file: tri_file.o
	gcc -o tri_file tri_file.o

tri_file.o: tri_file.c
	gcc -g -Wall -c tri_file.c

fp_test: football_player.o fp_test.o
	gcc -o fp_test football_player.o fp_test.o

football_player.o: football_player.c football_player.h
	gcc -g -Wall -c football_player.c

fp_test.o: fp_test.c football_player.h
	gcc -g -Wall -c fp_test.c

clean:
	rm -f *o fp_test tri_file appearance_locations digits.txt letters.txt others.txt

