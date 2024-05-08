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

unsigned long long int index_convert(COLUMN *col, int i)
{
    /*unsigned long long int j = 0;
    while ((col->index[j] != i) && (j < col->size)) ++j;

    if (j == col->size) return -1;
    return j;
    */
    return col->index[i];
}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
    int num_of_char;
    if (col->data[i] == NULL) {
        strcpy(str, "NULL");
        return ;
    }
    switch (col->column_type) {
        case UINT: {
           snprintf(str, size, "%llu", *(col->data[i]));
           break;
        }
        case INT: {
            snprintf(str, size, "%d", *(col->data[i]));
            break;
        }
        case CHAR: {
            snprintf(str, size, "%char", *(col->data[i]));
            break;
        }
        case FLOAT: {
            snprintf(str, size, "%f", *(col->data[i]));
            break;
        }
        case DOUBLE: {
            snprintf(str, size, "%lf", *(col->data[i]));
            break;
        }
        case STRING: {
            snprintf(str, size, "%s", *(col->data[i]));
            break;
        }
        case NULLVAL: {
            snprintf(str, size, "%d", *(col->data[i]));
            break;
        }
    }
}

void print_col(COLUMN* col){
    char* string = (char*) malloc(sizeof(char*));
    int i;
    for (i=0 ; i < col->size ; i++){
        convert_value(col, i, string, 100);
        printf("[%d] %s\n", i, string);
    }
    free(string);
}

void print_col_by_index(COLUMN *col)
{
    char str[9];
    printf("%s\n", col->title);
    unsigned long long int j;
    for (int i = 0; i < col->size; i++) {
        j = index_convert(col, i);
        convert_value(col, j, str, 8);
        printf("[%d] %s\n", i, str);
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

void insertion_sort(COLUMN *col) {
    int i, j;
    unsigned long long int k;

    for (i = 1; i < col->size; i++) {
        k = col->index[i];
        j = i - 1;
        while ( (j >= 0)  &&  data_cmp(col->column_type, (col->data[col->index[j]]), col->data[k]) == 1) {
            col->index[j + 1] = col->index[j];
            j--;
        }
        col->index[j + 1] = k;
    }

}

int partition(int* tab, int left, int right){
    int pivot = tab[right];
    int i = left - 1;
    int temp;
    for (int j = left; j < right ; j++){
        if (tab[j] <= pivot){
            i++;
            temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    int temp2 = tab[i+1];
    tab[i+1] = tab[right];
    tab[right] = temp2;
    return i+1;
}

void quick_sort(int* tab, int left, int right){
    if (left < right){
        int pi = partition(tab, left, right);
        quick_sort(tab, left, pi-1);
        quick_sort(tab, pi+1, right);
    }
}
/*
void sort(COLUMN *col, int sort_dir){
    if (col->valid_index == 0){
        quick_sort(col)
    }
}
 */