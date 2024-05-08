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
    new_column->titre = (char*) malloc(strlen(title)+1);
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
            snprintf(str,size,"%s",(char*)col->data[i]);
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

void *nbr_position(COLUMN *col, int position) {

    if (position < 0 || position >= col->TL) {
        printf("Position invalide.\n");
        return NULL;
    }

    return col->data[position];
}

Cdataframe *create_Cdataframe()
{
    Cdataframe *Cdataframe = malloc(sizeof(Cdataframe));
    Cdataframe ->column = NULL;
    Cdataframe -> nb_column = 0;
    return Cdataframe;
}

void ajout_colonne(Cdataframe *Cdataframe, ENUM_TYPE type, char *title) {
    COLUMN *new_column = create_column(type, title);
    if (new_column == NULL) {
        printf("Erreur lors de la création de la colonne.\n");
        return;
    }

    // On Réalloue la mémoire pour les pointeurs de colonnes
    Cdataframe->column = realloc(Cdataframe->column, sizeof(COLUMN *) * (Cdataframe->nb_column + 1));
    if (Cdataframe->column == NULL) {
        printf("Erreur lors de l'ajout de la colonne au dataframe.\n");
        delete_column(&new_column); // Libérer la mémoire de la nouvelle colonne
        return;
    }


    Cdataframe->column[Cdataframe->nb_column++] = new_column;
}

void insert_val_utilisateur(Cdataframe *Cdata) {
    int nb_lignes, nb_colonnes;

    do {
        printf("Entrez le nombre de lignes du CDataframe : ");
        scanf("%d", &nb_lignes);
    }while (nb_lignes<=0);

    do {
        printf("Entrez le nombre de colonnes du CDataframe : ");
        scanf("%d", &nb_colonnes);
    }while (nb_colonnes<=0);

    for (int i = 0; i < nb_colonnes; i++) {
        char title[100];
        ENUM_TYPE type;


        printf("Entrez le titre de la colonne %d : ", i + 1);
        scanf("%s", title);

        printf("Entrez le type de la colonne %d (1: NULL 2: UNIT, 3: INT, 4: CHAR, 5: FLOAT, 6: DOUBLE, 7: STRING, 8: STRUCTURE) : ", i + 1);
        int type_choice;
        scanf("%d", &type_choice);
        type = type_choice;

        ajout_colonne(Cdata, type, title);
    }

    for (int i = 0; i < nb_lignes; i++) {
        printf("Ligne %d :\n", i + 1);
        for (int j = 0; j < nb_colonnes; j++) {
            COLUMN *col = Cdata->column[j];
            printf("Saisissez une valeur pour la colonne '%s':\n", col->titre);

            switch (col->column_type) {
                case UNIT: {
                    unsigned int value;
                    printf("Entier non signé: ");
                    scanf("%u", &value);
                    insert_value(col, &value);
                    break;
                }
                case INT: {
                    int value;
                    printf("Entier signé: ");
                    scanf("%d", &value);
                    insert_value(col, &value);
                    break;
                }
                case CHAR: {
                    char value;
                    printf("Caractère: ");
                    scanf(" %c", &value);
                    getchar();
                    insert_value(col, &value);
                    break;
                }
                case FLOAT: {
                    float value;
                    printf("Flottant: ");
                    scanf("%f", &value);
                    insert_value(col, &value);
                    break;
                }
                case DOUBLE: {
                    double value;
                    printf("Double: ");
                    scanf("%lf", &value);
                    insert_value(col, &value);
                    break;
                }
                case STRING: {
                    char value[128];
                    printf("Chaîne de caractères : ");
                    scanf("%s", value);
                    insert_value(col, value);
                    break;
                }
                case STRUCTURE: {
                    void *value= malloc(sizeof(void*));
                    printf("Structure :");
                    scanf("%p", value);
                    insert_value(col, value);
                    break;
                }
            }
        }
    }
}

void affichage_Cdataframe(Cdataframe *Cdata) {

    for (int i = 0; i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->titre);
    }
    printf("\n");

    int ligne_max = 0;
    for (int i = 0; i < Cdata->nb_column; i++) {
        if (Cdata->column[i]->TL > ligne_max) {
            ligne_max = Cdata->column[i]->TL;
        }
    }
    for (int ligne = 0; ligne < ligne_max; ligne++) {
        for (int i = 0; i < Cdata->nb_column; i++) {
            if (ligne < Cdata->column[i]->TL) {
                char str[100];
                convert_value(Cdata->column[i], ligne, str, sizeof(str));
                printf("%-30s", str);
            } else {
                printf("%-30s", "");
            }
        }
        printf("\n");
    }
}

void ligne_affichage(Cdataframe *Cdata) {
    int limite_ligne = 0;
    while (limite_ligne <= 0) {
        printf("Entrez la valeur de la limite en ligne: ");
        scanf("%d", &limite_ligne);
    }


    for (int i = 0; i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->titre); // séparé d'une largeur d'au moins 30 caractères sur la gauche
    }
    printf("\n");


    for (int i = 0; i < limite_ligne && i < Cdata->column[0]->TL; i++) {
        for (int j = 0; j < Cdata->nb_column; j++) {
            char str[128];
            convert_value(Cdata->column[j], i, str, sizeof(str));
            printf("%-30s", str);
        }
        printf("\n");
    }
}

