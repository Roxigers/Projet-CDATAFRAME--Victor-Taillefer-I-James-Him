//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>


#include "functions.h"

int main()
{
    char* title = "colonne";
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

    Cdataframe *dataframe = create_Cdataframe();
    if (dataframe == NULL){  /**verifie qu'il a été créer ou pas**/
        printf("Error creating Cdataframe\n");
        return 1;
    }

    int nb_rows, nb_columns;
    printf("Enter the number of rows : ");
    scanf("%d",&nb_rows);
    printf("Enter the number of columns : ");
    scanf("%d",&nb_columns);

    insert_value_Cdata (dataframe, nb_rows, nb_columns);
    for (int i = 0; i < dataframe->nb_column; i++) {
        printf("Column %d: %s\n", i, dataframe->column[i]->titre);
        print_col(dataframe->column[i]);
    }
    return 0;
}
