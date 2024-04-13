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

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int nbr_occurence(COLUMN* col, int x);

int nbr_position(COLUMN* col, int x);

int nbr_occurence_sup(COLUMN* col, int x);

int nbr_occurence_inf(COLUMN* col, int x);




#endif