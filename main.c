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

    Cdataframe *df = create_Cdataframe();
    if (df == NULL)
    {  //verifie qu'il a été créer ou pas*
        printf("erreur dans la création du  Cdataframe\n");
        return 1;
    }
    insert_val_utilisateur(df);
    display_Cdataframe((df));
    add_column(df,CHAR);
    display_Cdataframe(df);
    return 0;



/*
int nombre = 0;

while (1) { // Boucle infinie
printf("\nVoici le menu : \n");
printf("0) Quitter\n");
printf("1) Remplissage du CDataframe à partir de saisies utilisateurs\n");
printf("2) Afficher tout le CDataframe\n");
printf("3) Afficher une partie des lignes du CDataframe selon une limite fournie par l'utilisateur\n");
printf("4) Afficher une partie des colonnes du CDataframe selon une limite fournie par l'utilisateur\n");
printf("5) Ajouter une ligne de valeurs au CDataframe\n");
printf("6) Supprimer une ligne de valeurs du CDataframe\n");
printf("7) Ajouter une colonne au CDataframe\n");
printf("8) Supprimer une colonne du CDataframe\n");
printf("9) Renommer le titre d'une colonne du CDataframe\n");
printf("10) Vérifier l'existence d'une valeur (recherche) dans le CDataframe\n");
printf("11) Accéder/remplacer la valeur se trouvant dans une cellule du CDataframe\n");
printf("12) Afficher les noms des colonnes\n");2
printf("13) Afficher le nombre de lignes et de colonnes\n");
printf("14) Analyser une valeur x\n");
printf("\nSaisissez un nombre : ");

scanf("%d", &nombre);

switch (nombre) {
    case 0:
// Quitter le programme
return 0;
case 1:

break;
case 2:

case 3:

break;
case 4:

break;
case 5:
printf("Pas encore fait\n");
break;
case 6:

break;
case 7:

break;
case 8: {
int column_value = 0;
while (column_value <= 0) {
printf("Enter the column value : ");
scanf("%d", &column_value);
}
delete_column(&df->column[column_value]);
break;
}
case 9:

break;
case 10:

break;
case 11:

break;
case 12:

break;
case 13:

break;
case 14:
break;
default:
printf("La saisie est invalide.\n");
break;
}
}
return 0;
}
*/

}