#include "bank_account.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// Utility functions used later

// Verify validity of owner value
int owner_is_valid(char* o) {
  int valid = 1;
  // Owner is not NULL
  if (o == NULL) { 
    printf("owner_is_valid: o is NULL, returning invalid\n");
    valid = 0; 
  }
  // Owner has at least 1 character
  if (strlen(o) <= 0) { 
    printf("owner_is_valid: o is shorter than 1 character, returning invalid\n");
    valid = 0; }
//  printf("owner is valid returning %i", valid);
  return valid;
}

int balance_is_valid(float ba) {
  int valid = 1;
  if (ba < 0) { 
    printf("balance_is_valid: balance is less than 0, returning invalid\n");
    valid = 0; 
  }
  return valid;
}

int account_number_is_valid(char* an) {
  int valid = 1;
  // Account Number has at least 1 character
  if (strlen(an) <= 0) { 
    printf("account_number_is_valid: Account number less than 1 character long, returning invalid\n");
    valid = 0; 
  }
  // Account number is all digits
  // Make a string of all digits
  char* digits = "0123456789";
  // Get length of an
  int anlen = strlen(an);
  // Use strspn to get length of substring of an that consist entirely of numbers
  // (which are in digits)
  int dlen = strspn(an, digits);
  // Assert if these are different
  if (dlen != anlen) { 
    printf("account_number_is_valid: account number length (%i) not equal to digit length (%i), returning invalid\n", anlen, dlen);
    valid = 0; 
  }
  return valid;
}

// Create a bank account
bank_account* create_account(char* o, float b, char* an){
  bank_account* ba = NULL;
  
//  printf("Creating account with these params\n\tOwner: %s\n\tAccount Number: %s\n\tBalance: $%.2f\n", o, an, b);
  // If our input is valid, go ahead and create an account
  if (owner_is_valid(o) && balance_is_valid(b) && account_number_is_valid(an)) {
    ba = malloc (sizeof(bank_account));
    if (ba != NULL) {
      // Allocate memory, verify it got malloc'd and copy contents of o into it
      ba -> owner = malloc ((strlen(o) + 1) * sizeof(char));
      if (ba -> owner == NULL) { // Make sure malloc worked
        free (ba -> owner);
        ba -> owner = NULL;
      } else { // If malloc worked, fill up the memory with stuff
        strcpy(ba -> owner, o);
      }

      // Do the same with account_number and an
      ba -> account_num = malloc ((strlen(an) + 1) * sizeof(char));
      if (ba -> account_num == NULL) { // Make sure malloc worked
        free (ba -> account_num);
        ba -> account_num = NULL;
      } else { // If malloc worked, fill up the memory with stuff
        strcpy(ba -> account_num, an);
      }

      // Lastly, do it with balance and b
      ba -> balance = malloc (sizeof(float));
      *(float*)ba -> balance = b;
//      printf("Created account with this nformation\n\tOwner: %s\n\tAccount Number: %s\n\tBalance: $%.2f\n",
//        ba -> owner, ba -> account_num, ba -> balance);
    } else {
      printf("Could not allocate memory for bank account\n");
    }
  }

  return ba;
}

void display_account(bank_account* ba){
  assert (ba != NULL);
  printf("Bank account Information\n\tOwner: %s\n\tAccount Number: %s\n\tBalance: $%.2f\n",
    ba -> owner, ba -> account_num, *(float*)ba -> balance);
}

int deposit(bank_account* ba, float a){
  int valid = 1;
  assert (ba != NULL);
  if (a < 0) {
    valid = 0;
  } else {
    *(float*)ba -> balance += a;
  }
  return valid;
}

int withdraw(bank_account* ba, float a){
  int valid = 1;
  assert (ba != NULL);
  if (a < 0 || a > *(float*)ba -> balance) {
    valid = 0;
  } else {
    *(float*)ba -> balance -= a;
  }
  return valid;
}

void delete_account(bank_account* ba){
  if (ba == NULL) {
    printf("Deletion failed: ba was set to NULL\n");
  } else {
    if (ba -> owner != NULL){ free (ba -> owner); }
    if (ba -> account_num != NULL){ free (ba -> account_num); }
    if (ba -> balance != NULL){ free (ba -> balance); }
    free (ba);
  }
}



