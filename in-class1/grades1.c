#include <stdio.h>

/* Average of grades. Do calculations immediately */

int main() {
  int count = 0;
  int sum = 0;
  int grade;
  printf("Enter a grade - negative to terminate: ");
  scanf("%d", &grade);
  while (grade >= 0) {
    sum += grade;
    count++;
    printf("Enter a grade - negative to terminate: ");
    scanf("%d", &grade);
  }

  if(count == 0) {
    printf("No grades entered\n");
    return 1;
  }
  float avg = sum / count;
  printf("Average is %f\n", avg);

  return 0;
}
