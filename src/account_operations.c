#include "account_operations.h"

void view_accounts(const User* session_user) {

    clear_screen();

    int account_count = arrlen(session_user->owned_bank_accounts);

    if (account_count == 0) {
        printf("%s, you have no accounts to your name.\n\n", session_user->first_name);
        pause();
        return;
    }

    printf("%s, you have %d account(s) at our bank:\n\n", session_user->first_name, account_count);

    for (int i = 0; i < account_count; i++) {
        printf("=======================================================\n");
        printf("Account #%d ( %s )\n\n", i+1, session_user->owned_bank_accounts[i]->iban);
        printf("%0.2Lf %s\n",
               session_user->owned_bank_accounts[i]->balance,
               session_user->owned_bank_accounts[i]->currency);
        printf("=======================================================\n\n");
    }

    pause();

}

void edit_data(User *session_user) {

    clear_screen();

    printf("What would you like to modify, %s?\n\n", session_user->first_name);
    printf("[1] MODIFY AN ACCOUNT'S BALANCE OR CURRENCY\n");
    printf("[2] MODIFY CREDENTIALS (FIRST NAME AND/OR LAST NAME)\n\n");

    printf("Enter an option [1] or [2]\n\n");

    int response;
    scanf(" %d", &response);

    while ((response != 1) && (response != 2)) {
        printf("\nEnter a valid option [1] or [2]\n\n");
        scanf(" %d", &response);
    }

    switch (response) {
        case 1:
            edit_account(session_user);
            break;
        case 2:
            clear_screen();
            printf("Not available yet!\n\n");
            pause();
            break;
    }


}

