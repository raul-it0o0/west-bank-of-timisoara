#ifndef WEST_BANK_OF_TIMISOARA_MENUS_H
#define WEST_BANK_OF_TIMISOARA_MENUS_H
#include <stdio.h>
#include "account_operations.h"
#include "helpers.h"
#include "print.h"

void no_match_found_prompt(char *user_input);

int auth(char *first_name,
         char *last_name,
         BankAccount accounts_info[],
         int *accounts_found);

void auth_success(char *first_name,
                  char *last_name,
                  BankAccount *user_accounts,
                  int *accounts_found);


#endif //WEST_BANK_OF_TIMISOARA_MENUS_H
