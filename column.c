//
// Created by Yannis on 29/03/2024.
//

#include "column.h"
#include <string.h>
#include <stdlib.h>


COLUMN* create_column(ENUM_TYPE type, char *title){
    COLUMN *new_column = (COLUMN*) malloc(sizeof(COLUMN));
    new_column->title = title;
    new_column->size = 0;
    new_column->max_size = 0;
    new_column->column_type = type;
    new_column->data = NULL;
    new_column->index = NULL;

    return new_column;
}