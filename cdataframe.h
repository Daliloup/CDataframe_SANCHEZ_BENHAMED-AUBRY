//
// Created by sanch on 29/03/2024.
//

#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "list.h"
#include "column.h"

typedef list CDATAFRAME;


// Basic Operations (Constructors, selectors, etc...)
CDATAFRAME *create_cdataframe();  // Will return empty doubly linked list;
void delete_cdataframe(CDATAFRAME **cdf);
void add_empty_column(CDATAFRAME *cdf, char *col_name, ENUM_TYPE *cdftype);
void delete_column_cdataframe(CDATAFRAME *cdf, char *col_name);
void delete_row_cdataframe(CDATAFRAME *cdf, int index);
void *get_value_cdataframe(CDATAFRAME *cdf, int col, int row);
void *set_value_cdataframe(CDATAFRAME *cdf, int col, int row, void *new_value);
void rename_col_cdataframe(CDATAFRAME *cdf, char *title, char *new_title);


// Higher Order operations
int get_cdataframe_cols_size(CDATAFRAME *cdf);
int is_in_cdataframe(CDATAFRAME *cdf, void *value);


// User Input
void fill_cdataframe(CDATAFRAME *cdf);
void add_column_user(CDATAFRAME *cdf);
void add_row_user(CDATAFRAME *cdf);
void set_new_value_cdataframe(CDATAFRAME *cdf, int i, int j);  // uses user input function from column.h
void display_partial_cdataframe(CDATAFRAME *cdf);  // user inputs the section he wants to see


// Display
void display_cdataframe(CDATAFRAME *cdf);
void display_col_names(CDATAFRAME *cdf);
void display_nb_rows(CDATAFRAME *cdf);
void display_nb_columns(CDATAFRAME *cdf);
void display_nb_equal_cdataframe(CDATAFRAME *cdf, void *value);
void display_nb_greater_cdataframe(CDATAFRAME *cdf, void *value);
void display_nb_less_cdataframe(CDATAFRAME *cdf, void *value);


// CSV Saving and Loading
CDATAFRAME* load_from_csv(char *file_name);
void save_into_csv(CDATAFRAME *cdf, char *file_name);


#endif
