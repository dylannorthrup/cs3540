#include "student.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int is_name_valid (const char* n) {
  return n != NULL && strlen (n) > 0;
}

int is_num_valid (const char* num) {
  int result = 0;
  if (num != NULL && strlen (num) == 9){
    int i = 0;
    while (i < strlen(num) && isdigit (num[i])) {
      i++;
      if (i == strlen(num)){
        result = 1;
      }
    } 
  }
  return result;
}

int is_gpa_valid (float ave) {
  int result = 0;
  if (ave > 0 && ave <= MAX_GPA) {
    result = 1;
  }
  return result;
}

student* create_student (const char* n, const char* num, float ave) {
  student* s = NULL;
  if (is_name_valid (n) && is_num_valid (num) && is_gpa_valid (ave)) {
    s = malloc (sizeof(student));
    if (s != NULL) {
      s -> name = malloc ((strlen(n) + 1) * sizeof(char));
      if (s -> name == NULL) {
        free (s);
        s = NULL;
      } else {
        strcpy (s -> name, n);
        s -> student_num = malloc ((strlen (num) + 1) * sizeof (char));
        if (s -> student_num == NULL) {
          free (s -> name);
          free (s);
          s = NULL;
        } else {
          strcpy (s -> student_num, num);
          s -> gpa = ave;
        }
      }
    }
  }
  return s;
}

void destroy_student (student* s) {
  assert (s != NULL);
  if (s -> name != NULL) {
    free (s -> name);
  }
  if (s -> student_num != NULL) {
    free (s -> student_num);
  }
  free (s);
}

void display_student (const student* s) {
  assert (s != NULL);
  if (s -> name != NULL) {
    printf ("name: %s\n", s -> name);
  }
  if (s -> student_num != NULL) {
    printf ("student number: %s\n", s -> student_num);
  }
  printf ("gpa: ");
}

int is_on_probation (const student* s) {
  assert (s != NULL);
  return s -> gpa < PROBATION_THRESHOLD;
}
