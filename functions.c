#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>
COLUMN *create_column(char* title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
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

Cdataframe *create_Cdataframe()
{
    Cdataframe *new_Cdataframe = (Cdataframe*) malloc(sizeof(Cdataframe));
    new_Cdataframe ->column = NULL;
    new_Cdataframe -> nb_column = 0;
}

