#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/structs.h"

User login(User user){
    FILE *fp = fopen("../Accounts.db", "rb");
    User tmp_user;
    char buf[256];
    if (fp == NULL){
        printf("There is no accounts yet. Please create one.\n");
        exit(0);
    }
    printf("****************\n");
    printf("* Logging In...*\n");
    printf("****************\n\n");
    printf("Enter your username: ");
    fgets(tmp_user.name, sizeof(buf), stdin);
    tmp_user.name[strcspn(tmp_user.name, "\n")] = 0;
    printf("Enter your password: ");
    fgets(tmp_user.pass, sizeof(buf), stdin);
    tmp_user.pass[strcspn(tmp_user.pass, "\n")] = 0;
    for (int i = 0; i < sizeof("../Accounts.db"); i++){
        fread(&user, sizeof(user), 1, fp);
        if (strcmp(tmp_user.name, user.name) == 0 && strcmp(tmp_user.pass, user.pass) == 0){
            
            printf("Logged in successfully.\n");
            return user;
        }
    }
    printf("%d\n", sizeof("../Accounts.db"));
    exit(0);
    fclose(fp);
}

void create_account(User user){
    FILE *fp = fopen("../Accounts.db", "ab+");
    User tmp_user;
    char buf[256];
    printf("**************************\n");
    printf("* Creating an account... *\n");
    printf("**************************\n\n");
    printf("Enter username: ");
    fgets(user.name, sizeof(buf), stdin);
    user.name[strcspn(user.name, "\n")] = 0;
    printf("Enter your password: ");
    fgets(user.pass, sizeof(buf), stdin);
    user.pass[strcspn(user.pass, "\n")] = 0;
    for (int i = 0; i < sizeof("../Accounts.db"); i++){
        fread(&tmp_user, sizeof(User), 1, fp);
        if (strcmp(tmp_user.name, user.name) == 0){
            printf("Account already exist.\n");
            exit(0);
        }
    }
    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);
    printf("Account successfully created.\n");
    exit(0);
}

User main_menu(User user){
    char line[3];
    int choice;
    printf("*************************************\n");
    printf("* Password Protected Personal Diary *\n");
    printf("*************************************\n\n");
    printf("1. Login\n");
    printf("2. Create an account\n");
    printf(">: ");
    fgets(line, sizeof(line), stdin);
    if (sscanf(line, "%d\n", &choice) != 1){
        printf("Please enter an integer\n");
        exit(0);
    }
    switch(choice){
        case 1:
            return login(user);
            break;
        case 2:
            create_account(user);
            break;
        default:
            printf("Invalid Input\n");
            exit(0);
    }
}
