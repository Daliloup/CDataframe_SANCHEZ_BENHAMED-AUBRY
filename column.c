//
// Created by Yannis on 29/03/2024.
//

#include "column.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ASC 0
#define DESC 1

int sizeof_coldata_ptr(COLUMN *col)
{
    switch (col->column_type) {
        case UINT: return sizeof(unsigned int*);
        case INT: return sizeof(int*);
        case CHAR: return sizeof(char*);
        case FLOAT: return sizeof(float*);
        case DOUBLE: return sizeof(double*);
        case STRING: return sizeof(char**);
        default: return sizeof(NULL);
    }
}


COLUMN* create_column(ENUM_TYPE type, char *title){
    COLUMN *ptr, *new_column;

    ptr = (COLUMN*) malloc(sizeof(COLUMN));
    if (ptr == NULL) {return NULL;}
    new_column = ptr;

    new_column->title = title;
    new_column->size = 0;
    new_column->max_size = 0;
    new_column->column_type = type;
    new_column->data = NULL;
    new_column->index = NULL;
    new_column->valid_index = 0;
    new_column->sort_dir = 0;

    return new_column;
}

int insert_value(COLUMN *col, void *value){
// check memory space
    if (col->size == col->max_size){
        void *ptr = NULL, *ptr2 = NULL;

        if (col->max_size == 0) {
            ptr = malloc(sizeof_coldata_ptr(col) * REALLOC_SIZE);
            ptr2 = (int*) malloc(sizeof(int) * REALLOC_SIZE);
        } else {
            ptr = realloc(col->data, col->max_size + REALLOC_SIZE);
            ptr2 = (int*) realloc(col->index, col->max_size + REALLOC_SIZE);
        }

        if ((ptr == NULL) || (ptr2 == NULL)) {
            return 0;
        }
        col->data = ptr;
        col->index = ptr2;

        col->max_size = col->max_size + REALLOC_SIZE;
    }

    col->data[col->size] = value;
    col->size++;
    return 1;
}