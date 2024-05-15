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
    NULLVAL = 1, UNIT, INT, CHAR, FLOAT, DOUBLE, STRING
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
    unsigned int TP;
    unsigned int TL;
    COL_TYPE **data;
    ENUM_TYPE column_type;
    unsigned long long int *index;
    int valid_index;
    int sort_dir;
}COLUMN;

typedef struct {
    COLUMN **column;
    int nb_column;
}Cdataframe;


//PARTIE 2

COLUMN *create_column(ENUM_TYPE type, char*title);

int insert_value(COLUMN *col, void *value);

void delete_column(COLUMN **col);

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);

void print_col(COLUMN* col);

int nbr_occurence(COLUMN* col, void* value);

int nbr_occurence_sup(COLUMN* col, void* value);

int nbr_occurence_inf(COLUMN* col, void* value);

void *nbr_position(COLUMN *col, int position);

Cdataframe *create_Cdataframe();

void ajout_colonne(Cdataframe* Cdata, ENUM_TYPE type, char *title);

void insert_val_utilisateur(Cdataframe* Cdata);

void affichage_Cdataframe(Cdataframe *Cdata);

void ligne_affichage(Cdataframe* Cdata);

void colonne_affichage(Cdataframe *Cdata);

void changer_titre(Cdataframe *Cdata);

void rechercher_valeur(Cdataframe* Cdata);

void changer_valeur(Cdataframe *df);

void affichage_nbr_ligne_colonne(Cdataframe* Cdata);

void sort(COLUMN* col, int sort_dir);

void quicksort_acc(COLUMN* col,unsigned int gauche, unsigned int droite);

int partition_acc(COLUMN* col,unsigned int gauche, unsigned int droite);

void tri_insertion_acc(COLUMN* col);

void quicksort_dec(COLUMN* col,unsigned int gauche, unsigned int droite);

int partition_dec(COLUMN* col,unsigned int gauche, unsigned int droite);

void tri_insertion_dec(COLUMN* col);

void print_col_by_index(COLUMN *col);

void erase_index(COLUMN *col);

int check_index(COLUMN *col);

void update_index(COLUMN *col);

int search_value_in_column(COLUMN *col, void *val);

int recherche_dicho(COLUMN *col, void *val, int gauche, int droite);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H