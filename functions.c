#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "columns.h"
#include <string.h>

// PARTI 2

Cdataframe *create_Cdataframe()
{
    Cdataframe *Cdataframe = malloc(sizeof(Cdataframe));
    Cdataframe ->column = NULL;
    Cdataframe -> nb_column = 0;
    return Cdataframe;
}

void add_column(Cdataframe *Cdataframe, ENUM_TYPE type) {
    char title[100];
    printf("Entrez le titre de la nouvelle colonne : ");
    scanf("%s",title);
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
    int valeur;
    printf("Combien de lignes avez vous a mettre? \n");
    scanf("%d",&valeur);
    for (int i = 0; i<valeur;i++)
    {
        printf("Saisissez une valeur pour la colonne '%s':\n", new_column->title);

        switch (new_column->column_type) {
            case UNIT: {
                unsigned int value;
                printf("Entier non signé: ");
                scanf("%u", &value);
                insert_value(new_column, &value);
                break;
            }
            case INT: {
                int value;
                printf("Entier signé: ");
                scanf("%d", &value);
                insert_value(new_column, &value);
                break;
            }
            case CHAR: {
                char value;
                printf("Caractère: ");
                scanf(" %c", &value);
                getchar();
                insert_value(new_column, &value);
                break;
            }
            case FLOAT: {
                float value;
                printf("Flottant: ");
                scanf("%f", &value);
                insert_value(new_column, &value);
                break;
            }
            case DOUBLE: {
                double value;
                printf("Double: ");
                scanf("%lf", &value);
                insert_value(new_column, &value);
                break;
            }
            case STRING: {
                char value[128];
                printf("Chaîne de caractères : ");
                scanf("%s", value);
                insert_value(new_column, value);
                break;
            }
        }
    }


    Cdataframe->column[Cdataframe->nb_column++] = new_column;
}

void insert_val_utilisateur(Cdataframe *Cdata) {
    int nb_row, nb_column;

    do {
        printf("Entrez le nombre de lignes du CDataframe : ");
        scanf("%d", &nb_row);
    }while (nb_row<=0);

    do {
        printf("Entrez le nombre de colonnes du CDataframe : ");
        scanf("%d", &nb_column);
    }while (nb_column<=0);

    for (int i = 0; i < nb_column; i++) {
        char title[100];
        ENUM_TYPE type;


        printf("Entrez le titre de la colonne %d : ", i + 1);
        scanf("%s", title);

        printf("Entrez le type de la colonne %d (1: NULL 2: UNIT, 3: INT, 4: CHAR, 5: FLOAT, 6: DOUBLE, 7: STRING) : ", i + 1);
        int type_choice;
        scanf("%d", &type_choice);
        type = type_choice;

        COLUMN *new_column = create_column(type, title);
        if (new_column == NULL) {
            printf("Erreur lors de la création de la colonne.\n");
            return;
        }

        // On Réalloue la mémoire pour les pointeurs de colonnes
        Cdata->column = realloc(Cdata->column, sizeof(COLUMN *) * (Cdata->nb_column + 1));
        if (Cdata->column == NULL) {
            printf("Erreur lors de l'ajout de la colonne au dataframe.\n");
            delete_column(&new_column); // Libérer la mémoire de la nouvelle colonne
            return;
        }


        Cdata->column[Cdata->nb_column++] = new_column;
    }

    for (int i = 0; i < nb_row; i++) {
        printf("Ligne %d :\n", i + 1);
        for (int j = 0; j < nb_column; j++) {
            COLUMN *col = Cdata->column[j];
            printf("Saisissez une valeur pour la colonne '%s':\n", col->title);

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
            }
        }
    }
}


void display_Cdataframe(Cdataframe *Cdata) {

    for (int i = 0; i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->title);
    }
    printf("\n");

    int max_row = 0;
    for (int i = 0; i < Cdata->nb_column; i++) {
        if (Cdata->column[i]->TL > max_row) {
            max_row = Cdata->column[i]->TL;
        }
    }
    for (int row = 0; row < max_row; row++) {
        for (int i = 0; i < Cdata->nb_column; i++) {
            if (row < Cdata->column[i]->TL) {
                char str[100];
                convert_value(Cdata->column[i], row, str, sizeof(str));
                printf("%-30s", str);
            } else {
                printf("%-30s", "");
            }
        }
        printf("\n");
    }
}

void display_sorted_Cdataframe(Cdataframe *Cdata) {

    for (int i = 0; i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->title);
    }
    printf("\n");

    int max_row = 0;
    for (int i = 0; i < Cdata->nb_column; i++) {
        if (Cdata->column[i]->TL > max_row) {
            max_row = Cdata->column[i]->TL;
        }
    }
    for (int row = 0; row < max_row; row++) {
        for (int i = 0; i < Cdata->nb_column; i++) {
            if (row < Cdata->column[i]->TL) {
                char str[100];
                convert_value(Cdata->column[i], Cdata->column[i]->index[row], str, sizeof(str));
                printf("%-30s", str);
            } else {
                printf("%-30s", "");
            }
        }
        printf("\n");
    }
}


