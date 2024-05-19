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
    }
}

/*
void add_row_user(CDATAFRAME *cdf)
{
    lnode *node = cdf->head;
    while (node != NULL) {
        ask_value_user((COLUMN*)node->data);
        node = node->next;
    }
}
 */

void display_col_names(CDATAFRAME *cdf)
{
    lnode *node = cdf->head;
    while (node != NULL) {
        printf("%s ", ((COLUMN*)node->data)->title);
        node = node->next;
    }
    printf("\n");
}

void display_cdataframe(CDATAFRAME *cdf)
{
    display_col_names(cdf);
    lnode *node = cdf->head;
    if (node == NULL) return;

    char str[21];
    for (int i = 0; i < ((COLUMN*)node->data)->size; i++) {
        node = cdf->head;
        while (node != NULL) {
            convert_value((COLUMN*)node->data, i, str, 10);
            printf("%s ", str);
            node = node->next;
        }
    }
}
