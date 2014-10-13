#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 0

void err_sys (const char* message);
void pdebug (const char* message);

int main() {
  char newline[] = "\n";
  char buf[] = " ";

  // open source file
  int fd1 = open("infile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) { err_sys ("error in open of fd1 for reading"); }
  pdebug("fd1 is open for reading");

  int fd2 = open("doubleout.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd2 < 0) { err_sys ("error in open of fd2 for writing"); }
  pdebug("fd2 is open for writing");

  pdebug("defining 'keep_looping'");
  int keep_looping = 1;
  pdebug("going into the loop");
  while (keep_looping) {
    ssize_t read_amount = read(fd1, &buf, (size_t) 1);
    // Check to see if we got anything
    if (read_amount < 0) {  // This indicates an error
      err_sys("error during read");
    } else if (read_amount == 0) {  // This indicates end of file
      keep_looping = 0;
    }
    
    if(keep_looping) {  // If we're still looping, let's print some stuff out
      // Check to see if this character is equal to our target
      int match = strncmp(newline, buf, (size_t) 1);
      if(match == 0) {
        ssize_t write_amount = write(fd2, newline, (size_t) 1);
        if (write_amount < (ssize_t) 1) { err_sys ("error writing out newline"); }
      }
      ssize_t write_amount = write(fd2, buf, (size_t) 1);
      if (write_amount < (ssize_t) 1) { err_sys ("error writing out character"); }
    }
  } 
      
  // Now that we're out of the loop, close the file descriptors
  close (fd1);
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
