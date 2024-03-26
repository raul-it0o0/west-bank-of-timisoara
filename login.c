#include <stdio.h>
#include <string.h>
#define maxLineSize 1024

int main(int argc, char *argv[]){

    char *userName = argv[1], *userSurname = argv[2];

    printf("Name:%s\n",userName);
    printf("Surname:%s\n",userSurname);
    
    
    // login and search for name, surname
    FILE* fPtr = fopen("data.csv","w");
    
    char *rowStr = NULL;
    fgets(rowStr,maxLineSize,fPtr);
    // stores header row in rowStr

    while(fgets(rowStr,maxLineSize,fPtr)){
        // get name username

        char *rowEntry = 
        
    }

    printf("Login Successful.\n");

    // center in terminal
    printf("~~~WEST BANK OF TIMISOARA~~~\n");
    printf("© 2024 West Bank of Timisoara\n"); 

    printf("Welcome %s! What would you like to do today?\n", argv[1]);




    fclose(fPtr);

    return 0;
}