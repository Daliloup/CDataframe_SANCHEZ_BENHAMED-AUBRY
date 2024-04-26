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
    col->index[col->size] = col->size;
    col->size++;
    return 1;
}


void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
    int num_of_char;
    if (col->data[i] == NULL) {
        strcpy(str, "NULL");
        return ;
    }
    switch (col->column_type) {
        case UINT: {
           num_of_char = snprintf(str, size, "%llu", *(col->data[i]));
           break;
        }
        case INT: {
            num_of_char = snprintf(str, size, "%d", *(col->data[i]));
            break;
        }
        case CHAR: {
            num_of_char = snprintf(str, size, "%char", *(col->data[i]));
            break;
        }
        case FLOAT: {
            num_of_char = snprintf(str, size, "%f", *(col->data[i]));
            break;
        }
        case DOUBLE: {
            num_of_char = snprintf(str, size, "%lf", *(col->data[i]));
            break;
        }
        case STRING: {
            num_of_char = snprintf(str, size, "%s", *(col->data[i]));
            break;
        }
        case NULLVAL: {
            num_of_char = snprintf(str, size, "%d", *(col->data[i]));
            break;
        }
    }
}

void delete_column(COLUMN **col)
{
    if ((*col)->max_size != 0) {
        free((*col)->data);
        free((*col)->index);
    }
    free(*col);
    *col = NULL;
}


int occurrence(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case (UINT):
                if (*(unsigned int*)(col->data[i]) == *((unsigned int*) x)) {
                    s++;
                }
                break;
            case (INT):
                if (*((int*)(col->data[i])) == *((int*) x)) {
                    s++;
                }
                break;
            case (CHAR):
                if (*(char*)(col->data[i]) == *((char*) x)) {
                    s++;
                }
                break;
            case (FLOAT):
                if (*(float*)(col->data[i]) == *((float*) x)) {
                    s++;
                }
                break;
            case (DOUBLE):
                if (*(double*)(col->data[i]) == *((double*) x)) {
                    s++;
                }
                break;
            case (STRING):
                if (strcmp(*(char**)(col->data[i]), *((char**) x)) == 0) {
                    s++;
                }
                break;
            default:;
        }
    }
    return s;
}

int greater_than(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case (UINT):
                if (*(unsigned int*)(col->data[i]) > *((unsigned int*) x)) {
                    s++;
                }
                break;
            case (INT):
                if (*((int*)(col->data[i])) > *((int*) x)) {
                    s++;
                }
                break;
            case (CHAR):
                if (*(char*)(col->data[i]) > *((char*) x)) {
                    s++;
                }
                break;
            case (FLOAT):
                if (*(float*)(col->data[i]) > *((float*) x)) {
                    s++;
                }
                break;
            case (DOUBLE):
                if (*(double*)(col->data[i]) > *((double*) x)) {
                    s++;
                }
                break;
            case (STRING):
                if (strcmp(*(char**)(col->data[i]), *((char**) x)) > 0) {
                    s++;
                }
                break;
            default:;
        }
    }
    return s;
}

int lower_than(COLUMN *col, void *x)
{
    int s = 0;
    for (int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case (UINT):
                if (*(unsigned int*)(col->data[i]) < *((unsigned int*) x)) {
                    s++;
                }
                break;
            case (INT):
                if (*((int*)(col->data[i])) < *((int*) x)) {
                    s++;
                }
                break;
            case (CHAR):
                if (*(char*)(col->data[i]) < *((char*) x)) {
                    s++;
                }
                break;
            case (FLOAT):
                if (*(float*)(col->data[i]) < *((float*) x)) {
                    s++;
                }
                break;
            case (DOUBLE):
                if (*(double*)(col->data[i]) < *((double*) x)) {
                    s++;
                }
                break;
            case (STRING):
                if (strcmp(*(char**)(col->data[i]), *((char**) x)) < 0) {
                    s++;
                }
                break;
            default:;
        }
    }
    return s;
}

void* value_with_position(COLUMN *col, int pos)
{
    int i = 0;
    while ((col->index[i] != pos) && (i < col->size)) ++i;

    if (i == col->size) return NULL;
    return col->data[i];
}