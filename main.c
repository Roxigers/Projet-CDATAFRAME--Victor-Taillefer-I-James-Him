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
Cdataframe *df =NULL;

int nombre = 0;

while (1) { // Boucle infinie
printf("\nVoici le menu : \n");
printf("0) Quitter\n");
printf("1) Remplissage du CDataframe a partir de saisies utilisateurs\n");
printf("2) Afficher tout le CDataframe\n");
printf("3) Afficher une partie des lignes du CDataframe selon une limite fournie par l'utilisateur\n");
printf("4) Afficher une partie des colonnes du CDataframe selon une limite fournie par l'utilisateur\n");
printf("5) Ajouter une colonne au CDataframe\n");
printf("6) Supprimer une colonne du CDataframe\n");
printf("7) Renommer le titre d'une colonne du CDataframe\n");
printf("8) Verifier l'existence d'une valeur (recherche) dans le CDataframe\n");
printf("9) Acceder/remplacer la valeur se trouvant dans une cellule du CDataframe\n");
printf("10) Afficher les noms des colonnes\n");
printf("11) Afficher le nombre de lignes et de colonnes\n");
printf("12) Mettre a jour/trier l'index d'une colonne\n");
printf("13) Afficher tout le CDataframe trie\n");
printf("14) Choisir le sens de tri d'une colonne\n");
printf("15) Verifier si l'index d'une colonne est valide\n");
printf("16) Suprimmer l'index d'une colonne\n");
printf("\nSaisissez un nombre : ");

scanf("%d", &nombre);

switch (nombre) {
    case 0:
// Quitter le programme
return 0;
case 1:
    {
    df = create_Cdataframe();
    if (df == NULL)
        {  //verifie qu'il a été créer ou pas*
            printf("erreur dans la creation du  Cdataframe\n");
            return 1;
        }
    insert_val_utilisateur(df);
    break;
    }
case 2:
{
    display_Cdataframe(df);
    break;
}

case 3:
{
    display_row(df);
    break;
}
case 4:
{
    display_column(df);
    break;
}
case 5:
{
    //printf("Entrez le titre de la colonne :\n");
    //char* tit;
    //gets(tit);
    printf("\n Entrez le type de la colonne parmis \n1:UNIT, \n2:INT, \n3:CHAR, \n4:FLOAT, \n5:DOUBLE, \n6:STRING:\n");
    ENUM_TYPE type;
    scanf("%d",&type);
    add_column(df,type, "tit");
    break;
}
case 6: {
    int column_value = 0;
    while (column_value <= 0) {
    printf("Entrez le numero de la colonne : ");
    scanf("%d", &column_value);
    }
    delete_column(&df->column[column_value]);
    for(int i=column_value;i<df->nb_column-1;i++)
        df->column[column_value]=df->column[column_value+1];
    df->nb_column = df->nb_column-1;
    break;
}
case 7:
{
    change_title(df);
    break;
}
case 8:
{
    search_value(df);
    break;
}
case 9:
{
    change_value(df);
    break;
}
case 10:
{
    display_column_names(df);
    break;
}
case 11: {
    display_row_column(df);
    break;
}
case 12:{
    int column_value = 0;
    while (column_value <= 0) {
        printf("Entrez le numero de la colonne : ");
        scanf("%d", &column_value);
    }
    update_index(df->column[column_value]);
    break;
}
case 13:{
    display_sorted_Cdataframe(df);
    break;
}
case 14:{
    int column_value = 0;
    while (column_value <= 0) {
        printf("Entrez le numero de la colonne : ");
        scanf("%d", &column_value);
    }
    sort_direction(df->column[column_value]);
    break;
}
case 15:{
    int column_value = 0;
    while (column_value <= 0) {
        printf("Entrez le numero de la colonne :\n ");
        scanf("%d", &column_value);
    }
    int id;
    id = check_index(df->column[column_value]);
    if(id==1)
        printf("l'index est valide\n");
    else {
        if (id == 0) {
            printf("l'index n'existe pas\n");
        }
        else {
            printf("l'index est invalide\n");
        }
    }
    break;
}
case 16:{
    int column_value = 0;
    while (column_value <= 0) {
        printf("Entrez le numero de la colonne : ");
        scanf("%d", &column_value);
    }
    erase_index(df->column[column_value]);
    break;
}
default:
printf("La saisie est invalide.\n");
break;
}
}
return 0;
}


