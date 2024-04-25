#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

COLUMN *create_column(char* title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    new_column->titre = (char*) malloc(sizeof(title)+1);
    strcpy(new_column->titre, title);
    new_column->donnee = NULL;
    new_column->TP = 0;
    new_column->TL = 0;
    return new_column;
}



/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/

int insert_value(COLUMN* col, int value)
{
    int retour = 1;
    /** verification des cas ou il est necessaire d'agrandir l'espace aloue*/
    if ((col->TP - col->TL == 0) || (col->donnee == NULL) )
    {

        if (col->donnee == NULL)
        {
            /** allocation en cas de création d'espace et ajout de la variable */
            col->donnee = malloc((col->TP+256)*sizeof(int));
            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
        else
        {
            /** reallocatoin lorsqu'il n'y a plus de place et ajout de la variable */
            realloc(col->donnee, (col->TP+256)*sizeof(int));

            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
    }
    else
    {
        /** ajout de la variable si il n'y a pas besoin d'allocation */
        col->donnee[col->TL] = value;
        col->TL += 1;
    }
    /** verification si le malloc ou realloc */
    if (col->donnee == NULL)
    {
        retour = 0;
    }
    return retour;
}

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN **col)
{
    free((*col)->donnee);
    free(*col);
}


/**
* @brief: Print a column content
* @param:  pointer to a column
*/
void print_col(COLUMN* col)
{

    for(int i=0;i<(col->TL);i++)
        printf("[%d] %d\n",i,col->donnee[i]);
}

/**Retourner le nombre de d’occurrences d’une valeur x (x donné en paramètre).*/

int nbr_occurence(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] == x)
        {
            cpt++;
        }
    }
    return cpt;
}

/**Retourner la valeur présente à la position x (x donné en paramètre).*/

int nbr_position(COLUMN* col, int x)
{
    int nombre;
    nombre = col->donnee[x];
    return nombre;
}

/**Retourner le nombre de valeurs qui sont supérieures à x (x donné en paramètre).*/

int nbr_occurence_sup(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] > x)
        {
            cpt++;
        }
    }
    return cpt;
}

/** Retourner le nombre de valeurs qui sont inférieures à x (x donné en paramètre).*/

int nbr_occurence_inf(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] < x)
        {
            cpt++;
        }
    }
    return cpt;
}

int add_column (Cdataframe *Cdata, COLUMN *new_column)
{
    COLUMN **new_columns = realloc(Cdata->column, (Cdata-> nb_column + 1) * sizeof(COLUMN *));
    Cdata->column = new_columns;
    Cdata->column[Cdata->nb_column] = new_column;
    Cdata->nb_column++;
    return 1;
}

Cdataframe *create_Cdataframe()
{
    Cdataframe *Cdataframe = malloc(sizeof(Cdataframe));
    Cdataframe ->column = NULL;
    Cdataframe -> nb_column = 0;
    return Cdataframe;
}

void insert_value_Cdata (Cdataframe *Cdata, int nb_rows, int nb_columns)
{
    char title[50];
    int value=0;
    for (int i=0; i < nb_columns; i++)
    {
        printf("title %d : ", i);
        scanf("%s", title);

        COLUMN *new_column = create_column(title);
        add_column(Cdata, new_column);
    }
    for (int i = 1; i < nb_rows; i++) {
        printf("Enter values for row %d:\n", i);
        for (int j = 0; j < nb_columns; j++) {
            printf("Enter value for column %d: ", j);
            scanf("%d", &value);

            if (!insert_value(Cdata->column[j], value)) { /**si ca a pas marcher il retourne l'inverse du return**/
                printf("Error adding value to column %d\n", j);
                return;
            }
        }
    }
}

void insert_value_endur(Cdataframe *Cdata, int nb_rows, int nb_columns, int **values) {
    for (int i = 0; i < nb_columns; i++) {
        COLUMN *new_column = create_column("Column");
        add_column(Cdata, new_column);

        for (int j = 0; j < nb_rows; j++) {
            insert_value(Cdata->column[i], values[j][i]);
        }
    }
}

void lim_rows_display (Cdataframe *Cdata, int lim_rows)
{
    for ( int i =0; i<Cdata->nb_column;i++)
    {
        printf("%s    ", Cdata->column[i]->titre);
    }
    printf("\n");

    for (int i=0;i<lim_rows && i < Cdata-> column[0]->TL;i++)
    {
        for (int j =0; j<Cdata->nb_column; j++)
        {
            printf("%d   ", Cdata->column[j]->donnee[i]);
        }
        printf("\n");
    }
}

void lim_column_display (Cdataframe *Cdata, int lim_column)
{
    for ( int i =0; i<Cdata->nb_column;i++)
    {
        printf("%s    ", Cdata->column[i]->titre);
    }
    printf("\n");
    for (int i = 0; i < Cdata->column[0]->TL;i++)
    {
        for (int j=0; j< lim_column; j++)
        {
            printf("%d   ", Cdata->column[j]->donnee[i]);
        }
        printf("\n");
    }
}