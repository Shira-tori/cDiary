#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Diary{
    int year, month, day, hour, minute, number;
    char subject[256];
    char note[1024];
} Diary;

typedef struct User {
    char name[256];
    char pass[256];
    Diary diary;
} User;

#endif