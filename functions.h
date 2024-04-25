//
// Created by HIM on 28/03/2024.
//

#ifndef PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
#define PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
/**
 * Create a column
 * @param1 : Column title
 * @return : Pointer to created column
 */

typedef struct
{
    char* titre;
    int TP;
    int TL;
    int* donnee;
}COLUMN;

typedef struct {
    COLUMN **column;
    int nb_column;
}Cdataframe;

COLUMN *create_column(char* title);

int insert_value(COLUMN* col, int value);

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int nbr_occurence(COLUMN* col, int x);

int nbr_position(COLUMN* col, int x);

int nbr_occurence_sup(COLUMN* col, int x);

int nbr_occurence_inf(COLUMN* col, int x);

int add_column (Cdataframe *Cdata, COLUMN *new_column);

Cdataframe *create_Cdataframe();

void insert_value_Cdata (Cdataframe *Cdata, int nb_rows, int nb_columns);

void insert_value_endur(Cdataframe *Cdata, int nb_rows, int nb_columns, int (*values)[4]);

void lim_rows_display (Cdataframe *Cdata, int lim_rows);

void lim_column_display(Cdataframe *Cdata, int lim_column);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
