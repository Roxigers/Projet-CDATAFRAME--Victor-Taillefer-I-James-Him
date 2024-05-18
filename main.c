//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include "columns.h"
#include <stdlib.h>
#define N 5

int main() {
    char str[128];
    COLUMN *mycol = create_column(INT, "Column 1");
    int a = 5, c = 9, b = 3;
    insert_value(mycol, &a);
    insert_value(mycol, &c);
    insert_value(mycol, &b);
    print_col(mycol);
    print_col_by_index(mycol);
    sort( mycol, mycol->sort_dir);
    print_col_by_index(mycol);
    printf("Occurrences de 'C': %d\n", nbr_occurence(mycol,&c));
    printf("Occurence inferieur a A : %d\n", nbr_occurence_inf(mycol,&a));
    printf("Occurence superieur a A : %d\n", nbr_occurence_sup(mycol,&a));

    void* value = nbr_position(mycol,0);
    if (value!=NULL)
    {
        printf("Valeur a la position 1 : %s\n", value);
    }
    else
    {
        printf("La valeur a la position 1 est NULL\n");
    }

    delete_column(&mycol);
    Cdataframe *df = create_Cdataframe();
    if (df == NULL)
    {  //verifie qu'il a été créer ou pas*
        printf("erreur dans la creation du  Cdataframe\n");
        return 1;
    }
    insert_val_utilisateur(df);
    affichage_Cdataframe((df));
    return 0;
}