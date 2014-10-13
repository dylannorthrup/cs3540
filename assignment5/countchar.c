#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 10
#define NUM_CHARS 128

void err_sys (const char* message);
void count_buffer (int char_counts[], char buf[], int amount);
void display_counts (int char_counts[]);

int main() {

  char buf[BUFF_SIZE];
  int char_counts [NUM_CHARS];
  int i;
  for (i = 0; i < NUM_CHARS; i++) {
    char_counts[i] = 0;
  }
//  int char_count = 0;
  // Source file
  int fd1 = open("filefile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) {
    err_sys ("error in open of fd1");
  }


  int done = 0;
  do {
    // Try to fill up the buffer with data
    ssize_t read_amount = read (fd1, &buf, BUFF_SIZE);
    // If we get < 0 as a result, there was a problem
    if (read_amount < 0) {
      err_sys ("error in read");
    }
    // If we get less data than BUFF_SIZE, this is the alst trip through
    if (read_amount < BUFF_SIZE) {
      done = 1;
    }
    // If we have data, we need to account for it
    if (read_amount > 0) {
    count_buffer(char_counts, buf, read_amount);
//      char_count += read_amount;
    }
  } while (!done);


  display_counts(char_counts);
//  printf("Had %d characters in file\n", char_count);

  // Now that we're out of the loop, close the file descriptors
  close (fd1);
  return (0);
}

void count_buffer (int char_counts[], char buf[], int amount) {
  int i = 0;
  for (i = 0; i < amount; i++) {
    char_counts[(int)buf[i]]++;
  }
}

void display_counts (int char_counts[]) {
  int i = 0;
  for (i = 0; i < NUM_CHARS; i++) {
    if(char_counts[i] > 0){
      printf("'%c': %d\n", i, char_counts[i]);
    }
  }
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit(0);
}
