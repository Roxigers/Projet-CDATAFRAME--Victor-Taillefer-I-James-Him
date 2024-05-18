//
// Created by HIM on 18/05/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "columns.h"
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char*title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    if (new_column==NULL){
        printf("Erreur allocation de la colonne");
        return NULL;
    }
    new_column->titre = (char*) malloc(strlen(title)+1);
    if (new_column->titre == NULL){
        printf("Erreur allocation titre de la colonne");
    }
    strcpy(new_column->titre, title);
    printf("dans quel sens la colonne sera-t-elle triee?  \n00 : ASCENDANT\n1 : DESCENDANT");
    scanf("%d",&new_column->sort_dir);
    new_column->TP = 0;
    new_column->TL = 0;
    new_column->data = NULL;
    new_column-> index = NULL;
    new_column ->column_type = type;
    new_column -> valid_index = 0;
    return new_column;
}

int insert_value(COLUMN *col, void *value) {

    if (col->TL == col->TP) {

        if (col->TL == 0)
        {
            col->data = (COL_TYPE **)malloc(sizeof(COL_TYPE *) * 256);
            col->index = (unsigned long long*)malloc(sizeof(unsigned long long)*256);
        }
        else
        {
            col->data = (COL_TYPE **)realloc(col->data, sizeof(COL_TYPE *) * (col->TL + 256));
            col->index = (unsigned long long*)realloc(col->index,sizeof(unsigned long long )*256);
        }
        if (col->data == NULL || col->index == NULL) {
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
                (col->data[col->TL])= (int *)malloc(sizeof(int));
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
        }
    }
    else
    {
        col->data[col->TL]= NULL;
    }
    col->TL++;
    (col->index)[(col->TL)-1] = (col->TL)-1;
    if(col->valid_index == 1)
        col->valid_index = -1;
    else
    {
        if(col->valid_index == -1)
            col->valid_index = 0;
    }

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

    switch (col->column_type) {
        case UNIT:
        case INT:
        case DOUBLE:
        case FLOAT:
        {
            for (int i = 0; i < col->TL; i++) {
                switch (col->column_type) {
                    case UNIT:
                        if (*((unsigned int *)col->data[i]) > *((unsigned int *)value))
                            cpt++;
                        break;
                    case INT:
                        if (*((int *)col->data[i]) > *((int *)value))
                            cpt++;
                        break;
                    case DOUBLE:
                        if (*((double *)col->data[i]) > *((double *)value))
                            cpt++;
                        break;
                    case FLOAT:
                        if (*((float *)col->data[i]) > *((float *)value))
                            cpt++;
                        break;
                }
            }
            break;
        }
        case CHAR:
        case STRING:
        {
            char value_str[128];
            convert_value(col, 0, value_str, sizeof(value_str));

            for (int i = 0; i < col->TL; i++) {
                char temp_value[128]; // valeur dans les colonnes
                convert_value(col, i, temp_value, sizeof(temp_value));

                if (strcmp(temp_value, (char *)value) > 0) { // on les compare grâce à strcmp
                    cpt++;
                }
            }
            break;
        }
    }

    return cpt;
}

int nbr_occurence_inf(COLUMN *col, void *value) {
    int cpt = 0;

    switch (col->column_type) {
        case UNIT:
        case INT:
        case DOUBLE:
        case FLOAT:
        {
            for (int i = 0; i < col->TL; i++) {
                switch (col->column_type) {
                    case UNIT:
                        if (*((unsigned int *)col->data[i]) < *((unsigned int *)value))
                            cpt++;
                        break;
                    case INT:
                        if (*((int *)col->data[i]) < *((int *)value))
                            cpt++;
                        break;
                    case DOUBLE:
                        if (*((double *)col->data[i]) < *((double *)value))
                            cpt++;
                        break;
                    case FLOAT:
                        if (*((float *)col->data[i]) < *((float *)value))
                            cpt++;
                        break;
                }
            }
            break;
        }
        case CHAR:
        case STRING:
        {
            char value_str[128];
            convert_value(col, 0, value_str, sizeof(value_str));

            for (int i = 0; i < col->TL; i++) {
                char temp_value[128]; // valeur dans les colonnes
                convert_value(col, i, temp_value, sizeof(temp_value));

                if (strcmp(temp_value, (char *)value) < 0) { // on les compare grâce à strcmp
                    cpt++;
                }
            }
            break;
        }

    }

    return cpt;
}

void *nbr_position(COLUMN *col, int position) {

    if (position < 0 || position >= col->TL) {
        printf("Position invalide.\n");
        return NULL;
    }

    return col->data[position];
}

int partition_dec(COLUMN* col,unsigned int gauche, unsigned int droite)
{
    switch (col->column_type) {
        case UNIT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).uint_value >= pivot.uint_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case INT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).int_value >= pivot.int_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case CHAR: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).char_value >= pivot.char_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case FLOAT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).float_value >= pivot.float_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case STRING: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data[col->index[j]])).string_value, pivot.string_value >= 0)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
    }
}

void quicksort_dec(COLUMN* col,unsigned int gauche, unsigned int droite)
{
    if(gauche<droite)
    {
        int pi = partition_acc(col,gauche,droite);
        quicksort_dec(col,gauche, pi-1);
        quicksort_dec(col, pi+1, droite);
    }
}





