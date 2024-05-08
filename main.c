//
// Created by HIM on 28/03/2024.
//

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdlib.h>
#define N 5

int main() {
    COLUMN *mycol = create_column(CHAR, "Column 1");
    char a = 'A', c = 'C';
    insert_value(mycol, &a);
    insert_value(mycol, NULL);
    insert_value(mycol, &c);
    print_col(mycol);

    printf("Occurrences de 'C': %d\n", nbr_occurence(mycol,&c));
    printf("Occurence inférieur à A : %d\n", nbr_occurence_inf(mycol,&a));
    printf("Occurence supérieur à A : %d", nbr_occurence_sup(mycol,&a));

    delete_column(&mycol);
    return 0;
}
