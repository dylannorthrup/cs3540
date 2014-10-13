#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 10

void err_sys (const char* message);

int main() {
  char buf[BUFF_SIZE];
  // Source file
  int fd1 = open("filefile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) {
    err_sys ("error in open of fd1");
  }
  // Destination file
  // We can use creat for this
  //int fd2 = creat("copyfile.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  // Or we can use open and pass in the O_CREAT flag along with the O_WRONLY flag
  int fd2 = open("copyfile.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd2 < 0) {
    err_sys ("error in open of fd2");
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
    // If we have data, we need to write stuff out
    if (read_amount > 0) {
      ssize_t write_amount = write (fd2, buf, read_amount);
      if (write_amount < read_amount) {
        err_sys ("error in writing out data");
      }
    }
  } while (!done);

  // Now that we're out of the loop, close the file descriptors
  close (fd1);
  close (fd2);
  return (0);
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit(0);
}
