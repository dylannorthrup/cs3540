#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// Function prototypes 
int* get_grades (int* num);
float calculate_average (int grades[], int num_grades);
void display_average (float ave);
float calculate_median (int grades[], int num_grades);
void display_median (float median);
float calc_two_value_average (int i, int j);
float calc_std_dev(int grades[], int num_grades, float ave);
void display_std_dev (float std_dev);
float float_abs_val(float f);

int main () {
  int num_grades;
  int* grades = get_grades (&num_grades);
  if (num_grades == 0) {
    printf ("no grades\n");
  } else {
    float ave = calculate_average (grades, num_grades);
    display_average (ave);
    float median = calculate_median (grades, num_grades);
    display_median (median);
    float std_dev = calc_std_dev (grades, num_grades, ave);
    display_std_dev (std_dev);
    // DEBUG 
//    int i;
//    for (i = 0; i < num_grades; i++) {
//      printf("Element %i is %d\n", i, grades[i]);
//    }
  }  
  return 0;
}

/* Code from rosettacode.com */
int intcmp(const void *aa, const void *bb) {
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
}

/* Take input and build up grades array */
int* get_grades (int* num) {
  assert (num != NULL);
  int* grades = malloc (10 * sizeof (int));
  if (grades == NULL) {
    printf ("out of resources - terminating\n");
    exit(0);
  } else {
    int size = 10;
    *num = 0;
    int grade;
    printf ("enter a grade - negative to terminate: ");
    scanf ("%d", &grade);
    while (grade >= 0) {
      if (*num == size) {
        int* temp = malloc ((2 * size) * sizeof (int));
        int i;
        for (i = 0; i < size; i++) {
          temp[i] = grades[i];
        }
        free (grades);
        grades = temp;
        size *= 2;
      }
      grades[*num] = grade;
      (*num)++;
      printf ("enter a grade - negative to terminate: ");
      scanf ("%d", &grade);
    }
  }
  assert (grades != NULL);
  /* Adding on something to sort the grades array before returning */
  qsort(grades, (*num), sizeof(int), intcmp);
  return grades;
}

// Calculate the average of the array
float calculate_average (int grades[], int num_grades) {
  assert (num_grades > 0);
  int sum = 0;
  int i;
  for (i = 0; i < num_grades; i++) {
    sum += grades[i];
  }
  return (float)sum/num_grades;
}

// Print out the average we calculated 
void display_average (float ave) {
  assert (ave >= 0);
  printf ("average: %f\n", ave);
}

// Return the average of two ints
// ** simpler than allocating a temp array, then filling that array with appropriate values
// ** and passing it to calculate_average, even if it's less pedogogically sound and/or
// ** not re-using code (therefore a bit anti-DRY)
float calc_two_value_average (int i, int j) {
  float ret_val;
  ret_val = (i + j)/2.0;
  return ret_val;
}

// Calculate the median element of the array
// NOTE: requires a sorted array
float calculate_median (int grades[], int num_grades) {
  float ret_val;
  if (num_grades % 2) { // length of array is odd
    ret_val = grades[num_grades/2];
  } else {  // length of array is even
    // In this case, median is the average of the two middle values
    // Find two middle values
    int i = num_grades/2; // This rounds up
    int j = i - 1;  // Get first one
    ret_val = calc_two_value_average(grades[i], grades[j]);
  }
  return ret_val;
}

// Print out the median we calculated 
void display_median (float median) {
  assert (median >= 0);
  printf ("median: %f\n", median);
}


// Print out the standard deviation we calculated 
void display_std_dev (float std_dev) {
  assert (std_dev >= 0);
  printf ("standard deviation: %f\n", std_dev);
}

/* Need something to calculate absolute value for calc_std_dev */
float float_abs_val(float f) {
  /* If this is a negative number, multiply by -1 */
  if (f < 0) {
    f = f * -1;
  }
  /* Return the, now positive, value */
  return f;
}

/* Calculate the standard deviation of an array of integers */
float calc_std_dev(int grades[], int num_grades, float ave) {
  float dev = 0;      /* Standard Deviation */
  float diff = 0;     /* Individual difference of a single calculation */
  float diff_sum = 0; /* Accumulating sum of the square of the differences */
  int i;              /* Counter declaration to shut up the compiler */

  /* Formula for standard deviation is 
   *    (square root of (sum of square of differences between elements and the ave)) / number of elements
   *
   * Iterate through array finding the difference, squaring that and adding it to the difference sum 
   */
  for(i = 0; i < num_grades; i++) {
    diff = float_abs_val(ave - grades[i]);
    diff_sum += (diff * diff);
//    printf("DEBUG [calc_std_dev]: element = %i :: ave = %f :: diff = %f :: diff_sum = %f\n", grades[i], ave, diff, diff_sum);
  }
  /* Take the square root of the sum divided by number of grades and return that */
  dev = sqrt(diff_sum / num_grades);
//  printf("DEBUG [calc_std_dev]: diff_sum = %f :: dev = %f\n", diff_sum, dev);
  return dev;
}
