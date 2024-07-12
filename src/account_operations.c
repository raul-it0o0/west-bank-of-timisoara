#include "account_operations.h"

void view_accounts(const User* session_user) {

    clear_screen();

    int account_count = arrlen(session_user->owned_bank_accounts);

    if (account_count == 0) {
        printf("%s, you have no accounts to view.\n\n", session_user->first_name);
        pause();
        return;
    }

    printf("%s, you have %d account(s) at our bank:\n", session_user->first_name, account_count);

    for (int i = 0; i < account_count; i++) {
        printf("=======================================================\n");
        printf("Account #%d ( %s )\n\n", i+1, session_user->owned_bank_accounts[i]->iban);
        printf("%0.2Lf %s\n\n",
               session_user->owned_bank_accounts[i]->balance,
               session_user->owned_bank_accounts[i]->currency);
        printf("=======================================================\n");
    }

    pause();

}

void new_account(User *session_user, bool authenticated) {

    clear_screen();

    unsigned char response = 0;

    if(!authenticated) {
        printf("\nYou last entered the following credentials:\n");
        printf("First Name: %s\n", session_user->first_name);
        printf("Last Name: %s\n", session_user->last_name);

        printf("\nWould you like to:\nInput new credentials [Y]; or"
               "\nKeep this data for the new account [n]\n\n");
        scanf(" %c", &response);

        if (response == 'Y') {

            memset(session_user->first_name, '\0', MAX_CHARS_FOR_NAME);
            memset(session_user->last_name, '\0', MAX_CHARS_FOR_NAME);

            printf("\nEnter new first name: ");
            scanf(" %s", session_user->first_name);

            printf("Enter new last name: ");
            scanf(" %s", session_user->last_name);

        }
    }

    // Make sure the credentials
    // are written in capitals in the DB
    capitalize_str(session_user->first_name);
    capitalize_str(session_user->last_name);

    clear_screen();

    printf("Choose your currency for your new account.\nOur bank only supports the following currencies:\n\n");
    printf("[1] RON (Romanian Leu)\n");
    printf("[2] EUR (Euro)\n");
    printf("[3] GBP (British Pound)\n");
    printf("[4] USD (US Dollar)\n");
    printf("[5] BTC (Bitcoin)\n\n");
    printf("Choose an option 1-5:\n\n");

    int input;
    scanf("%d", &input);

    while ((input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5)) {
        printf("\n\n Please enter a valid option 1-5.\n\n");
        scanf("%d", &input);
    }

    BankAccount* new_account = bank_account_init(input, session_user->first_name, session_user->last_name);
    if (new_account == NULL) {
        printf("Allocation failed\n");
        pause();
        return;
    }

    // Append new account information to the data.csv file
    FILE *file_ptr = fopen("../data/data.csv", "a");

    fprintf(file_ptr, "\n%s,%s,%s,%s,%0.2Lf",
            session_user->first_name,
            session_user->last_name,
            new_account->iban,
            new_account->currency,
            new_account->balance);

    fclose(file_ptr);

    // Append the new account in the user's owned accounts array
    arrput(session_user->owned_bank_accounts, new_account);

    clear_screen();
    printf("Congrats! Your new account has been created!\nYour balance is currently 0, so perform a "
           "transaction or "
           "edit account to add funds\n\n");

    pause();
}