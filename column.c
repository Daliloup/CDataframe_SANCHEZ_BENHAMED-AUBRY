//
// Created by Yannis on 29/03/2024.
//

#include "column.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ASC 0
#define DESC 1


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
        printf("\nCheck 1");
        printf("\n%llu", _msize(col));
        col = (COLUMN*) realloc(col, _msize(col)+256);
        printf("\n%llu", _msize(col));
        printf("\nCheck 2");
        printf("\n%d", col->max_size);
        col->max_size += 256/sizeof(col->column_type);
        printf("\nCheck 3");
        printf("\n%d", col->max_size);
    }
    /*
     * This function doesn't work yet and produces an error when called
     * because col->data is set to NULL when creating a column
     */
    switch(col->column_type){
        case NULLVAL:
            col->data[col->size] = NULL;
            break;
        case UINT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(unsigned int));
            *((unsigned int*)col->data[col->size])= *((unsigned int*)value);
            break;
        case INT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(int));
            *((int*)col->data[col->size])= *((int*)value);
            break;
        case CHAR:
            printf("\nIt's a char");
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(char));
            printf("check 4");
            *((char*)col->data[col->size])= *((char*)value);
            printf("check 5");
            break;
        case FLOAT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(float));
            *((float*)col->data[col->size])= *((float*)value);
            break;
        case DOUBLE:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(double));
            *((double*)col->data[col->size])= *((double*)value);
            break;
        case STRING:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(char*));
            *((char**)col->data[col->size])= *((char**)value);
            break;
        case STRUCTURE:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(int));
            *((int*)col->data[col->size])= *((int*)value);
            break;
    }
    col->size++;
    return 1;
}