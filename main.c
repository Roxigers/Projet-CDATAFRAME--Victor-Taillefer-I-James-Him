//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>

int main()
{
    char *title ;
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
    if (df == NULL){  //verifie qu'il a été créer ou pas*
        printf("Error creating Cdataframe\n");
        return 1;
    }
    int nb_rows, nb_columns;
    printf("Enter the number of rows : ");
    scanf("%d",&nb_rows);
    printf("Enter the number of columns : ");
    scanf("%d",&nb_columns);
    insert_value_Cdata (df, nb_rows, nb_columns);
    for (int i = 0; i < df->nb_column; i++) {
        printf("Column %d: %s\n", i, df->column[i]->titre);
        print_col(df->column[i]);
    }
    int lim_rows = 0;
    while (lim_rows <= 0)
    {
        printf("Enter the row limit value : ");
        scanf("%d",&lim_rows);
    }

    //int values[2][4] = {{1, 2, 3,4}, {5, 6, 7, 8}};
   // insert_value_endur(df, 2, 4, values);

    lim_rows_display(df, lim_rows);
    int lim_column = 0;
    while (lim_column <= 0)
    {
        printf("Enter the row limit value : ");
        scanf("%d",&lim_column);
    }
    lim_column_display(df, lim_rows);

    //Ajouter une colonne au CDataframe
    COLUMN *new_column = create_column("Nouveau Titre");
    add_column(df,new_column);

    //Supprimer une colonne du Cdataframe
    int column_value2 = 0;
    while (column_value2 <= 0) {
        printf("Enter the column  value : ");
        scanf("%d", &column_value2);
    }
    delete_column(&df->column[column_value2]);

    //Vérifier l'existence d'une valeur (recherche) dans le CDataframe
    int search_value;
    int cpt;
    printf("Enter a desired value : ");
    scanf("%d",&search_value);
    cpt = nbr_occurence(df,search_value);
    if (cpt != 0)
    {
        printf("The value exist");
    }
    else
    {
        printf("The value does not exist");
    }

    //Renommer le titre d'une colonne du Cdataframe
    int column_value3 = 0;
    while (column_value3 <= 0)
    {
        printf("Enter the column  value : ");
        scanf("%d",&column_value3);
    }
    strcpy(df->column[column_value3]->titre, "Nouveau Titre");

    //Accéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne
    int row_value = 0;
    while (row_value <= 0)
    {
        printf("Enter the row value : ");
        scanf("%d",&row_value);
    }

    int column_value4 = 0;
    while (column_value4 <= 0)
    {
        printf("Enter the column  value : ");
        scanf("%d",&column_value4);
    }
    int new_value;
    printf("Enter the new value : ");
    scanf("%d",&new_value);
    df->column[column_value4]->donnee[row_value]= new_value;

//afficher le nom des colonnes
    for (int i = 0; i < df->nb_column; i++)
    {
        printf("Column %d: %s\n", i, df->column[i]->titre);
    }

//Affichage nombre de ligne et de colonne
    printf("Number of rows : %d",df->column[0]->TL);
    printf("Number of columns : %d",df->nb_column);

//Donnée par rapport à x
    int x;
    printf("Enter a value for x");
    scanf("%d",&x);
    printf("Number of cells containing the value %d : %d",x, nbr_occurence(df, x));
    printf("Number of cells greater than the value %d : %d",x, nbr_occurence_sup(df,x));
    printf("Number of cells less than the value %d : %d",x, nbr_occurence_inf(df,x));

    return 0;
}
