
#ifndef PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
#define PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H

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
};
typedef union column_type COL_TYPE ;

typedef struct
{
    char* title;
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

Cdataframe *create_Cdataframe();

void add_column(Cdataframe *Cdataframe, ENUM_TYPE type);

void insert_val_utilisateur(Cdataframe* Cdata);

void display_Cdataframe(Cdataframe *Cdata);

void display_sorted_Cdataframe(Cdataframe *Cdata);

void display_row(Cdataframe* Cdata);

void display_column(Cdataframe *Cdata);

void change_title(Cdataframe *Cdata);

void search_value(Cdataframe* Cdata);

void change_value(Cdataframe *df);

void display_row_column(Cdataframe* Cdata);

void display_column_names(Cdataframe* df);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
