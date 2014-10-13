#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 0

void err_sys (const char* message);
void pdebug (const char* message);

int main() {
  char buf[] = " ";
  // Optional targets
  //char target[] = "B";
  //char target[] = " ";
  char target[] = "D";
  //char target[] = "q";
  int where_is_it = -1;

  // open source file
  int fd1 = open("infile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) {
    err_sys ("error in open of fd1");
  }
  pdebug("fd1 is open for reading");

  // Seek to the end of the source file
  int fsize = lseek(fd1, -1, SEEK_END);
  pdebug("lseek to end of fd1");
//  printf("file size is %d bytes\n", (int) fsize);

  pdebug("defining 'keep_looping'");
  int keep_looping = 1;
  pdebug("going into the loop");
  while (keep_looping) {
    ssize_t read_amount = read(fd1, &buf, (size_t) 1);
//    printf("post-read: buf contains '%c' at fsize %d\n", buf[0], fsize);
    if (read_amount != 1) {
      //printf("read %d bytes\n", (int) read_amount);
      //printf("post read: buf contains '%c' \n", buf[0]);
      err_sys("read_amount was not equal to 1");
    }
    // Check to see if this character is equal to our target
    int match = strncmp(target, buf, (size_t) 1);
    if(match == 0) {
      // Print out a thing saying we're there (if we're debugging)
      pdebug("THEY MATCH!!!");
      // Set where_is_it to fsize (which is where in the file it's located)
      where_is_it = fsize;
      // And break out of the loop
      keep_looping = 0;
    } else {  // Otherwise
      // Check to see if we're at the beginning of the file
      if(fsize <= 0){
        keep_looping = 0;
      }
      // If not, move backward in the file one byte
      fsize--;
      // And lseek there
      lseek(fd1, (off_t) fsize, SEEK_SET);
    }
  } 
      
  // If where_is_it is not -1, we found the character
  if(where_is_it != -1) {
    printf("Found target character '%s' at byte %d in file.\n", target, where_is_it);
  } else {
    printf("Could not find target character '%s' in file\n", target);
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