int partition_acc(COLUMN* col,unsigned int gauche, unsigned int droite)
{
    switch (col->column_type) {
        case UNIT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).uint_value <= pivot.uint_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case INT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).int_value <= pivot.int_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case DOUBLE: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).int_value <= pivot.double_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case CHAR: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).char_value <= pivot.char_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case FLOAT: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data)[col->index[j]]).float_value <= pivot.float_value)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
        case STRING: {
            COL_TYPE pivot;
            pivot = *(col->data)[col->index[droite]];
            int i=gauche-1;
            for(int j=gauche;j<droite;j++)
            {
                if((*(col->data[col->index[j]])).string_value, pivot.string_value <= 0)
                {
                    i++;
                    unsigned long long provisoire;
                    provisoire = col->index[i];
                    col->index[i] = col->index[j];
                    col->index[j] = provisoire;
                }
            }
            unsigned long long provisoire;
            provisoire = col->index[i+1];
            col->index[i+1] = col->index[droite];
            col->index[droite] = provisoire;
            return i+1;
            break;
        }
    }
}

void quicksort_acc(COLUMN* col,unsigned int gauche, unsigned int droite)
{
    if(gauche<droite)
    {
        int pi = partition_acc(col,gauche,droite);
        quicksort_acc(col,gauche, pi-1);
        quicksort_acc(col, pi+1, droite);
    }
}

void tri_insertion_acc(COLUMN* col)
{
    for(int i=1;i<col->TL;i++)
    {
        switch (col->column_type) {
            case UNIT: {
                unsigned int k = (*(col->data[col->index[i]])).uint_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).uint_value>k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case INT: {
                int k = (*(col->data[col->index[i]])).int_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).int_value>k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case DOUBLE: {
                double k = (*(col->data[col->index[i]])).double_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).double_value>k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case CHAR: {
                char k = (*(col->data[col->index[i]])).char_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).char_value>k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case FLOAT: {
                float k = (*(col->data[col->index[i]])).float_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).float_value>k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case STRING: {
                char* k = (*(col->data[col->index[i]])).string_value;
                int j = i-1;
                while(j>0 && (strcmp((*(col->data[col->index[j]])).string_value, k) > 0))
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
        }
    }
}

void tri_insertion_dec(COLUMN* col)
{
    for(unsigned int i=col->TL-1;i>0;i--)
    {
        switch (col->column_type) {
            case UNIT: {
                unsigned int k = (*(col->data[col->index[i]])).uint_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).uint_value<k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case INT: {
                int k = (*(col->data[col->index[i]])).int_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).int_value<k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case DOUBLE: {
                double k = (*(col->data[col->index[i]])).double_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).double_value<k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case CHAR: {
                char k = (*(col->data[col->index[i]])).char_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).char_value<k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case FLOAT: {
                float k = (*(col->data[col->index[i]])).float_value;
                int j = i-1;
                while(j>0 && (*(col->data[col->index[j]])).float_value<k)
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
            case STRING: {
                char* k = (*(col->data[col->index[i]])).string_value;
                int j = i-1;
                while(j>0 && (strcmp((*(col->data[col->index[j]])).string_value, k) < 0))
                {
                    col->index[j+1] = col->index[j];
                    j--;
                }
                break;
            }
        }
    }
}



void sort(COLUMN* col, int sort_dir)
{
    if(col->valid_index == 0)
    {
        if(sort_dir==0)
            quicksort_acc(col,0,col->TL-1);
        else
            quicksort_dec(col,0,col->TL-1);
    }
    else
    if(col->valid_index == -1)
    {
        if(sort_dir == 0)
            tri_insertion_acc(col);
        else
            tri_insertion_dec(col);
    }

    col->valid_index = 1;
}

void print_col_by_index(COLUMN *col)
{
    switch (col->column_type) {
        case UNIT: {
            for(int i=0; i<col->TL;i++)
                printf("[%d] %u\n",i,(*(col->data[col->index[i]])).uint_value);
            break;
        }
        case INT: {
            for(int i=0; i<col->TL;i++)
                printf("[%d] %i\n",i,(*(col->data[col->index[i]])).int_value);
            break;
        }
        case DOUBLE: {
            for(int i=0; i<col->TL;i++)
                printf("%d %f",i,(*(col->data[col->index[i]])).double_value);
            break;
        }
        case CHAR: {
            for(int i=0; i<col->TL;i++)
                printf("%d %c",i,(*(col->data[col->index[i]])).char_value);
            break;
        }
        case FLOAT: {
            for(int i=0; i<col->TL;i++)
                printf("%d %f",i,(*(col->data[col->index[i]])).float_value);
            break;
        }
        case STRING: {
            for(int i=0; i<col->TL;i++)
                printf("%d %s",i,(*(col->data[col->index[i]])).string_value);
            break;
        }
    }
}

void erase_index(COLUMN *col)
{
    col->valid_index = 0;
    free(col->index);
    col->index = NULL;
}

int check_index(COLUMN *col)
{
    if(col->index == NULL)
        return 0;
    else
    {
        if(col->valid_index == 1)
            return 1;
        else
            return -1;
    }
}

void update_index(COLUMN *col)
{
    sort(col, col->sort_dir);
}
