#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 10
#define DEBUG 0

void err_sys (const char* message);
void pdebug (const char* message);
static char* reverse(char* str);

int main() {
  char buf_ary[BUFF_SIZE];
  char* buf = buf_ary;
//  char debug_msg_ary[80] = "";
//  char* debug_msg = debug_msg_ary;  // Used for pdebug when I need to substitute a value into the message
  // Source file
  int fd1 = open("infile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd1 < 0) {
    err_sys ("error in open of fd1");
  }
  pdebug("fd1 is open for reading");
  // Destination file
  // We can use creat for this
  //int fd2 = creat("copyfile.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  // Or we can use open and pass in the O_CREAT flag along with the O_WRONLY flag
  int fd2 = open("outfile.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd2 < 0) {
    err_sys ("error in open of fd2");
  }
  pdebug("fd2 is open for writing");


//  int done = 0;
//  do {
//    buf = reverse(buf);
//    ssize_t read_amount = read (fd1, buf, BUFF_SIZE);
//    printf("read %d bytes\n", (int) read_amount);
//    if (read_amount < 0) { err_sys ("error in read"); }
//    if (read_amount < BUFF_SIZE) { done = 1; }
//    if (read_amount > 0) {
//      ssize_t write_amount = write (fd2, buf, read_amount);
//      if (write_amount < read_amount) { err_sys ("error in write"); }
//    }
//  } while (!done);

  // Seek to the end of the source file
  int fsize = lseek(fd1, -1, SEEK_END);
  pdebug("lseek to end of fd1");

  // Algorithm
  //
  //  Check to make sure fsize > BUFF_SIZE
  //  If fsize < BUFF_SIZE {
  //    Read in from 0 and read in fsize bytes into buf
  //    start from end of buf (which is fsize long now) and write chars to fd2
  //    exit loop
  //  } else {
  //    fsize -= BUFF_SIZE
  //    Read in BUFF_SIZE bytes starting from fsize
  //    start from end of buf (which is BUFF_SIZE long) and write chars to fd2
  //  }

  pdebug("defining 'keep_looping'");
  int keep_looping = 1;
  pdebug("defining 'this_many'");
  int this_many = BUFF_SIZE;
  pdebug("going into a loop");
  while (keep_looping) {
    pdebug("- doing a loop");
    // If fsize =< BUFF_SIZE 
    if (fsize <= BUFF_SIZE) {
      pdebug("- fsize <= BUFF_SIZE");
    //   move file pointer to zero
      lseek(fd1, (off_t) 0, SEEK_SET);
    //   set read amount to fsize
      this_many = fsize;
    //   unset loop variable to exit loop
      keep_looping = 0;
    } else {
      pdebug("- fsize > BUFF_SIZE");
    //   decrease fsize by BUFF_SIZE
      fsize -= BUFF_SIZE;
      pdebug("- fsize decremented by BUFF_SIZE");
    //   Move file pointer to fsize
      lseek(fd1, (off_t) fsize, SEEK_SET);
    }
    pdebug("Done with setting vars. About to read data");
    // Read in this_many bytes starting from fsize
    ssize_t read_amount = read (fd1, buf, this_many);
    pdebug("Data read in");
    // Make sure we got the expected amount
    if (read_amount != this_many) {
      pdebug("read_amount was not equal to this_many");
      char msg[80]; // 80 chars should be enough
      sprintf(msg,"error in file read. Read in %d bytes but expected %d", (int) read_amount, this_many);
      err_sys (msg);
    }
    pdebug("SUCCESS: read_amount was equal to this_many");
    if (read_amount > 0) {
      pdebug("shuffling buf off to reverse");
      // Pass reversing off to reverse function
      buf = reverse(buf);
      // Write (now reversed) buf to fd2
      pdebug("writing buf to fd2");
      ssize_t write_amount = write (fd2, buf, read_amount);
      if (write_amount < read_amount) {
        //printf("buf size: %d\n", sizeof(buf));
        //printf("write_amount: %d\n", write_amount);
        err_sys ("error in writing out data");
      }
    }
 }

  // Now that we're out of the loop, close the file descriptors
  close (fd1);
  close (fd2);
  return (0);
}

// Copied from http://www.perlmonks.org/?node_id=589993
static char* reverse(char* str) {
  pdebug("reverse: allocating variables");
  pdebug("reverse: allocating left");
  char* left  = str;
  //printf("%s", left);
  pdebug("reverse: getting length of str");
  int str_length = strlen(str) - 1;
  pdebug("reverse: allocating right");
  char* right = left + str_length;
  pdebug("reverse: allocating tmp");
  char  tmp;
  pdebug("reverse: Going into while loop");
  while (left < right) {
    tmp      = *left;
    *left++  = *right;
    *right-- = tmp;
  }
  return str;
}

void pdebug (const char* message) {
  if (DEBUG)
    printf ("%s\n", message);
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit(0);
}
