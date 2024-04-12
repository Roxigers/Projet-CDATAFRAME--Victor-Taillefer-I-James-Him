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
            col->donnee = malloc((col->TP+256)*sizeof(int));
            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
        else
        {
            realloc(col->donnee, (col->TP+256)*sizeof(int));

            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
    }
    else
    {
        col->donnee[col->TL] = value;
        col->TL += 1;
    }
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