void colonne_affichage(Cdataframe *Cdata) {
    int lim_column = 0;
    while (lim_column <= 0) {
        printf("Enter the column limit value: ");
        scanf("%d", &lim_column);
    }

    for (int i = 0; i < lim_column && i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->titre);
    }
    printf("\n");

    for (int i = 0; i < Cdata->column[0]->TL; i++) { //ils sont tous le mem nb de colonnes
        for (int j = 0; j < lim_column && j < Cdata->nb_column; j++) {
            char str[100];
            convert_value(Cdata->column[j], i, str, sizeof(str));
            printf("%-30s", str);
        }
        printf("\n");
    }
}

void changer_titre(Cdataframe *Cdata) {
    int valeur_colonne_titre = 0;
    char nouveau_titre[100];

    while (valeur_colonne_titre < 1 || valeur_colonne_titre > Cdata->nb_column) {
        printf("Quelle colonne voulez-vous changer le titre de 1 à %d : ", Cdata->nb_column);
        scanf("%d", &valeur_colonne_titre);
    }

    printf("Le nouveau titre '%s': ", Cdata->column[valeur_colonne_titre - 1]->titre); //-1 psk les tableaux commencent à 0
    scanf("%s", nouveau_titre);

    strcpy(Cdata->column[valeur_colonne_titre - 1]->titre, nouveau_titre); //On copie le nouveau dans l'ancien titre
}

void rechercher_valeur(Cdataframe *Cdata) {

    printf("Entrez la valeur recherchée : ");
    char value[100];
    scanf("%s", value);

    int cpt = 0;

    for (int i = 0; i < Cdata->nb_column; i++) {
        COLUMN *col = Cdata->column[i];

        switch (col->column_type) {
            case INT:
            case FLOAT:   //il peuvent etre comparé directement donc on a pas besoin de mettre de code
            case DOUBLE:
            case UNIT:
            case CHAR: {
                int count = nbr_occurence(col, value);
                if (count > 0) {
                    printf("La valeur %s existe dans la colonne '%s'.\n", value, col->titre);
                    cpt = 1;
                }
                break;
            }
            case STRING: {
                // Comparer la valeur avec chaque valeur de la colonne de type STRING
                for (int j = 0; j < col->TL; j++) {
                    char str[128];
                    convert_value(col, j, str, sizeof(str));
                    if (strcmp(str, value) == 0) { //permet de comparer deux chaines de caractères
                        printf("La valeur %s existe dans la colonne '%s'.\n", value, col->titre);
                        cpt = 1;
                        break;
                    }
                }
                break;
            }
            case STRUCTURE: {
                for (int j = 0; j < col->TL; j++) {
                    void *ptr = nbr_position(col, j);
                    if (ptr != NULL && *((char *) ptr) == *value) {
                        printf("La valeur %s existe dans la colonne '%s'.\n", value, col->titre);
                        cpt = 1;
                        break;
                    }
                }
            }
        }
    }

    if (cpt == 0) {
        printf("La valeur %s n'existe pas dans le CDataframe.\n", value);
    }
}

void changer_valeur(Cdataframe *df) { //je n'arrive pas a accédé a la première valeur
    int ligne_valeur = 0;
    while (ligne_valeur <= 0) {
        printf("Entrez la valeur de la ligne : ");
        scanf("%d", &ligne_valeur);
    }

    int colonne_valeur = 0;
    while (colonne_valeur <= 0) {
        printf("Entrez la valeur de la colonne : ");
        scanf("%d", &colonne_valeur);
    }

    //On regarde la valeur de la colonne qui change et on demande en fonction du type des données
    switch (df->column[colonne_valeur]->column_type) {
        case UNIT:
        {
            int valeur;
            printf("Entrez la nouvelle valeur (entier) : ");
            scanf("%d", &valeur);
            *((int *)df->column[colonne_valeur]->data[ligne_valeur]) = valeur;
            break;
        }
        case INT: {
            int valeur;
            printf("Entrez la nouvelle valeur (entier) : ");
            scanf("%d", &valeur);
            *((int *)df->column[colonne_valeur]->data[ligne_valeur]) = valeur;
            break;
        }
        case CHAR: {
            char valeur;
            printf("Entrez la nouvelle valeur (caractère) : ");
            scanf(" %c", &valeur);
            *((char *)df->column[colonne_valeur]->data[ligne_valeur]) = valeur;
            break;
        }
        case FLOAT: {
            float valeur;
            printf("Entrez la nouvelle valeur (flottant) : ");
            scanf("%f", &valeur);
            *((float *)df->column[colonne_valeur]->data[ligne_valeur]) = valeur;
            break;
        }
        case DOUBLE: {
            double valeur;
            printf("Entrez la nouvelle valeur (double) : ");
            scanf("%lf", &valeur);
            *((double *)df->column[colonne_valeur]->data[ligne_valeur]) = valeur;
            break;
        }
        case STRING: {
            char valeur[100];
            printf("Entrez la nouvelle valeur (chaine de caractères) : ");
            scanf("%s", valeur);
            strcpy((char *)df->column[colonne_valeur]->data[ligne_valeur], valeur);
            break;
        }
        case STRUCTURE: {
            void *valeur = malloc(sizeof(void*));
            printf("Entrez la nouvelle valeur pour la structure : ");
            scanf("%p", valeur);
            memcpy(df->column[colonne_valeur]->data[ligne_valeur], valeur, sizeof(void*));
            free(valeur);
            break;
        }
    }
}

void affichage_nbr_ligne_colonne(Cdataframe* Cdata)
{
    printf("Le nombre de lignes est : %d\n",Cdata->column[0]->TL);
    printf("Le nombre de colonnes est : %d", Cdata->nb_column);
}


