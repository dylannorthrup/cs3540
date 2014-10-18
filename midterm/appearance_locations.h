#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Keep track of locations in a linked list since it's easier to grow
// dynamically
// Bits in the list
typedef struct char_loc char_loc;
typedef struct location_list location_list;

struct char_loc {
  int loc;
  char_loc* next;
};

// And the list itself. Since I'm just growing it, I'm not doing anything
// other than stringing ints together, so this is really barebones
struct location_list {
  char_loc* front;
  char_loc* rear;
};

// Function prototypes
void err_sys (const char* message);
void record_locations (location_list* ll, char buf[], int amount, char* tgt);
void display_locations (location_list* ll);
location_list* create_list();
char_loc* create_location(int num);
void add_location(location_list* ll, int n);
