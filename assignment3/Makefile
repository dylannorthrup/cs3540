test_bank_account: bank_account.o test_bank_account.o
	gcc -o test_bank_account bank_account.o test_bank_account.o

bank_account.o: bank_account.c bank_account.h
	gcc -g -Wall -c bank_account.c

test_bank_account.o: test_bank_account.c bank_account.h
	gcc -g -Wall -c test_bank_account.c

clean:
	rm -f *o test_bank_account

