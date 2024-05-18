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

        printf("Entrez le type de la colonne %d (1: NULL 2: UNIT, 3: INT, 4: CHAR, 5: FLOAT, 6: DOUBLE, 7: STRING) : ", i + 1);
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
    }
}

void affichage_nbr_ligne_colonne(Cdataframe* Cdata)
{
    printf("Le nombre de lignes est : %d\n",Cdata->column[0]->TL);
    printf("Le nombre de colonnes est : %d", Cdata->nb_column);
}