#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
    char* titre;
    int TP;
    int TL;
    int* donnee;
}COLUMN;
COLUMN *create_column(char* title);

int insert_value(COLUMN* col, int value);

#endif