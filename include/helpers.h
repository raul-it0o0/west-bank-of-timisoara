#ifndef PROGRAMMING_PROJECT_AUTH_H
#define PROGRAMMING_PROJECT_AUTH_H
#define MAX_CHARS_PER_LINE 1024
#define MAX_CHARS_FOR_NAME 50
#include <stdio.h>
#include <stdbool.h>
#include "stb_ds.h"
#include "print.h"

typedef struct BankAccount {

    char iban[16];
    char currency[3];
    long double balance;

} BankAccount;
BankAccount* bank_account_init(int currency_code, const char *first_name, const char *last_name);
void bank_account_destroy(BankAccount* this);

typedef struct User {

    char* first_name;
    char* last_name;
    BankAccount** owned_bank_accounts;

} User;
User* user_init(const char *first_name, const char *last_name);
void user_destroy(User* this);

void capitalize_str(char *str);
void generate_iban(const char *first_name, const char *last_name, char *iban);
bool unique_iban(const char* iban);

void get_matches(User* user);

#endif //PROGRAMMING_PROJECT_AUTH_H
