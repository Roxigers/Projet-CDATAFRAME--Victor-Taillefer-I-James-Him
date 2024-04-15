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
    return 0;
}
