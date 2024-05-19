//
// Created by HIM on 18/05/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "columns.h"
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char*title)//On crée une colonne
//ON prends en paramètre le type qu'on veut mettre a la colonne et le titre de la colonne
// Elle renvoie la colonne qu'on vient de créer
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN)); //On verifie que ca a été alloué ou pas
    if (new_column==NULL){
        printf("Erreur allocation de la colonne");
        return NULL;
    }
    new_column->title = (char*) malloc(strlen(title)+1);//pareil ici pour savoir si le titre a été enregistré
    if (new_column->title == NULL){
        printf("Erreur allocation titre de la colonne");
    }
    strcpy(new_column->title, title);
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

int insert_value(COLUMN *col, void *value) {//Permet a l'utilisateur d'insérer ses valeurs
//On prend en paramètre les valeurs saisie par l'utilisateur et la colonne qui va recevoir la valeur
//Il retourne 1 si ca a été effectué et 0 si ca a échoué

    if (col->TL == col->TP) {//on alloue si c'est la première fois

        if (col->TL == 0)
        {
            col->data = (COL_TYPE **)malloc(sizeof(COL_TYPE *) * 256);
            col->index = (unsigned long long*)malloc(sizeof(unsigned long long)*256);
        }
        else //sinon on rajoute 256 pour être large
        {
            col->data = (COL_TYPE **)realloc(col->data, sizeof(COL_TYPE *) * (col->TL + 256));
            col->index = (unsigned long long*)realloc(col->index,sizeof(unsigned long long )*256);
        }
        if (col->data == NULL || col->index == NULL) {
            printf("Erreur de reallocation de memoire");
            return 0;
        }
        col->TP += 256;//On met a jour la taille physique
    }

    // Allocation de l'espace pour stocker la valeur
    if(value != NULL)
    {
        switch (col->column_type) { //On alloue l'espace et on lui affecte la valeur
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


void delete_column(COLUMN **col) {//On supprime une colonne
//On prend en paramètre l'adresse de la colonne a supprime
//On ne renvoie rien car on supprime qql chose et on a besoin de rien renvoyer
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
    free((*col)->title);
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
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)//On converti les valeur d'un colonne en string
//On prend en paramètre la colonne, la posiiton de la valeur a convertir, un pointeur vers un string ou la valeur sera stocké et la taille max de la chaine
//ON ne renvoie rien car on fait les modifications directement sur la colonne
{
    if (col->data[i]== NULL)
    {
        snprintf(str, size,"NULL");
        return;
    }
    switch (col-> column_type) //snprintf formate n'importe quelle type en string
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

void print_col(COLUMN* col) {//On affiche une colonne
//On prend en paramètre la colonne a afficher
//On ne renvoie rien car le but de la fonction est deja effectué a l'intérieur
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

int nbr_occurence(COLUMN *col, void *value) {//On regarde le nombre d'occurence d'une valeur
//On prend en paramètre la colonne ou on va recherché la valeur et la valeur a recherché
//On renvoie le nombre d'occurence de la valeur
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
        convert_value(col, 0, value_str, sizeof(value_str)); //On ocnvertie les valeur en string

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

int nbr_occurence_sup(COLUMN *col, void *value) {//Permet de renvoyer le nombre de valeur sup a la valeur saisie
//On prend en paramètre la colonne ou l'on va recherché la valeur et la valeur saisie
//On renvoie le nbr de valeur sup
    int cpt = 0;

    switch (col->column_type) {
        case UNIT:
        case INT:
        case DOUBLE:
        case FLOAT://On marque rien et on converti tout en double c'est plus simple
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

int nbr_occurence_inf(COLUMN *col, void *value) {//l'inverse de la fonction précédente
//Meme paramètre que la fonction précédente
//On renvoie le nbr de valeur inf
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

void *nbr_position(COLUMN *col, int position) {//On recherche la valeura  la position saisie
//il prend en paramètre la colonne oou l'on va recherché la valeur et sa position
//ON renvoie un type void car on ne sait pas quelle est le type de la valeur renvoyer

    if (position < 0 || position >= col->TL) {
        printf("Position invalide.\n");
        return NULL;
    }

    return col->data[position];
}


int comparaison(COLUMN* col,int i,int j) //Fonction qui permet de comparer deux valeur
//paramètre : pointeur sur une structure, position i de la valeur 1 et position j de la valeur 2
//renvoie 1 ou 0 en fonction de si la comparaison est vrai dans les return
{
    switch (col->column_type)
    {
        case UNIT:
        {
            return ((*col->data[i]).uint_value>(*col->data[j]).uint_value);
            break;
        }
        case INT :
        {
            return ((*col->data[i]).int_value>(*col->data[j]).int_value);
            break;
        }
        case DOUBLE:
        {
            return ((*col->data[i]).double_value>(*col->data[j]).double_value);
            break;
        }
        case FLOAT:
        {
            return ((*col->data[i]).float_value>(*col->data[j]).float_value);
            break;
        }
        case CHAR:
        {
            return ((*col->data[i]).char_value>(*col->data[j]).char_value);
            break;
        }
        case STRING:
        {
            if((strcmp((*(col->data[i])).string_value, (*(col->data[j])).string_value)) > 0)
                return 1;
            else
                return 0;
        }
    }
}



int partition_dec(COLUMN* col,unsigned int left, unsigned int right) //fonction de partionnement
//Prend en compte la colonne, l'index du debut et de fin a partitionner
//Renvoie un entier représentant la position finale du pivot après partitionnement
{

    int i=left-1;
    for(int j=left;j<right;j++)
    {
        if(comparaison(col,col->index[j],col->index[right]))
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
    col->index[i+1] = col->index[right];
    col->index[right] = provisoire;
    return i+1;
}

void quicksort_dec(COLUMN* col,unsigned int left, unsigned int right)//l'algorithme de tri rapide
//Prend en compte la colonne, l'index du debut et de fin a partitionner
//elle ne renvoie rien car elle modifie directement les indices dans la struc COLONNE
{
    if(left<right)
    {
        int pi = partition_acc(col,left,right);
        quicksort_dec(col,left, pi-1);
        quicksort_dec(col, pi+1, right);
    }
}





int partition_acc(COLUMN* col,unsigned int left, unsigned int right)//fonction de partitionnement
//Prend en compte la colonne, l'index du debut et de fin a partitionner
//renvoie l'entier de la position finale du pivot après partitionnement
{
    int i=left-1;
    for(int j=left;j<right;j++)
    {
        if(comparaison(col,col->index[right],col->index[j]))
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
    col->index[i+1] = col->index[right];
    col->index[right] = provisoire;
    return i+1;
}



void quicksort_acc(COLUMN* col,unsigned int left, unsigned int right)//l'algorithme de tri rapide
//Prend en compte la colonne, l'index du debut et de fin a partitionner
//elle ne renvoie rien car elle modifie directement les indices dans la struc COLONNE
{
    if(left<right)
    {
        int pi = partition_acc(col,left,right);
        quicksort_acc(col,left, pi-1);
        quicksort_acc(col, pi+1, right);
    }
}

void tri_insertion_acc(COLUMN* col)//implémente l'algorithme de tri par insertion
//on a en paramètre la colonne a trier
//On ne renvoie rien car le tri se fait dans la fonction
{
    for(int i=1;i<col->TL;i++)
    {
        int j = i-1;
        while(j>0 && comparaison(col,j,i))
        {
            col->index[j+1] = col->index[j];
            j--;
        }
    }
}

void tri_insertion_dec(COLUMN* col)//implémente l'algorithme de tri par insertion
//on a en paramètre la colonne a trier
//On ne renvoie rien car le tri se fait dans la fonction
{
    for(int i=1;i<col->TL;i++)
    {
        int j = i-1;
        while(j>0 && comparaison(col,i,j))
        {
            col->index[j+1] = col->index[j];
            j--;
        }
    }
}



void sort(COLUMN* col, int sort_dir)//trie les données dans une colonne
//pointeur sur structure COLONNE, entier qui indique si le tri est ascendant ou descendant
//Ne renvoie rien car il change directement les place des donnée en faisant appel au fonction
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


void print_col_by_index(COLUMN *col)//Affiche les valeurs de la colonne triée
//Parzmètre : la colonne
//Ne renvoie rien car elle print deja les valeurs dans la fonctions
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

void erase_index(COLUMN *col)//Libère la mémoire allouée pour le tableau d'index
//Paramètre : la colonne
//Ne renvoie rien car il supprime juste la mémoire allouée
{
    col->valid_index = 0;
    free(col->index);
    col->index = NULL;
}

int check_index(COLUMN *col)//vérifie l'état de l'index d'une colonne
//Paramètre : la colonne
//Renvoie 0, -1 ou 1 selon si l'index est présent, invalide ou valide
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

void sort_direction(COLUMN *col)//demande dans quel sens on veut que la colonne soit triée
//paramètre : la colonne (le pointeur sur la structure COLONNE)
//ne renvoie rien
{
    printf("dans quel sens la colonne sera-t-elle triée?  \n0 : ASCENDANT\n1 : DESCENDANT");
    scanf("%d",&col->sort_dir);
}


void update_index(COLUMN *col)// il met à jour l'index d'une colonne
//paramètre : pointeur vers une structure COLONNE
//ne renvoie rien et appel juste la fonctionsort
{
    sort(col, col->sort_dir);
}