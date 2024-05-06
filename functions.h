//
// Created by HIM on 28/03/2024.
//

#ifndef PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
#define PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
/**
 * Create a column
 * @param1 : Column title
 * @return : Pointer to created column
 */
enum enum_type
{
NULLVAL = 1, UNIT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;


union column_type{
unsigned int uint_value;
signed int int_value;
char char_value;
float float_value;
double double_value;
char* string_value;
void* struct_value;
};
typedef union column_type COL_TYPE ;

typedef struct
{
char* titre;
signed int TP;
unsigned int TL;
int* donnee;
COL_TYPE **data;
unsigned long long int *index;
ENUM_TYPE column_type;
}COLUMN;

typedef struct {
COLUMN **column;
int nb_column;
}Cdataframe;

COLUMN *create_column(char* title);

int insert_value(COLUMN* col, int value);

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int nbr_occurence(COLUMN* col, int x);

int nbr_position(COLUMN* col, int x);

int nbr_occurence_sup(COLUMN* col, int x);

int nbr_occurence_inf(COLUMN* col, int x);

int add_column (Cdataframe *Cdata);

Cdataframe *create_Cdataframe();

void insert_value_endur(Cdataframe *Cdata, int nb_rows, int nb_columns, int (*values)[4]);

void lim_rows_display (Cdataframe *Cdata);

void lim_column_display(Cdataframe *Cdata);

void insert_values_user(Cdataframe *Cdata);

void display_CDataframe(Cdataframe *Cdata);

void nouveau_titre(Cdataframe *df);

void verifier_valeur_existante(Cdataframe *df);

void modifier_valeur_cellule(Cdataframe *df);

void Affichage_nom_colonne(Cdataframe *df);

void Affichage_nbr_ligne_colonne(Cdataframe *df);

void analyser_valeur_x(Cdataframe *df);

//PARTIE 2

COLUMN *create_colum2(ENUM_TYPE type, char*title);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H