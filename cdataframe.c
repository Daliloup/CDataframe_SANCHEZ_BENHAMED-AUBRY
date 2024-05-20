//
// Created by sanch on 29/03/2024.
//

#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CDATAFRAME *create_cdataframe()
{
    CDATAFRAME *cdf = lst_create_list();
    return cdf;
}

void delete_cdataframe(CDATAFRAME **cdf) {
    cdf_erase(*cdf);
    free(*cdf);
    *cdf = NULL;
}

void cdf_erase(CDATAFRAME *cdf) {
    if (cdf->head == NULL)
        return;
    while (cdf->head != cdf->tail) {
        delete_column((COLUMN**) &cdf->head->data);
        cdf->head = cdf->head->next;
        free(cdf->head->prev);
    }
    free(cdf->head);
    cdf->head = NULL;
    cdf->tail = NULL;
}

void add_empty_column(CDATAFRAME *cdf, char *col_name, ENUM_TYPE cdftype)
{
    COLUMN *new_col = create_column(cdftype, col_name);
    lst_insert_tail(cdf, lst_create_lnode(new_col));
}

void delete_column_cdataframe(CDATAFRAME *cdf, char *col_name)
{
    lnode *node = cdf->head;
    if (strcmp(((COLUMN*)node->data)->title, col_name) == 0) {
        delete_column((COLUMN**)&cdf->head->data);
        cdf->head = cdf->head->next;
        return;
    }

    while (node->next != NULL) {
        if (strcmp(((COLUMN*)node->next->data)->title, col_name) == 0) {
            delete_column((COLUMN**)&node->next->data);
            node->next = node->next->next;
            free(node->next);
            return;
        }
        node = node->next;
    }
}

void delete_row_cdataframe(CDATAFRAME *cdf, int index)
{
    lnode *node = cdf->head;
    while (node != NULL) {
        delete_with_index(node->data, index);
        node = node->next;
    }
}

void rename_col_cdataframe(CDATAFRAME *cdf, char *title, char *new_title)
{
    lnode *node = cdf->head;
    while ((node != NULL) && (strcmp(((COLUMN*)node->data)->title, title) != 0)) {
        node = node->next;
    }

    if (node == NULL) return;
    ((COLUMN*)node->data)->title = new_title;
}

void fill_cdataframe(CDATAFRAME *cdf)
{
    int nb_col, nb_row, i;
    ENUM_TYPE cdf_type;

    printf("Number of columns: ");
    scanf("%d", &nb_col);
    for (i = 0; i < nb_col; i++) {
        char *title = (char*) malloc(sizeof(char) * 20);

        printf("\nCOLUMN %d\n", i+1);
        printf("[1.NULLVALUE, ");
        printf("2.U_INT, ");
        printf("3.INT, ");
        printf("4.CHAR, ");
        printf("5.FLOAT, ");
        printf("6.DOUBLE, ");
        printf("7.STRING]");
        printf("\nWhich type? ");

        scanf(" %d", &cdf_type);

        printf("Title: ");
        fflush(stdin);
        gets(title);

        add_empty_column(cdf, title, cdf_type);
        //printf("%s - %d", ((COLUMN*)cdf->head->data)->title, ((COLUMN*)cdf->head->data)->column_type);
    }

    printf("\nNumber of rows: ");
    scanf(" %d", &nb_row);

    for (i = 0; i < nb_row; i++) {
        printf("Row %d\n", i+1);
        add_row_user(cdf);
    }
    printf("\n");
}


