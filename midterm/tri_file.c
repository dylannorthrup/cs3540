#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 0

void err_sys (const char* message);
void pdebug (const char* message);

int main(int argc, char **argv) {
  char buf[] = " ";

  // open source file
  int fd1 = open("infile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) { err_sys ("error in open of fd1 for reading"); }
  pdebug("fd1 is open for reading");

  int letters_out = open("letters.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (letters_out < 0) { err_sys ("error in open of letters_out for writing"); }
  pdebug("letters_out is open for writing");

  int digits_out = open("digits.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (digits_out < 0) { err_sys ("error in open of digits_out for writing"); }
  pdebug("digits_out is open for writing");

  int others_out = open("others.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (others_out < 0) { err_sys ("error in open of others_out for writing"); }
  pdebug("others_out is open for writing");

  pdebug("defining 'keep_looping'");
  int keep_looping = 1;
  pdebug("going into the loop");
  while (keep_looping) {
    // This is inefficient, but complies with the assignment as written (which does not specify
    // being able to handle variable sized buffers for this portion of the assignment)
    ssize_t read_amount = read(fd1, &buf, (size_t) 1);
    // Check to see if we got anything
    if (read_amount < 0) {  // This indicates an error
      err_sys("error during read");
    } else if (read_amount == 0) {  // This indicates end of file
      keep_looping = 0;
    }
    
    if(keep_looping) {  // If we're still looping, let's print some stuff out
      if(buf[0] > 47 && buf[0] < 58) { // It's a number
        ssize_t write_amount = write(digits_out, buf, (size_t) 1);
        if (write_amount < (ssize_t) 1) { err_sys ("error writing out digit"); }
      } else if ((buf[0] > 64 && buf[0] < 91) || (buf[0] > 96 && buf[0] < 123)) { // It's a letter
        ssize_t write_amount = write(letters_out, buf, (size_t) 1);
        if (write_amount < (ssize_t) 1) { err_sys ("error writing out letter"); }
      } else {
        ssize_t write_amount = write(others_out, buf, (size_t) 1);
        if (write_amount < (ssize_t) 1) { err_sys ("error writing out other"); }
      } 
    }
  } 
      
  // Now that we're out of the loop, close the file descriptors
  close (fd1);
  close (letters_out);
  close (digits_out);
  close (others_out);
  return (0);
}

void pdebug (const char* message) {
  if (DEBUG)
    printf ("%s\n", message);
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit(0);
}
