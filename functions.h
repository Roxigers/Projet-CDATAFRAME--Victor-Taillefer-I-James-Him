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
    unsigned int TP;
    unsigned int TL;
    COL_TYPE **data;
    unsigned long long int *index;
    ENUM_TYPE column_type;
}COLUMN;

typedef struct {
    COLUMN **column;
    int nb_column;
}Cdataframe;


//PARTIE 2

COLUMN *create_colum(ENUM_TYPE type, char*title);

int insert_value(COLUMN *col, void *value);

void delete_column(COLUMN **col);

#endif //PROJET_CDATAFRAME__VICTOR_TAILLEFER_I_JAMES_HIM_FUNCTIONS_H
