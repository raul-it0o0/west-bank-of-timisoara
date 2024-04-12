#ifndef PROGRAMMING_PROJECT_AUTH_SUCCESS_H
#define PROGRAMMING_PROJECT_AUTH_SUCCESS_H
#include "../auth/auth.h"
#include "../user_inputs/user_inputs.h"

void auth_success(char *first_name,
                  char *last_name,
                  struct account *user_accounts,
                  int *accounts_found);

void view_accounts(char *first_name,
                   struct account *user_accounts,
                   const int *accounts_found);

#endif //PROGRAMMING_PROJECT_AUTH_SUCCESS_H
