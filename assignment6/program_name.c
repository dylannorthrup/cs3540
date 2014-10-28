#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Our structure */
typedef struct rec {
  char name[15];
  double price;
  int count;
} rec;

#define DEBUG 1

// Function prototypes

FILE* open_for_writing(char* fname);
FILE* open_for_reading(char* fname);
void add_record(char* fname, char* item, char* price, char* count);
void delete_record(char* fname, char* item);
void print_report(char* fname);
void err_sys (const char* message);
void pdebug (const char* message);
void usage();

int main(int argc, char* argv[]) {

  // Parse arguments to see what we need to do
  if(strcmp(argv[2], "add") == 0 && argc == 6) {
    add_record(argv[1], argv[3], argv[4], argv[5]);
  } else if(strcmp(argv[2], "delete") == 0 && argc == 4) {
    delete_record(argv[1], argv[3]);
  } else if(strcmp(argv[2], "report") == 0 && argc == 3) {
    print_report(argv[1]);
  } else {
    usage();
  }
  exit (0);
}

void usage () {
  printf("Usage: program_name <data_file_name> <action> [options]\n");
  printf("\tPossible actions are 'add', 'delete' and 'report'.\n");
  printf("\tEXAMPLES\n");
  printf("\t\tprogram_name <data_file_name> add <item_name> <item_price> <item_count>\n");
  printf("\t\tprogram_name <data_file_name> delete <item_name>\n");
  printf("\t\tprogram_name <data_file_name> report\n");
  exit (1);
}

// Do these in functions so I can encapsulate the logic
FILE* open_for_writing(char* fname) {
  FILE *fd;
  fd = fopen(fname, "wb");
  if (!fd) {
    err_sys("Unable to open file for writing");
  }
  return fd;
}
FILE* open_for_reading(char* fname) {
  FILE *fd;
  fd = fopen(fname, "rb");
  if (!fd) {
    err_sys("Unable to open file for writing");
  }
  return fd;
}

rec* create_record(char* item, char* price, char* count) {
  double p;
  int c;
  rec* ret_rec;
  p = atof(price);
  c = atoi(count);
  ret_rec = malloc(sizeof(rec));
  strcpy(ret_rec -> name, item);  // Deep copy of contents
  ret_rec -> price = p;
  ret_rec -> count = c;

  // Now, return what we just created
  return ret_rec;
}

void print_record(rec* r) {
  pdebug("Inside print_record");
  assert(r != NULL);
  assert(r -> name != NULL);
  pdebug("print_record: Nothing is NULL");
  double sum = r -> count * r -> price;
  pdebug("print_record: Sum calculated");
  printf("%s       %f  x %d = %f\n", r -> name, r -> price, r -> count, sum);
}

void add_record(char* fname, char* item, char* price, char* count) {
  pdebug("Adding record\n");
  // Open file for reading/writing
  FILE *fd;
  struct rec* my_record;

  // Open up the file
  fd = open_for_writing(fname);

  // Create the record
  my_record = create_record(item, price, count);

  // Print out the record
  print_record(my_record);

  // And add it to the fil
  fwrite(&my_record,sizeof(struct rec),1,fd);

  // And finish up here
  fclose(fd);
//  return 0;
}

void delete_record(char* fname, char* item) {
  err_sys ("Deleting record functionality not implemented yet\n");
}

void print_report(char* fname) {
  err_sys ("Printing report functionality not implemented yet\n");
//  FILE *fd;
//  struct rec* my_record;
}

void pdebug (const char* message) {
  if(DEBUG) { printf ("DEBUG: %s\n", message); }
}

void err_sys (const char* message) {
  printf ("DEBUG: %s\n", message);
  exit(2);
}
