#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

// PARTI 2

COLUMN *create_column(ENUM_TYPE type, char*title)
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
    if(value != NULL)
    {
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
        }
    }
    else
    {
        col->data[col->TL]= NULL;
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
            case FLOAT:
                free((*col)->data[i]);
                break;
            case CHAR:
                free((*col)->data[i]);
                break;
            case STRING:
                free((*col)->data[i]);
                break;
            case DOUBLE:
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

/**
 * @brief: Convert a value into a string
 * @param1: Pointer to the column
 * @param2: Position of the value in the data array
 * @param3: The string in which the value will be written
 * @param4: Maximum size of the string
 */
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)
{
    if (col->data[i]== NULL)
    {
        snprintf(str, size,"NULL");
        return;
    }
    switch (col-> column_type)
    {
        case INT :
            snprintf(str,size, "%d", *((int*)col->data[i]));
            break;
        case DOUBLE :
            snprintf(str,size, "%lf", *((double*)col->data[i]));
            break;
        case FLOAT :
            snprintf(str,size,"%f",*((float*)col->data[i]));
            break;
        case UNIT :
            snprintf(str,size,"%u", *((unsigned int*)col->data[i]));
            break;
        case STRING :
            strncpy(str,(char*)col->data[i],size); //c'est deja un char donc pas besoin de e formater
            break;
        case CHAR :
            snprintf(str,size,"%c",*((char*)col->data[i]));
            break;
        case STRUCTURE :
            snprintf(str,size,"%p",col->data[i]);
            break;
    }
}

void print_col(COLUMN* col) {
    char str[128];
    for (int i = 0; i < col->TL; i++) {
        printf("[%d] ", i);
        if (col->data[i] == NULL) {
            printf("NULL\n");
        }
        else
        {
            convert_value(col,i,str,sizeof(str));
            printf("%s\n",str);
        }
    }
}

int nbr_occurence(COLUMN *col, void *value) {
    int cpt = 0;

    // on verifie le type de colonne car car strcmp marche seulement quand y'as plusieurs caractère
    if (col->column_type == CHAR) {
        char value_char = *((char *) value); // on convertie void* en char
        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL && *((char *) col->data[i]) == value_char) {
                cpt++;
            }
        }
    } else {
        char value_str[128];
        convert_value(col, 0, value_str, sizeof(value_str));

        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL) {
                char temp_value[128]; //valeur dans les colonnes
                convert_value(col, i, temp_value, sizeof(temp_value));

                if (strcmp(temp_value, (char *) value) == 0) { //on les compare grace a strcmp
                    cpt++;
                }
            }
        }
    }
    return cpt;
}

int nbr_occurence_sup(COLUMN *col, void *value) {
    int cpt = 0;

    // on verifie le type de colonne car car strcmp marche seulement quand y'as plusieurs caractère
    if (col->column_type == CHAR) {
        char value_char = *((char *) value); // on convertie void* en char
        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL && *((char *) col->data[i]) > value_char) {
                cpt++;
            }
        }
    } else {
        char value_str[128];
        convert_value(col, 0, value_str, sizeof(value_str));

        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL) {
                char temp_value[128]; //valeur dans les colonnes
                convert_value(col, i, temp_value, sizeof(temp_value));

                if (strcmp(temp_value, (char *) value) > 0) { //on les compare grace a strcmp
                    cpt++;
                }
            }
        }
    }
    return cpt;
}

int nbr_occurence_inf(COLUMN *col, void *value) {
    int cpt = 0;

    // on verifie le type de colonne car car strcmp marche seulement quand y'as plusieurs caractère
    if (col->column_type == CHAR) {
        char value_char = *((char *) value); // on convertie void* en char
        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL && *((char *) col->data[i]) < value_char) {
                cpt++;
            }
        }
    } else {
        char value_str[128];
        convert_value(col, 0, value_str, sizeof(value_str));

        for (int i = 0; i < col->TL; i++) {
            if (col->data[i] != NULL) {
                char temp_value[128]; //valeur dans les colonnes
                convert_value(col, i, temp_value, sizeof(temp_value));

                if (strcmp(temp_value, (char *) value) < 0) { //on les compare grace a strcmp
                    cpt++;
                }
            }
        }
    }
    return cpt;
}


