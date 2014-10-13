#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Average entered grades storing data before calculation */

/* function prototype declaration */
float calc_mean(int *grades, int num_grades);
float calc_std_dev(int grades[], int num_grades, float mean);
float float_abs_val(float f);
int* get_grades(int* num_grades);

int main() {
  int num_grades;
/*  printf("How many grades ya got? ");
  scanf("%d", &num_grades);
  while (num_grades < 0) {
    printf("Number of grades cannot be negative, try again: ");
    scanf("%d", &num_grades);
  } */
  int* grades = get_grades(&num_grades);
  if(num_grades == 0) {
    printf("No grades entered\n");
    return 1;
  }
  float mean = calc_mean(grades, num_grades);
  float std_dev = calc_std_dev(grades, num_grades, mean);
  printf("Average is %f\n", mean);
  printf("Standard Deviation is %f\n", std_dev);

  return 0;
}

int* get_grades(int* num_grades) {
  /* allocate memory for the array */
  int* grades = malloc(10 * sizeof(int));
  if (grades == NULL) {
    // Handle error
  }
  int i;              /* Counter declaration to shut up the compiler */
  for(i = 0; i < &num_grades; i++) {
    printf("Enter a grade: ");
    scanf("%d", &grades[i]);
    while (grades[i] < 0) {
      printf("Number of grades cannot be negative, try again: ");
      scanf("%d", &grades[i]);
    }
  }
  return grades;
}

/* Calculate the mean (average) of an array of integers */
float calc_mean(int *grades, int num_grades) {
  float mean;         /* Mean of the values of the array */
  float sum = 0;      /* Total of the members of the array */
  int i;              /* Counter declaration to shut up the compiler */
  /* Iterate through the array adding each value to the sum */
  for(i = 0; i < num_grades; i++) {
    sum += grades[i];
  }
  /* Divide the sum by the number of grades */
  mean = sum / num_grades;
  return mean;
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
float calc_std_dev(int grades[], int num_grades, float mean) {
  float dev = 0;      /* Standard Deviation */
  float diff = 0;     /* Individual difference of a single calculation */
  float diff_sum = 0; /* Accumulating sum of the square of the differences */
  int i;              /* Counter declaration to shut up the compiler */

  /* Formula for standard deviation is 
   *    square root of (sum of square of differences between elements and the mean) / number of elements) 
   *
   * Iterate through array finding the difference, squaring that and adding it to the difference sum 
   */
  for(i = 0; i < num_grades; i++) {
    diff = float_abs_val(mean - grades[i]);
    diff_sum += (diff * diff);
    printf("DEBUG [calc_std_dev]: element = %i :: mean = %f :: diff = %f :: diff_sum = %f\n", grades[i], mean, diff, diff_sum);
  }
  /* Divide sum by number of grades and return that */
  dev = sqrt(diff_sum) / num_grades;
  printf("DEBUG [calc_std_dev]: diff_sum = %f :: dev = %f\n", diff_sum, dev);
  return dev;
}
