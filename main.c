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
    print_col(col);
    val = 52;
    if (insert_value(col, val))
        printf("Value added successfully to my column\n");
    else
        printf("Error adding value to my column\n");
    print_col(col);
    delete_column(&col);
    return 0;
}

