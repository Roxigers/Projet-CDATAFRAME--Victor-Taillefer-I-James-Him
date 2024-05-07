#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

// PARTI 2

COLUMN *create_colum(ENUM_TYPE type, char*title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    if (new_column==NULL){
        printf("Erreur allocation de la colonne");
        return NULL;
    }
    new_column->titre = (char*) malloc(sizeof(title)+1);
    if (new_column->titre == NULL){
        printf("Erreur allocation titre de la colonne");
    }
    strcpy(new_column->titre, title);

    new_column->TP = 0;
    new_column->TL = 0;
    new_column->data = NULL;
    new_column-> index = NULL;
    new_column ->column_type = type;
    return new_column;
}

int insert_value(COLUMN *col, void *value) {
    // Vérification de l'espace mémoire
    if (col->TL == col->TP) {

        if (col->TL == 0)
            col->data = (COL_TYPE **)malloc(sizeof(COL_TYPE *) * 256);
        else
            col->data = (COL_TYPE **)realloc(col->data, sizeof(COL_TYPE *) * (col->TL + 256));
        if (col->data == NULL) {
            printf("Erreur de reallocation de memoire");
            return 0;
        }
        col->TP += 256;
    }

    // Allocation de l'espace pour stocker la valeur
    switch (col->column_type) {
        case UNIT:
            col->data[col->TL] = (unsigned int *)malloc(sizeof(unsigned int));
            *((unsigned int *)col->data[col->TL]) = *((unsigned int *)value);
            break;
        case INT:
            col->data[col->TL] = (int *)malloc(sizeof(int));
            *((int *)col->data[col->TL]) = *((int *)value);
            break;
        case CHAR:
            col->data[col->TL] = (char *)malloc(sizeof(char));
            *((char *)col->data[col->TL]) = *((char *)value);
            break;
        case FLOAT:
            col->data[col->TL] = (float *)malloc(sizeof(float));
            *((float *)col->data[col->TL]) = *((float *)value);
            break;
        case DOUBLE:
            col->data[col->TL] = (double *)malloc(sizeof(double));
            *((double *)col->data[col->TL]) = *((double *)value);
            break;
        case STRING:
            col->data[col->TL] = (char *)malloc(strlen((char *)value) + 1);
            strcpy((char *)col->data[col->TL], (char *)value);
            break;
        case STRUCTURE:
            col->data[col->TL] = (void *)malloc(sizeof(void));
            *((void **)col->data[col->TL]) = *((void **)value);
            break;
        default:
            printf("Type de colonne non pris en charge");
            return 0;
    }

    col->TL++;
    return 1;
}

void delete_column(COLUMN **col) {
    for (int i = 0; i < (*col)->TL; i++) {
        switch ((*col)->column_type) {
            case UNIT:
                free((*col)->data[i]);
                break;
            case INT:
                free((*col)->data[i]);
                break;
            case CHAR:
                free((*col)->data[i]);
                break;
            case FLOAT:
                free((*col)->data[i]);
                break;
            case DOUBLE:
                free((*col)->data[i]);
                break;
            case STRING:
                free((*col)->data[i]);
                break;
            case STRUCTURE:
                free((void *) (*col)->data[i]); //on le cast en void* on peut utiliser free
                break;
        }
    }
    free((*col)->titre);
    free((*col)->data);
    free((*col)->index);
    free(*col);
}

