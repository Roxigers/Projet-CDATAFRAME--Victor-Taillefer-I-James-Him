
#ifndef PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_COLUMNS_H
#define PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_COLUMNS_H

#include "functions.h"

COLUMN *create_column(ENUM_TYPE type, char*title);

int insert_value(COLUMN *col, void *value);

/**
* @brief: Free the space allocated by a column * @param1: Pointer to the column
*/
void delete_column(COLUMN **col);

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);

void print_col(COLUMN* col);

int nbr_occurence(COLUMN* col, void* value);

int nbr_occurence_sup(COLUMN* col, void* value);

int nbr_occurence_inf(COLUMN* col, void* value);

void* nbr_position(COLUMN *col, int position);

void sort(COLUMN* col, int sort_dir);

void quicksort(COLUMN* col,unsigned int left, unsigned int right);

int partition(COLUMN* col,unsigned int left, unsigned int right);

void tri_insertion(COLUMN* col);

void print_col_by_index(COLUMN *col);

void erase_index(COLUMN *col);

int check_index(COLUMN *col);

void update_index(COLUMN *col);

int comparaison(COLUMN* col,int i,int j);

void sort_direction(COLUMN *col);

void echanger(COLUMN* col,int i,int j);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_COLUMNS_H