void add_row_user(CDATAFRAME *cdf)
{
    lnode *node = cdf->head;
    while (node != NULL) {
        switch (((COLUMN*)node->data)->column_type) {
            case UINT:
            {
                unsigned long long int *i = (unsigned long long int*) malloc(sizeof(unsigned long long int));
                printf("Enter value (uint): ");
                scanf(" %llu", i);
                insert_value((COLUMN*)node->data, i);
                break;
            }
            case INT: {
                int *i = (int*) malloc(sizeof(int));
                printf("Enter value (int): ");
                scanf(" %d", i);
                insert_value((COLUMN *) node->data, i);
                break;
            }
            case CHAR: {
                char *i = (char*) malloc(sizeof(char));
                printf("Enter value (char): ");
                scanf(" %c", i);
                insert_value((COLUMN *) node->data, i);
                break;
            }
            case FLOAT: {
                float *i = (float*) malloc(sizeof(float));
                printf("Enter value (float): ");
                scanf(" %f", i);
                insert_value((COLUMN *) node->data, i);
                break;
            }
            case DOUBLE: {
                double *i = (double*) malloc(sizeof(double));
                printf("Enter value (double): ");
                scanf(" %lf", i);
                insert_value((COLUMN *) node->data, i);
                break;
            }
            case STRING: {
                char *i = (char*) malloc(20*sizeof(char));
                printf("Enter value (string): ");
                fflush(stdin);
                gets(i);
                printf("%s\n", i);
                printf("Alors ?\n");
                insert_value((COLUMN *) node->data, &i);
                printf("test\n");
                printf("%s\n", ((COLUMN*) node->data)->data[((COLUMN*) node->data)->size]);
                printf("EEEET\n");
                break;
            }
        }
        node = node->next;
    }
}

void display_col_names(CDATAFRAME *cdf)
{
    lnode *node = cdf->head;
    if (node == NULL){
        printf("EMPTY_DATAFRAME");
        return;
    }

    int i;
    printf("      |");
    while (node != NULL) {
        print_in_cdataframe(((COLUMN*)node->data)->title);
        node = node->next;
    }
    printf("\n");
}

int get_string_size(char *str){
    int size = 0;
    while (str[size] != '\0'){
        size++;
    }
    return size;
}

void print_in_cdataframe(char *str){
    int i;
    int size_str = get_string_size(str);
    for ( i=0 ; i < (12- size_str)/2 ; i++){
        printf(" ");
    }
    printf("%s", str);
    for (i=0 ; i < 12 - (size_str + (12-size_str)/2) ; i++){
        printf(" ");
    }
    printf("|");
}

void display_cdataframe(CDATAFRAME *cdf)
{
    display_col_names(cdf);
    lnode *node = cdf->head;
    if (node == NULL) return;

    char str[21];
    int max = ((COLUMN*) node->data)->size;
    for (int i = 0; i < max; i++) {
        printf("[%d", i);
        if (i<10) printf("]   |");
        else if (i < 100) printf("]  |");
        else if (i < 1000) printf("] |");
        node = cdf->head;
        while (node != NULL) {
            convert_value((COLUMN*)node->data, ((COLUMN*)node->data)->index[i], str, 12);
            print_in_cdataframe(str);
            node = node->next;
        }
        printf("\n");
    }
}

int get_cdataframe_cols_size(CDATAFRAME *cdf){
    lnode *node = cdf->head;
    if (node == NULL) return 0;

    int num_cols = 0;
    while (node != NULL){
        num_cols++;
        node = node->next;
    }
    return num_cols;
}

void set_new_value_cdataframe(CDATAFRAME *cdf, int i, int j){
    lnode *node = cdf->head;
    while ((j > 0) && (node != NULL)){
        j--;
        node = node->next;
    }
    if ((j > 0) || (node == NULL)){
        printf("Index out of range. Nothing has been done\n");
        return;
    }
    if (((COLUMN*)node->data)->size <= i){
        printf("Index out of range. Nothing has been done\n");
        return;
    }
    replace_value_column(node->data, i);
}

void sort_dataframe_column(CDATAFRAME *cdf, char *title){
    lnode *node = cdf->head;
    if (node == NULL) return;
    while ( strcmp(((COLUMN*)node->data)->title, title ) != 0){
        node = node->next;
        if (node == NULL){
            printf("Column not found\n");
            return;
        }
    }
    lnode *main_node = node;
    node = cdf->head;
    update_index((COLUMN*)main_node->data);
    while (node != NULL){
        copy_index(main_node->data, node->data);
        node = node->next;
    }
}