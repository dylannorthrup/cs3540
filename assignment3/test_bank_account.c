#include "bank_account.h"
#include <stdio.h>

void print_account_if_operation_succeeded(int result, bank_account* ba) {
  if(result == 1){
    display_account(ba);
  } else {
    printf("Previous operation returned %i (which isn't 1 and indicates a failure)\n", result);
  }
}

int main() {
  printf ("-------- Starting test run --------\n");
  // Make sure this thing works
  printf("Creating initial account\n");
  bank_account* ba = NULL;
  ba = create_account("Dude", 200.00, "12345");
  if (ba != NULL) {
    display_account(ba);
  } else {
    printf ("Could not create a bank account\n");
  }
  // Add some money
  int result;
  printf("Depositing $400\n");
  result = deposit(ba, 400.00);
  print_account_if_operation_succeeded(result, ba);
  printf("Withdrawing $350\n");
  withdraw(ba, 350.00);
  print_account_if_operation_succeeded(result, ba);
  
  // Try to deposit a negative number
  printf("Depositing -$400\n");
  result = deposit(ba, -400.00);
  print_account_if_operation_succeeded(result, ba);
  // And withdraw a negative number
  printf("Withdrawing -$50\n");
  withdraw(ba, -50.00);
  print_account_if_operation_succeeded(result, ba);
  // Withdraw more than the balance
  printf("Withdrawing $900\n");
  withdraw(ba, 900.00);
  print_account_if_operation_succeeded(result, ba);
  

  printf("Deleting account\n");
  delete_account(ba);
  display_account(ba);

  // Test assertion if ba = null
  ba = NULL;
  delete_account(ba);

// These all assert and stop the program. Uncomment and run to test.
//  result = deposit(ba, 400.00);
//  result = withdraw(ba, 400.00);
//  display_account(ba);

  return 0;
}
