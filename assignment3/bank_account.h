#ifndef _BANK_ACCOUNT_H
#define _BANK_ACCOUNT_H

typedef struct {
  char* owner;
  char* account_num;
  float* balance;
} bank_account;


/* create_account
  * input: owner, initial balance, account number
  * output: pointer to a bank account
  * return NULL is any input is not valid
  */
bank_account* create_account(char* o, float b, char* an);

/* display_account
  * input - pointer to a bank account 
  * displays all attributes of the account - format not specified
  * assertion used to verify pointer to the bank account is not NULL
  */
void display_account(bank_account* ba);

/* deposit
  * input - pointer to bank account (cannot be NULL) & amount of deposit (must be positive)
  * postcondition: amount has been added to balance
  * returns false if amount of deposit is not positive - true otherwise
  * assertion used to verify pointer to the bank account is not NULL
  */
int deposit(bank_account* ba, float a);

/* withdraw
  * input - pointer to bank account (cannot be NULL) & amount of withdrawal (must be positive & cannot be larger than the balance
  * postcondition: amount has been subtracted from balance
  * returns false if amount of withdrawal is not valid - true otherwise
  * assertion used to verify pointer to the bank account is not NULL
  */
int withdraw(bank_account* ba, float a);

/* delete_account
  * input - pointer to bank account 
  * postcondition: all memory allocated to the bank account has been deallocated
  * does nothing if input pointer is NULL
  */
void delete_account(bank_account* ba);


#endif
