//
// Created by HIM on 28/03/2024.
//
#include "functions.h"
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(char* title)
{
    COLUMN* new_column = (COLUMN*) malloc(sizeof(COLUMN));
    strcpy(new_column->titre, title);
    new_column->donnee = NULL;
    new_column->TP = 0;
    new_column->TL = 0;
    return new_column;
}
