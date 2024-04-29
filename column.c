//
// Created by Yannis on 29/03/2024.
//

#include "column.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int data_cmp(ENUM_TYPE enum_type, void *val1, void *val2)
{
    int i = 0, j;
    switch (enum_type) {
        case UINT:
            if (*(unsigned int*)val1 < *(unsigned int*)val2) i = -1;
            else if (*(unsigned int*)val1 > *(unsigned int*)val2) i = 1;
            break;
        case INT:
            if (*(int*)val1 < *(int*)val2) i = -1;
            else if (*(int*)val1 > *(int*)val2) i = 1;
            break;
        case CHAR:
            if (*(char*)val1 < *(char*)val2) i = -1;
            else if (*(char*)val1 > *(char*)val2) i = 1;
            break;
        case FLOAT:
            if (*(float*)val1 < *(float*)val2) i = -1;
            else if (*(float*)val1 > *(float*)val2) i = 1;
            break;
        case DOUBLE:
            if (*(double*)val1 < *(double*)val2) i = -1;
            else if (*(double*)val1 > *(double*)val2) i = 1;
            break;
        case STRING:
            j = strcmp(val1, val2);
            if (j < 0) i = -1;
            else if (j > 0) i = 1;
            break;
        default:;
    }
    return i;
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
    col->index[col->size] = col->size;
    col->size++;
    return 1;
}

int index_convert(COLUMN *col, int i)
{
    int j = 0;
    while ((col->index[i] != i) && (i < col->size)) ++j;

    if (j == col->size) return -1;
    return j;
}

void delete_column(COLUMN **col)
{
    if ((*col)->max_size != 0) {
        free((*col)->data);
        free((*col)->index);
        free((*col)->title);
    }
    free(*col);
    *col = NULL;
}


int occurrence(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        s += (data_cmp(col->column_type, x, col->data[i]) == 0);
    }
    return s;
}

int greater_than(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        s += (data_cmp(col->column_type, x, col->data[i]) == 1);
    }
    return s;
}

int lower_than(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        s += (data_cmp(col->column_type, x, col->data[i]) == -1);
    }
    return s;
}

void* value_with_position(COLUMN *col, int pos)
{
    pos = index_convert(col, pos);

    if (pos == -1) return NULL;
    return col->data[pos];
}

void replace_value_column(COLUMN *col, int i)
{
    i = index_convert(col, i);

    if (i == -1) return;

    switch (col->column_type) {
        case UINT:
            printf("Enter value (u_int): ");
            scanf(" %u", col->data[i]);
            break;
        case INT:
            printf("Enter value (int): ");
            scanf(" %d", col->data[i]);
            break;
        case CHAR:
            printf("Enter value (char): ");
            scanf(" %c", col->data[i]);
            break;
        case FLOAT:
            printf("Enter value (float): ");
            scanf(" %f", col->data[i]);
            break;
        case DOUBLE:
            printf("Enter value (int): ");
            scanf(" %lf", col->data[i]);
            break;
        case STRING:
            printf("Enter value (int): ");
            gets(col->data[i]);
            break;
        default:;
    }
}