void display_row(Cdataframe *Cdata) {
    int row_lim = 0;
    while (row_lim <= 0) {
        printf("Entrez la valeur de la limite en ligne: ");
        scanf("%d", &row_lim);
    }


    for (int i = 0; i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->title); // séparé d'une largeur d'au moins 30 caractères sur la gauche
    }
    printf("\n");


    for (int i = 0; i < row_lim && i < Cdata->column[0]->TL; i++) {
        for (int j = 0; j < Cdata->nb_column; j++) {
            char str[128];
            convert_value(Cdata->column[j], i, str, sizeof(str));
            printf("%-30s", str);
        }
        printf("\n");
    }
}

void display_column(Cdataframe *Cdata) {
    int lim_column = 0;
    while (lim_column <= 0) {
        printf("Entrez la valeur de la limite en colonne: ");
        scanf("%d", &lim_column);
    }

    for (int i = 0; i < lim_column && i < Cdata->nb_column; i++) {
        printf("%-30s", Cdata->column[i]->title);
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

void change_title(Cdataframe *Cdata) {
    int title_value = -1;
    char nouveau_titre[100];

    while (title_value < 0 || title_value > Cdata->nb_column) {
        printf("Quelle colonne voulez-vous changer le titre de 0 a %d : ", Cdata->nb_column-1);
        scanf("%d", &title_value);
    }

    printf("Le nouveau titre '%s': ", Cdata->column[title_value]->title); //-1 psk les tableaux commencent à 0
    scanf("%s", nouveau_titre);

    strcpy(Cdata->column[title_value]->title, nouveau_titre); //On copie le nouveau dans l'ancien titre
}

void search_value(Cdataframe *Cdata) {

    printf("Entrez la valeur recherchee : ");
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
                    printf("La valeur %s existe dans la colonne '%s'.\n", value, col->title);
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
                        printf("La valeur %s existe dans la colonne '%s'.\n", value, col->title);
                        cpt = 1;
                        break;
                    }
                }
                break;
            }
        }
    }

    if (cpt == 0) {
        printf("La valeur %s n'existe pas dans le CDataframe.\n", value);
    }
}

void change_value(Cdataframe *df) { //je n'arrive pas a accédé a la première valeur
    int row_value = -1;
    while (row_value < 0) {
        printf("Entrez la valeur de la ligne : ");
        scanf("%d", &row_value);
    }

    int column_value = -1;
    while (column_value < 0) {
        printf("Entrez la valeur de la colonne : ");
        scanf("%d", &column_value);
    }

    //On regarde la valeur de la colonne qui change et on demande en fonction du type des données
    switch (df->column[column_value]->column_type) {
        case UNIT:
        {
            int valeur;
            printf("Entrez la nouvelle valeur (entier positif) : ");
            scanf("%d", &valeur);
            *((int *)df->column[column_value]->data[row_value]) = valeur;
            break;
        }
        case INT: {
            int valeur;
            printf("Entrez la nouvelle valeur (entier) : ");
            scanf("%d", &valeur);
            *((int *)df->column[column_value]->data[row_value]) = valeur;
            break;
        }
        case CHAR: {
            char valeur;
            printf("Entrez la nouvelle valeur (caractere) : ");
            scanf(" %c", &valeur);
            *((char *)df->column[column_value]->data[row_value]) = valeur;
            break;
        }
        case FLOAT: {
            float valeur;
            printf("Entrez la nouvelle valeur (flottant) : ");
            scanf("%f", &valeur);
            *((float *)df->column[column_value]->data[row_value]) = valeur;
            break;
        }
        case DOUBLE: {
            double valeur;
            printf("Entrez la nouvelle valeur (double) : ");
            scanf("%lf", &valeur);
            *((double *)df->column[column_value]->data[row_value]) = valeur;
            break;
        }
        case STRING: {
            char valeur[100];
            printf("Entrez la nouvelle valeur (chaine de caracteres) : ");
            scanf("%s", valeur);
            strcpy((char *)df->column[column_value]->data[row_value], valeur);
            break;
        }
    }
    df->column[column_value]->valid_index=0;
}

void display_row_column(Cdataframe* Cdata)
{
    printf("Le nombre de lignes est : %d\n",Cdata->column[0]->TL);
    printf("Le nombre de colonnes est : %d", Cdata->nb_column);
}

void display_column_names(Cdataframe* df)
{
    for(int i=0;i<df->nb_column;i++)
    {
        printf("Column %d: %s\n",i,df->column[i]->title);
    }
}
