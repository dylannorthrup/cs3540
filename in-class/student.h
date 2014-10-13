#ifndef _STUDENT_H
#define _STUDENT_H

#define MAX_GPA 4.0
#define NULL 0

#define PROBATION_THRESHOLD 2.0

typedef struct {
  char* name;
  char* student_num;
  float gpa;
} student;

/**************************************************************
 * preconditions:
 * n cannot be NULL and cannot be empty
 * num cannot be NULL and must be of the appropriate format
 * 0 <= average <= MAX_GPA
 * return null if a precondition is not valid
 * returns a pointer to a student
 **************************************************************/

student* create_student (const char* n, const char* num, float ave);


/**************************************************************
 * precondition: s is not NULL (checked with assertion)
 * postcondition: all memory allocated to s has been deallocated
 **************************************************************/
void destroy_student (student* s);

/**************************************************************
 * precondition: s is not NULL (checked with assertion)
 * postcondition: student has been displayed on stdout
 **************************************************************/
void display_student (const student* s);

/**************************************************************
 * precondition: s is not NULL (checked with assertion)
 * returns whether s is on probation
 **************************************************************/
int is_on_probation (const student* s);

#endif
