//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdlib.h>
#define N 5

int main() {
    char str[128];
    COLUMN *mycol = create_column(CHAR, "Column 1");
    char a = 'A', c = 'C';
    insert_value(mycol, &a);
    insert_value(mycol, NULL);
    insert_value(mycol, &c);
    print_col(mycol);

    printf("Occurrences de 'C': %d\n", nbr_occurence(mycol,&c));
    printf("Occurence inférieur à A : %d\n", nbr_occurence_inf(mycol,&a));
    printf("Occurence supérieur à A : %d\n", nbr_occurence_sup(mycol,&a));

    void* value = nbr_position(mycol,0);
    if (value!=NULL)
    {
        printf("Valeur à la position 1 : %s\n", value);
    }
    else
    {
        printf("La valeur à la position 1 est NULL\n");
    }

    delete_column(&mycol);
    Cdataframe *df = create_Cdataframe();
    if (df == NULL)
    {  //verifie qu'il a été créer ou pas*
        printf("erreur dans la création du  Cdataframe\n");
        return 1;
    }
    insert_val_utilisateur(df);
    affichage_Cdataframe((df));
    return 0;
}