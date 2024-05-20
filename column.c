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
    printf("%f\n", *(float*)value);

    switch (col->column_type){
        case UINT: {
            col->data[col->size] = (unsigned long long int*) value;
            break;
        }
        case INT: {
            col->data[col->size] = (int*) value;
            break;
        }
        case CHAR: {
            col->data[col->size] = (char*) value;
            break;
        }
        case FLOAT: {
            printf("%d here\n", *(col->data[col->size]));
            col->data[col->size]->float_value = *(float*) value;
            printf("%d here\n", *(col->data[col->size]));
            break;
        }
        case DOUBLE: {
            col->data[col->size] = (double*) value;
            break;
        }
        case STRING: {
            col->data[col->size] = (char**) value;
            break;
        }
        case NULLVAL: {
            break;
        }
    }

    //col->data[col->size] = value;
    col->index[col->size] = col->size;
    col->size++;
    if (col->valid_index == 1){
        col->valid_index = -1;
    } else if (col->valid_index == -1){
        col->valid_index = 0;
    }
    printf("nickel\n");
    print_col_by_index(col);
    return 1;
}

unsigned long long int index_convert(COLUMN *col, unsigned long long int i){
    unsigned long long int j = 0;
    while ((col->index[j] != i) && (j < col->size)) ++j;

    if (j == col->size) return -1;
    return j;
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
            snprintf(str, size, "%c", *(col->data[i]));
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
    char str[12];
    printf("%s\n", col->title);
    unsigned long long int j;
    for (int i = 0; i < col->size; i++) {
        j = col->index[i];
        convert_value(col, j, str, 12);
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

void* value_with_position(COLUMN *col, unsigned long long int pos)
{
    printf("----------------\n%llu\n", pos);
    pos = index_convert(col, pos);
    printf("%llu\n-----------------------\n", pos);

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
            printf("Enter value (double): ");
            scanf(" %lf", col->data[i]);
            break;
        case STRING:
            printf("Enter value (string: ");
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

int partition(COLUMN *col, int left, unsigned int right){
    int pivot_index = left;
    int i = left;
    unsigned long long int temp;
    for (int j = left+1; j < right ; j++){
        if (data_cmp(col->column_type, col->data[col->index[j]], col->data[col->index[pivot_index]]) == -1){
            temp = col->index[i];
            col->index[i] = col->index[j];
            col->index[j] = temp;
        }
    }
    unsigned long long int temp2 = col->index[i];
    col->index[i] = col->index[pivot_index];
    col->index[pivot_index] = temp2;
    return i;
}

void quick_sort(COLUMN *col, int left, unsigned int right){
    if (left < right){
        int pi = partition(col, left, right);
        quick_sort(col, left, pi);
        quick_sort(col, pi+1, right);
    }
}

void reverse(COLUMN *col){
    int i = 0;
    unsigned long long int temp;
    while (i < col->size - i){
        temp = col->index[i];
        col->index[i] = col->index[col->size - i-1];
        col->index[col->size - i-1] = temp;
        i++;
    }
}
void sort(COLUMN *col, int sort_dir){
    if (col->valid_index == 0){
        quick_sort(col, 0, col->size);
    } else {
        insertion_sort(col);
    }
    if (sort_dir == DESC){
        reverse(col);
    }
    col->valid_index = 1;
}

void erase_index(COLUMN *col){
    free(col->index);
    col->index = NULL;
    col->valid_index = 0;
}

int check_index(COLUMN *col){
    if (col->index == NULL) return 0;
    if (col->valid_index == 1) return 1;
    return -1;
}

void update_index(COLUMN *col){
    sort(col, col->sort_dir);
}

int search_value_in_column(COLUMN *col, void *val){
    unsigned int l = 0, r = col->size -1;
    if (col->valid_index != 1) return -1;

    int k;
    while (l <= r){
        k = data_cmp(col->column_type, val, col->data[col->index[(r+l)/2]]);
        switch(k){
            case -1:
                r = ((l+r)/2) - 1;
                break;
            case 1:
                l = ((l+r)/2) + 1;
                break;
            case 0:
                return 1;
        }
    }
    return 0;
}

void delete_with_index(COLUMN *col, unsigned long long int i){
    unsigned long long int asso_index = col->index[i];
    free(col->data[asso_index]);

    unsigned long long int j = i;
    while (j+1 < col->size){
        col->index[j] = col->index[j+1];
        j++;
    }
    col->index[j] = -1;

    j = 0;
    while (asso_index + j+1 < col->size) {
        col->data[asso_index + j] = col->data[asso_index + j+1];
        (col->index[index_convert(col,asso_index + j+1)])--;
        j++;
    }

    (col->size)--;
}

void copy_index(COLUMN *main_col, COLUMN *col){
    for (int i=0 ; i < main_col->size ; i++){
        col->index[i] = main_col->index[i];
    }
}