void edit_account(User *session_user) {

    clear_screen();

    int account_count = arrlen(session_user->owned_bank_accounts);
    BankAccount* account_to_edit;

    if (account_count == 0) {
        printf("%s, you have no accounts to your name.\n\n", session_user->first_name);
        pause();
        return;
    }
    else if (account_count == 1) {
        account_to_edit = session_user->owned_bank_accounts[0];
    }
    else {

        printf("%s, you have %d account(s) at our bank:\n\n", session_user->first_name, account_count);

        for (int i = 0; i < account_count; i++) {
            printf("=======================================================\n");
            printf("Account #%d ( %s )\n\n", i + 1, session_user->owned_bank_accounts[i]->iban);
            printf("%0.2Lf %s\n",
                   session_user->owned_bank_accounts[i]->balance,
                   session_user->owned_bank_accounts[i]->currency);
            printf("=======================================================\n\n");
        }

        printf("Choose an account [1] to [%d] to modify\n\n", account_count);
        int response;
        scanf(" %d", &response);

        while ((response < 1) && (response > account_count)) {
            printf("\nChoose a valid account [1] to [%d] to modify\n\n", account_count);
            scanf(" %d", &response);
        }

        account_to_edit = session_user->owned_bank_accounts[response];
    }

    clear_screen();
    printf("You have selected the account with IBAN ( %s )\n", account_to_edit->iban);
    printf("Current balance: %0.2Lf %s\n\n",
           account_to_edit->balance,
           account_to_edit->currency);
    printf("[1] WITHDRAW FUNDS\n");
    printf("[2] DEPOSIT FUNDS\n");
    printf("[3] CHANGE ACCOUNT CURRENCY\n\n");

    int response;
    scanf(" %d", &response);

    while ((response != 1) && (response != 2) && (response != 3)) {
        printf("\nChoose a valid option [1] to [3]\n\n");
        scanf(" %d", &response);
    }

    clear_screen();

    switch(response) {
        case 1: {

            if (account_to_edit->balance == 0) {
                printf("Your account is empty, %s.\n", session_user->first_name);
                printf("There are no funds to withdraw.\n\n");
                break;
            }

            printf("Current balance: %0.2Lf %s\n\n",
                   account_to_edit->balance,
                   account_to_edit->currency);
            printf("Enter withdrawal amount (%s): ", account_to_edit->currency);

            long double withdrawal_amount = 0;
            scanf(" %Lf", &withdrawal_amount);

            while ((withdrawal_amount > account_to_edit->balance) || (withdrawal_amount < 0)) {
                printf("\nWithdrawal amount exceeds balance / is a negative number! Enter again: ");
                scanf(" %Lf", &withdrawal_amount);
            }

            // Update stack (local) data
            account_to_edit->balance -= withdrawal_amount;

            // Update database
            // Read file to store every row except row to be modified
            FILE *file_ptr = fopen("../data/data.csv", "r");

            if (file_ptr == NULL) {
                printf("Error opening CSV file\n\n");
                break;
            }

            char **rows = NULL;
            char *row_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));
            char *column_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));

            while (fgets(row_reader, MAX_CHARS_PER_LINE, file_ptr) != NULL) {

                // Clear column reader string
                memset(column_reader, '\0', MAX_CHARS_PER_LINE);

                // Copy full row to column reader
                strcpy(column_reader, row_reader);

                // Tokenize, get FirstName column
                strtok(column_reader, ",");

                // Check for FirstName match before checking the rest (optimization)
                if (strcmp(column_reader, session_user->first_name) != 0) {
                    // If no match, store row to be appended later
                            arrput(rows, row_reader);
                    continue;
                }

                // Get LastName column (and ignore)
                strtok(NULL, ",");
                // Get IBAN and check for match
                strtok(NULL, ",");
                if (strcmp(column_reader, account_to_edit->iban) == 0) {
                    // Found row to be modified
                    // Do not store, it will be appended later
                    continue;
                }
            }

            // Free readers
            free(column_reader);
            memset(column_reader, '\0', MAX_CHARS_PER_LINE);
            free(row_reader);
            memset(row_reader, '\0', MAX_CHARS_PER_LINE);

            // Close file
            fclose(file_ptr);

            // Open file to overwrite
            file_ptr = fopen("../data/data.csv", "w");

            // Write all the rows except the one to be modified
            for (int i = 0; i < arrlen(rows); i++) {
                fprintf(file_ptr, "%s", rows[i]);
            }

            arrfree(rows);

            // Write the row to be modified
            // If the new currency is BTC, allow for more decimal precision
            if (strcmp(account_to_edit->currency, "BTC") == 0)
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.9Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);
            else
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.2Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);

            fclose(file_ptr);

            break;
        }

        case 2: {
            clear_screen();
            printf("Choose the currency to deposit money in:\n\n");

            printf("[1] RON (Romanian Leu)\n");
            printf("[2] EUR (Euro)\n");
            printf("[3] GBP (British Pound)\n");
            printf("[4] USD (US Dollar)\n");
            printf("[5] BTC (Bitcoin)\n\n");
            printf("Choose an option 1-5:\n\n");

            scanf(" %d", &response);

            while ((response != 1) && (response != 2) && (response != 3) && (response != 4) && (response !=
                                                                                                5)) {
                printf("\n\n Please enter a valid option 1-5.\n\n");
                scanf("%d", &response);
            }

            char deposit_currency[3];
            get_currency_from_code(response, deposit_currency);
            printf("LOG: Desired currency: %s\n", deposit_currency);

            clear_screen();
            printf("Enter the amount to deposit (%s): ", deposit_currency);
            long double deposit_amount;
            scanf("%Lf", &deposit_amount);

            while (deposit_amount < 0) {
                printf("Amount must be greater than zero!\nEnter again: \n");
                scanf(" %Lf", &deposit_amount);
            }

            if (deposit_amount == 0) {
                // Do nothing
                break;
            }

            if (response == get_currency_code(account_to_edit->currency)) {
                // No currency conversion is needed
                // Update stack (local) data
                account_to_edit->balance += deposit_amount;
                printf("Successfully deposited %0.2Lf %s\n\n", deposit_amount, account_to_edit->currency);
                printf("LOG: Modified locally\n");
            } else {
                deposit_amount = currency_conversion(response, get_currency_code
                        (account_to_edit->currency), deposit_amount);

                // Update stack (local) data
                account_to_edit->balance += deposit_amount;
                printf("Successfully deposited %0.2Lf %s\n\n", deposit_amount, account_to_edit->currency);
                printf("LOG: Modified locally\n");
            }

            // Update database
            // Read file to store every row except row to be modified
            FILE *file_ptr = fopen("../data/data.csv", "r");

            if (file_ptr == NULL) {
                printf("Error opening CSV file\n\n");
                break;
            }

            char **rows = NULL;
            char *row_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));
            char *column_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));

            while (fgets(row_reader, MAX_CHARS_PER_LINE, file_ptr) != NULL) {

                // Clear column reader string
                memset(column_reader, '\0', MAX_CHARS_PER_LINE);

                // Copy full row to column reader
                strcpy(column_reader, row_reader);

                // Tokenize, get FirstName column
                strtok(column_reader, ",");

                // Check for FirstName match before checking the rest (optimization)
                if (strcmp(column_reader, session_user->first_name) != 0) {
                    // If no match, store row to be appended later
                    arrput(rows, row_reader);
                    continue;
                }

                // Get LastName column (and ignore)
                strcpy(column_reader,strtok(NULL, ","));

                // Get IBAN and check for match
                strcpy(column_reader,strtok(NULL, ","));
                if (strcmp(column_reader, account_to_edit->iban) == 0) {
                    // Found row to be modified
                    // Do not store, it will be appended later
                    continue;
                }
            }

            // Free readers
            free(column_reader);
            free(row_reader);

            printf("LOG: Done reading for overwrite\n");
            fclose(file_ptr);

            // Open file to overwrite
            file_ptr = fopen("../data/data.csv", "w");

            // Write all the rows except the one to be modified
            for (int i = 0; i < arrlen(rows); i++) {
                fprintf(file_ptr, "%s", rows[i]);
            }

            arrfree(rows);

            // Write the row to be modified
            // If the new currency is BTC, allow for more decimal precision
            if (strcmp(account_to_edit->currency, "BTC") == 0)
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.9Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);
            else
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.2Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);

            fclose(file_ptr);

            printf("LOG: Done overwriting\n");

            break;

        }

        case 3: {
            clear_screen();
            printf("Choose the currency to change to:\n\n");

            printf("[1] RON (Romanian Leu)\n");
            printf("[2] EUR (Euro)\n");
            printf("[3] GBP (British Pound)\n");
            printf("[4] USD (US Dollar)\n");
            printf("[5] BTC (Bitcoin)\n\n");
            printf("Choose an option 1-5:\n\n");

            scanf(" %d", &response);

            while ((response != 1) && (response != 2) && (response != 3) && (response != 4) && (response !=
                                                                                                5)) {
                printf("\n\n Please enter a valid option 1-5.\n\n");
                scanf("%d", &response);
            }

            clear_screen();

            if (response == get_currency_code(account_to_edit->currency)) {
                printf("Your account is already in that currency.\n\n");
                break;
            }

            char new_currency[3];
            get_currency_from_code(response, new_currency);
            long double new_balance = 0;
            new_balance = currency_conversion(get_currency_code(account_to_edit->currency),
                                              response,
                                              account_to_edit->balance);

            printf("Your new balance will be %Lf %s\n\n", new_balance, new_currency);

            printf("Confirm?\n");
            printf("[y] Yes\n");
            printf("[N] No\n\n");

            char confirmation = 0;
            scanf(" %c", &confirmation);

            clear_screen();

            if (confirmation == 'N') {
                printf("Operation cancelled. Nothing has changed.\n\n");
                break;
            }

            printf("Operation successful.\n");
            printf("New account balance: %Lf %s\n\n", new_balance, new_currency);

            // Update stack (local) data
            memset(account_to_edit->currency, '\0', 3);
            strcpy(account_to_edit->currency, new_currency);

            account_to_edit->balance = new_balance;

            // Update database
            // Read file to store every row except row to be modified
            FILE *file_ptr = fopen("../data/data.csv", "r");

            if (file_ptr == NULL) {
                printf("Error opening CSV file\n\n");
                break;
            }

            char **rows = NULL;
            char *row_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));
            char *column_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));

            while (fgets(row_reader, MAX_CHARS_PER_LINE, file_ptr) != NULL) {

                // Clear column reader string
                memset(column_reader, '\0', MAX_CHARS_PER_LINE);

                // Copy full row to column reader
                strcpy(column_reader, row_reader);

                // Tokenize, get FirstName column
                strtok(column_reader, ",");

                // Check for FirstName match before checking the rest (optimization)
                if (strcmp(column_reader, session_user->first_name) != 0) {
                    // If no match, store row to be appended later
                            arrput(rows, row_reader);
                    continue;
                }

                // Get LastName column (and ignore)
                strtok(NULL, ",");
                // Get IBAN and check for match
                strtok(NULL, ",");
                if (strcmp(column_reader, account_to_edit->iban) == 0) {
                    // Found row to be modified
                    // Do not store, it will be appended later
                    continue;
                }
            }

            // Free readers
            free(column_reader);
            memset(column_reader, '\0', MAX_CHARS_PER_LINE);
            free(row_reader);
            memset(row_reader, '\0', MAX_CHARS_PER_LINE);

            // Close file
            fclose(file_ptr);

            // Open file to overwrite
            file_ptr = fopen("../data/data.csv", "w");

            // Write all the rows except the one to be modified
            for (int i = 0; i < arrlen(rows); i++) {
                fprintf(file_ptr, "%s", rows[i]);
            }

            arrfree(rows);

            // Write the row to be modified
            // If the new currency is BTC, allow for more decimal precision
            if (strcmp(account_to_edit->currency, "BTC") == 0)
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.9Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);
            else
                fprintf(file_ptr, "\n%s,%s,%s,%s,%0.2Lf",
                        session_user->first_name,
                        session_user->last_name,
                        account_to_edit->iban,
                        account_to_edit->currency,
                        account_to_edit->balance);

            fclose(file_ptr);

            break;
        }
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
    scanf(" %d", &input);

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

    if (file_ptr == NULL) {
        printf("Error opening CSV file. Re-run and try again.\n");
        pause();
        return;
    }

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