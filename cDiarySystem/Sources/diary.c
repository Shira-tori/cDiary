#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/structs.h"
#include "../Headers/login.h"

void add_record(User *pUser){
    char line[256];
    printf("*******************\n");
    printf("* Adding a record *\n");
    printf("*******************\n\n");
    printf("Enter the date [yyyy-mm-dd]: ");
    fgets(line, sizeof(line), stdin);
    if(sscanf(line, "%d-%d-%d", &pUser->diary.year, &pUser->diary.month, &pUser->diary.day) != 3){
        printf("Please follow the format.\n");
        exit(0);
    }
    printf("What is this for?: ");
    fgets(pUser->diary.subject, sizeof(pUser->diary.subject), stdin);
    pUser->diary.subject[strcspn(pUser->diary.subject, "\n")] = 0;
    printf("Note: ");
    fgets(pUser->diary.note, sizeof(pUser->diary.note), stdin);
    FILE *fp = fopen("../Diaries.db", "ab+");
    pUser->diary.number = sizeof("../Diaries.db");
    fwrite(pUser, sizeof(User), 1, fp);
    printf("Successfully added record.\n");
    exit(0);  
}

void view_record(User *pUser){
    char buf[2];
    int choice;
    User tmp_user;
    printf("*******************\n");
    printf("* Viewing records *\n");
    printf("*******************\n\n");
    while(choice != 3){
        printf("1. View today's records\n");
        printf("2. View all records\n");
        printf("3. Back\n");
        printf(">: ");
        fgets(buf, sizeof(buf), stdin);
        if(sscanf(buf, "%d", &choice) != 1){
            printf("Please enter an integer.\n");
            exit(0);
        }
        switch(choice){
            case 1:
                
                break;
            case 2:
                FILE *fp = fopen("../Diaries.db", "rb");
                if (fp == NULL){
                    printf("There are no records yet. Please create one.\n");
                    exit(0);
                }
                for (int i = 0; i < sizeof("../Diaries.db"); i++){
                    if (fread(&tmp_user, sizeof(User), 1, fp) == EOF){
                        break;
                    }
                    if (strcmp(pUser->name, tmp_user.name) == 0 && tmp_user.diary.number == sizeof("../Diaries.db")){
                        printf("\nDate: %d", tmp_user.diary.year);
                        if (tmp_user.diary.month < 10){
                            printf("-0%d", tmp_user.diary.month);
                        }
                        else{
                            printf("-%d", tmp_user.diary.month);
                        }
                        if (tmp_user.diary.day < 10){
                            printf("-0%d\n", tmp_user.diary.day);
                        }
                        else{
                            printf("-%d\n", tmp_user.diary.day);
                        }
                        printf("Subject: %s\n", tmp_user.diary.subject);
                        printf("Note: ");
                        for (int j = 0; j < sizeof(tmp_user.diary.note); j++){
                            printf("%c", tmp_user.diary.note[j]);
                            if (tmp_user.diary.note[j] == '\n'){
                                break;
                            }
                        }
                    }
                }
                fclose(fp);
                break;
       }
    }        
} 

void delete_record(){

}

void edit_record(){

}

void edit_pass(User *pUser){
    FILE *fp = fopen("../Accounts.db", "rb+");
    User tmp_user;
    printf("*********************\n");
    printf("* Changing Password *\n");
    printf("*********************\n\n");
    printf("Enter your password: ");
    fgets(tmp_user.pass, sizeof(tmp_user.pass), stdin);
    tmp_user.pass[strcspn(tmp_user.pass, "\n")] = 0;
    if (strcmp(pUser->pass, tmp_user.pass) == 0){
        printf("Enter your new password: ");
        fgets(pUser->pass, sizeof(pUser->pass), stdin);
        pUser->pass[strcspn(pUser->pass, "\n")] = 0;
        for (int i = 0; i < sizeof("../Accounts.db"); i++){
            fread(&tmp_user, sizeof(User), 1, fp);
            if (strcmp(tmp_user.name, pUser->name) == 0){
                fseek(fp, -1*sizeof(User), SEEK_CUR);
                fwrite(pUser, sizeof(User), 1, fp);
                printf("Password successfully changed.\n");
                exit(0);
            }
        }
    }
    else{
        printf("Wrong password.\n");
        exit(0);
    }
}

void diary_menu(User *puser){
    char line[3], *endptr;
    int lengthOfName = strlen(puser->name), choice;
    for (int i = 0; i < lengthOfName + 13; i++){
        printf("*");
    }
    printf("\n");
    printf("* Welcome %s! *\n", puser->name);
    for (int i = 0; i < lengthOfName + 13; i++){
        printf("*");
    }
    printf("\n\n");
    printf("1. Add a record\n");
    printf("2. View record\n");
    printf("3. Delete a record\n");
    printf("4. Edit a record\n");
    printf("5. Edit password\n");
    printf("6. Exit\n");
    printf(">: ");
    fgets(line, sizeof(line), stdin);
    choice = strtol(line, &endptr, 10);
    if (*endptr && *endptr != '\n'){
        printf("Please enter an integer.\n");
        exit(0);
    }
    switch(choice){
        case 1:
            add_record(puser);
            break;
        case 2:
            view_record(puser);
            break;
        case 3:
            delete_record();
            break;
        case 4:
            edit_record();
            break;
        case 5:
            edit_pass(puser);
            break;
        case 6:
            printf("Goodbye!\n");
            exit(0);
            break;
    }
}

int main(){
    User user = main_menu(user);
    User *puser = &user;
    diary_menu(puser);
    return 0;
}