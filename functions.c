#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>

COLUMN *create_column(char* title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    new_column->titre = (char*) malloc(sizeof(title)+1);
    strcpy(new_column->titre, title);
    new_column->donnee = NULL;
    new_column->TP = 0;
    new_column->TL = 0;
    return new_column;
}



/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/

int insert_value(COLUMN* col, int value)
{
    int retour = 1;
    /** verification des cas ou il est necessaire d'agrandir l'espace aloue*/
    if ((col->TP - col->TL == 0) || (col->donnee == NULL) )
    {

        if (col->donnee == NULL)
        {
            /** allocation en cas de création d'espace et ajout de la variable */
            col->donnee = malloc((col->TP+256)*sizeof(int));
            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
        else
        {
            /** reallocatoin lorsqu'il n'y a plus de place et ajout de la variable */
            realloc(col->donnee, (col->TP+256)*sizeof(int));

            col->TP += 256;
            col->donnee[col->TL] = value;
            col->TL += 1;
        }
    }
    else
    {
        /** ajout de la variable si il n'y a pas besoin d'allocation */
        col->donnee[col->TL] = value;
        col->TL += 1;
    }
    /** verification si le malloc ou realloc */
    if (col->donnee == NULL)
    {
        retour = 0;
    }
    return retour;
}

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN **col)
{

    free((*col)->donnee);
    free((*col)->titre);
    free(*col);
}


/**
* @brief: Print a column content
* @param:  pointer to a column
*/
void print_col(COLUMN* col)
{

    for(int i=0;i<(col->TL);i++)
        printf("[%d] %d\n",i,col->donnee[i]);
}

/**Retourner le nombre de d’occurrences d’une valeur x (x donné en paramètre).*/

int nbr_occurence(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] == x)
        {
            cpt++;
        }
    }
    return cpt;
}

/**Retourner la valeur présente à la position x (x donné en paramètre).*/

int nbr_position(COLUMN* col, int x)
{
    int nombre;
    nombre = col->donnee[x];
    return nombre;
}

/**Retourner le nombre de valeurs qui sont supérieures à x (x donné en paramètre).*/

int nbr_occurence_sup(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] > x)
        {
            cpt++;
        }
    }
    return cpt;
}

/** Retourner le nombre de valeurs qui sont inférieures à x (x donné en paramètre).*/

int nbr_occurence_inf(COLUMN* col, int x)
{
    int cpt=0;
    for (int i=0;i<col->TL;i++)
    {
        if (col->donnee[i] < x)
        {
            cpt++;
        }
    }
    return cpt;
}

int add_column (Cdataframe *Cdata)
{
    char title[50];
    printf("Enter title for column : ");
    scanf("%s", title);
    COLUMN *new_column = create_column(title);

    COLUMN **new_columns = realloc(Cdata->column, (Cdata-> nb_column + 1) * sizeof(COLUMN *));
    Cdata->column = new_columns;
    Cdata->column[Cdata->nb_column] = new_column;
    Cdata->nb_column++;

    printf("Enter values for the new column : \n");
    for (int i = 0; i < Cdata->column[0]->TL;i++){
        int value;
        printf("Enter value for row %d: ", i + 1);
        scanf("%d", &value);
        insert_value(Cdata->column[Cdata->nb_column-1], value);
    }
    return 1;
}

Cdataframe *create_Cdataframe()
{
    Cdataframe *Cdataframe = malloc(sizeof(Cdataframe));
    Cdataframe ->column = NULL;
    Cdataframe -> nb_column = 0;
    return Cdataframe;
}


void insert_value_endur(Cdataframe *Cdata, int nb_rows, int nb_columns, int (*values)[4]) {
    for (int i = 0; i < nb_columns; i++) {
        add_column(Cdata);

        for (int j = 0; j < nb_rows; j++) {
            insert_value(Cdata->column[i], values[j][i]);
        }
    }
}

void lim_rows_display (Cdataframe *Cdata)
{
    int lim_rows = 0;
    while (lim_rows <= 0)
    {
        printf("Enter the row limit value : ");
        scanf("%d",&lim_rows);
    }
    for ( int i =0; i<Cdata->nb_column;i++)
    {
        printf("%s    ", Cdata->column[i]->titre);
    }
    printf("\n");

    for (int i=0;i<lim_rows && i < Cdata-> column[0]->TL;i++)
    {
        for (int j =0; j<Cdata->nb_column; j++)
        {
            printf("%d   ", Cdata->column[j]->donnee[i]);
        }
        printf("\n");
    }
}

