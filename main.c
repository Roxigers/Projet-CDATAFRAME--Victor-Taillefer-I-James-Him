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

    Cdataframe *df = create_Cdataframe();
    if (df == NULL){  /**verifie qu'il a été créer ou pas**/
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

    int values[2][4] = {{1, 2, 3,4}, {5, 6, 7, 8}};
    insert_value_endur(df, 2, 4, values);

    int lim_rows = 0;
    while (lim_rows <= 0)
    {
        printf("Enter the row limit value : ");
        scanf("%d",&lim_rows);
    }
    lim_rows_display(df, lim_rows);

    int lim_column = 0;
    while (lim_column <= 0)
    {
        printf("Enter the row limit value : ");
        scanf("%d",&lim_column);
    }
    lim_column_display(df, lim_rows);
    return 0;
}
