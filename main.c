#include <stdio.h>


#include "functions.h"

int main()
{
    char* title = "colonne";
    COLUMN* col =  create_column(title);
    int a = insert_value(col, 3);
    printf("%d",a);
    return 0;
}