void lim_column_display (Cdataframe *Cdata)
{
    int lim_column = 0;
    while (lim_column <= 0)
    {
        printf("Enter the column limit value : ");
        scanf("%d",&lim_column);
    }

    for ( int i =0; i<Cdata->nb_column;i++)
    {
        printf("%s    ", Cdata->column[i]->titre);
    }
    printf("\n");
    for (int i = 0; i < Cdata->column[0]->TL;i++)
    {
        for (int j=0; j< lim_column; j++)
        {
            printf("%d   ", Cdata->column[j]->donnee[i]);
        }
        printf("\n");
    }
}

void insert_values_user(Cdataframe *Cdata) {
    int nb_rows = 0, nb_columns = 0;

    printf("Enter the number of rows: ");
    scanf("%d", &nb_rows);

    printf("Enter the number of columns: ");
    scanf("%d", &nb_columns);

    for (int i = 0; i < nb_columns; i++) {
        add_column(Cdata);
    }

    for (int i = 0; i < nb_rows; i++) {
        printf("Enter values for row %d:\n", i + 1);
        for (int j = 0; j < nb_columns; j++) {
            int value;
            printf("Enter value for column %d: ", j);
            scanf("%d", &value);
            insert_value(Cdata->column[j], value);
        }
    }
}

void display_CDataframe(Cdataframe *Cdata)
{
    printf("Affichage du CDataframe : \n");
    for (int i = 0; i< Cdata->nb_column;i++)
    {
        printf("%s \t", Cdata->column[i]->titre);
    }
    printf("\n");

    for (int i = 0; i < Cdata->column[0]->TL; i++) //On suppose qu'elles ont toute le meme nombre de ligne
    {
        for (int j = 0; j<Cdata->nb_column;j++)
        {
            printf("%d\t",Cdata->column[j]->donnee[i]);
        }
        printf("\n");
    }
}

void nouveau_titre(Cdataframe *df) {
    int column_value = 0;
    char nouveau_titre[50];
    while (column_value <= 0)
    {
        printf("Enter the column value : ");
        scanf("%d", &column_value);
    }
    printf("Nouveau Titre : ");
    scanf("%s", nouveau_titre);
    strcpy(df->column[column_value]->titre, nouveau_titre);
}

void verifier_valeur_existante(Cdataframe *df) {
    int search_value;
    int cpt;
    printf("Enter a desired value : ");
    scanf("%d", &search_value);
    cpt = nbr_occurence(df, search_value);
    if (cpt != 0) {
        printf("The value exists.\n");
    } else {
        printf("The value does not exist.\n");
    }
}

void modifier_valeur_cellule(Cdataframe *df) {
    int row_value = 0;
    while (row_value <= 0) {
        printf("Enter the row value : ");
        scanf("%d", &row_value);
    }

    int column_value = 0;
    while (column_value <= 0) {
        printf("Enter the column value : ");
        scanf("%d", &column_value);
    }

    int new_value;
    printf("Enter the new value : ");
    scanf("%d", &new_value);

    df->column[column_value]->donnee[row_value] = new_value;
}

void Affichage_nom_colonne(Cdataframe *df)
{
    for (int i = 0; i < df->nb_column; i++)
    {
        printf("Column %d: %s\n", i, df->column[i]->titre);
    }
}

void Affichage_nbr_ligne_colonne(Cdataframe *df)
{
    printf("\nNumber of rows : %d",df->column[0]->TL);
    printf("\nNumber of columns : %d",df->nb_column);
}

void analyser_valeur_x(Cdataframe *df) {
    int x;
    printf("Enter a value for x: ");
    scanf("%d", &x);

    for (int i = 0; i < df->nb_column; i++) {
        printf("Column %d:\n", i);
        printf("Number of cells containing the value %d : %d\n", x, nbr_occurence(df->column[i], x));
        printf("Number of cells greater than the value %d : %d\n", x, nbr_occurence_sup(df->column[i], x));
        printf("Number of cells less than the value %d : %d\n", x, nbr_occurence_inf(df->column[i], x));
    }
}

// PARTI 2

COLUMN *create_colum2(ENUM_TYPE type, char*title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    if (new_column==NULL){
        return NULL;
    }
    new_column->titre = (char*) malloc(sizeof(title)+1);
    strcpy(new_column->titre, title);
    new_column->donnee = NULL;
    new_column->TP = 0;
    new_column->TL = 0;
    new_column->data = NULL;
    new_column-> index = NULL;
    new_column ->column_type = type;
    return new_column;
}