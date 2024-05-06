//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdlib.h>

int main()
{
    char *title=NULL;
    title = (char*)malloc((strlen("colonne")+1)*sizeof(char));
    strcpy(title, "colonne");
    printf("%s",title);

    COLUMN* col=NULL;
    col =  create_column(title);
    int val = 5;
    if (insert_value(col, val))
        printf("Value added successfully to my column\n");
    else
        printf("Error adding value to my column\n");
    val = 52;
    if (insert_value(col, val))
        printf("Value added successfully to my column\n");
    else
        printf("Error adding value to my column\n");
    print_col(col);
    printf("%d\n",nbr_occurence(col, 5));
    printf("%d\n",nbr_position(col, 1));
    printf("%d\n",nbr_occurence_sup(col,4));
    printf("%d\n",nbr_occurence_inf(col,6));
    delete_column(&col);
    Cdataframe *df = create_Cdataframe();
    if (df == NULL)
    {  //verifie qu'il a été créer ou pas*
        printf("erreur dans la création du  Cdataframe\n");
    return 1;
    }

//int values[2][4] = {{1, 2, 3,4}, {5, 6, 7, 8}};
// insert_value_endur(df, 2, 4, values);

    int nombre = 0;

    while (1)
    { // Boucle infinie
        printf("\nVoici le menu : \n");
        printf("0) Quitter\n");
        printf("1) Remplissage du CDataframe a partir de saisies utilisateurs\n");
        printf("2) Afficher tout le CDataframe\n");
        printf("3) Afficher une partie des lignes du CDataframe selon une limite fournie par l'utilisateur\n");
        printf("4) Afficher une partie des colonnes du CDataframe selon une limite fournie par l'utilisateur\n");
        printf("5) Ajouter une ligne de valeurs au CDataframe\n");
        printf("6) Supprimer une ligne de valeurs du CDataframe\n");
        printf("7) Ajouter une colonne au CDataframe\n");
        printf("8) Supprimer une colonne du CDataframe\n");
        printf("9) Renommer le titre d'une colonne du CDataframe\n");
        printf("10) Verifier l'existence d'une valeur (recherche) dans le CDataframe\n");
        printf("11) Acceder/remplacer la valeur se trouvant dans une cellule du CDataframe\n");
        printf("12) Afficher les noms des colonnes\n");
        printf("13) Afficher le nombre de lignes et de colonnes\n");
        printf("14) Analyser une valeur x\n");
        printf("\nSaisissez un nombre : ");

        scanf("%d", &nombre);

        switch (nombre) {
            case 0:
            // Quitter le programme
            return 0;
            case 1:
                insert_values_user(df);
                break;
            case 2:
                display_CDataframe(df);
                break;
            case 3:
                lim_rows_display(df);
                break;
            case 4:
                lim_column_display(df);
                break;
            case 5:
                printf("Pas encore fait\n");
                break;
            case 6:
                printf("Pas encore fait\n");
                break;
            case 7:
                add_column(df);
                break;
            case 8: {
                int column_value = 0;
                while (column_value <= 0)
                {
                    printf("Enter the column value : ");
                    scanf("%d", &column_value);
                }
                delete_column(&df->column[column_value]);
                for (int i = column_value+1; i< df->nb_column; i ++)
                {
                    df->column[i-1]= df->column[i];
                }
                df->nb_column--;
                df->column = realloc(df->column, df->nb_column * sizeof(COLUMN *));
                break;
                }
            case 9:
                nouveau_titre(df);
                break;
            case 10:
                verifier_valeur_existante(df);
                break;
            case 11:
                modifier_valeur_cellule(df);
                break;
            case 12:
                Affichage_nom_colonne(df);
                break;
            case 13:
                Affichage_nbr_ligne_colonne(df);
                break;
            case 14:
                analyser_valeur_x(df);
                break;
            default:
                printf("La saisie est invalide.\n");
            break;
        }
    }
    return 0;
}