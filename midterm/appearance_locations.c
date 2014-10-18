#include "appearance_locations.h"
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 10

// Start of actual programming
int main() {

  location_list* locations = create_list();
  char buf[BUFF_SIZE];
  char target[] = "a";
  int current_file_pos = 0;
  // Source file
  int fd1 = open("infile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
    // If we get less data than BUFF_SIZE, this is the last trip through
    if (read_amount < BUFF_SIZE) {
      done = 1;
    }
    // If we have data, we need to account for it
    if (read_amount > 0) {
      record_locations(locations, buf, read_amount, target);
    }
  } while (!done);


  display_locations(locations);

  // Now that we're out of the loop, close the file descriptors
  close (fd1);
  return (0);
}

void record_locations (location_list* ll, char buf[], int amount, char* tgt) {
  int i = 0;
  for (i = 0; i < amount; i++) {
    if (buf[i] == tgt) {
      locations[(int)buf[i]]++;
    }
  }
}

void display_locations (location_list* ll) {
  printf("File locations for target variable: ");
  int loop = 1;
  char_loc* loc = ll -> front;
  while (loop) {
    printf("%d ", loc -> loc);
    if (loc -> next == NULL) {  // If this is the last location
      loop = 0;                 // Break out of the loop
    } else {                    // Otherwise
      loc = loc -> next;        // Point to the next location
    }
  }
  // Print ending newline
  printf("\n");
}

void err_sys (const char* message) {
  printf ("%s\n", message);
  exit(0);
}

// Dynamically grown list to keep track of the locations where 
// our target character appears
location_list* create_list() {
  location_list* l = malloc(sizeof (location_list));
  if (l != NULL) {
    l -> front = NULL;
    l -> rear = NULL;
  }
  return l;
}

// Create a location node inside the location_list
char_loc* create_location(int num) {
  char_loc* l = malloc(sizeof (char_loc));
  if (l != NULL) {
    l -> loc = num;
    l -> next = NULL;
  }
  return l;
}

// Adding a location to the location list
void add_location(location_list* ll, int n){
  assert (ll != NULL);  // Make sure we actually have a list to add to
  char_loc* loc = create_location(n);
  assert (loc != NULL); // Make sure this actually created a location
  // If the front is NULL, this is our first entry
  // Set front to point to the new location we've created
  if (ll -> front == NULL) {
    ll -> front = loc;
  } else {  // Otherwise
    // find what's at the rear of the list
    char_loc* r = ll -> rear;
    // And point that node to the newly created node
    r -> next = loc;
  }
  // And, either way, point the list at the newly created node;
  ll -> rear = loc;
}
  




