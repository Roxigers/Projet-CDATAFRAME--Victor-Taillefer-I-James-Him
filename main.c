//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdlib.h>

int main()
{
    // Création d'une colonne
    COLUMN *my_col = create_colum(INT, "My Column");

    if (my_col == NULL) {
        printf("Erreur lors de la création de la colonne.\n");
        return 1;
    }

    char a = 'A', c = 'C';
    insert_value(my_col,&a);
    insert_value(my_col,&c);

    return 0;
}