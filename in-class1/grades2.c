#include <stdio.h>

/* Average entered grades storing data before calculation */

int main() {
  int num_grades;
  printf("How many grades ya got? ");
  scanf("%d", &num_grades);
  int grades[num_grades];
  int i;
  for(i = 0; i < num_grades; i++) {
    printf("Enter a grade - negative to terminate: ");
    scanf("%d", &grades[i]);
  }

  if(num_grades == 0) {
    printf("No grades entered\n");
    return 1;
  }
  float avg = sum / count;
  printf("Average is %f\n", avg);

  return 0;
}
