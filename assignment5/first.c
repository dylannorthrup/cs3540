#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void err_sys (const char* message);

int main() {
  char buf[] = "Howdy, y'all!";
  int fd = creat("first_file.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0) {
    err_sys ("error in creating file");
  }
  // Write five characters to the file we just opened
  ssize_t amount = write(fd, buf, 5);
  // Make sure the return value from that write is what we expect
  if (amount != 5) { err_sys ("error while writing [did not get a 5 back from write]"); }
  // Move the current file pointer somewhere else in the file
  off_t offset = lseek(fd, 2, SEEK_SET);
  if (offset < 0) { err_sys ("error during lseek."); }
  // Go ahead and start writing again
  amount = write (fd, buf, 8);
  if (amount != 8) { err_sys ("error while writing [did not get an 8 back from write()]"); }

  // Now, let's go crazy
  offset = lseek (fd, 2000, SEEK_CUR);
  if (offset < 0) { err_sys ("error during lseek."); }
  // Now, try to write it out
  amount = write (fd, buf, 13);
  if (amount != 13) { err_sys ("error while writing [did not get an 13 back from write()]"); }
  
  close (fd);
  return 0;
}

void err_sys (const char* message) {
  printf("%s\n", message);
  exit (0);
}