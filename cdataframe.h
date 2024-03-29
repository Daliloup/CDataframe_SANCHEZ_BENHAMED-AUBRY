//
// Created by sanch on 29/03/2024.
//

#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "list.h"

typedef list CDATAFRAME;

CDATAFRAME make_cdataframe(ENUM_TYPE *cdftype, int size);
void delete_cdataframe(CDATAFRAME **cdf);
void delete_column(CDATAFRAME *cdf, char *col_name);
int get_cdataframe_cols_size(CDATAFRAME *cdf);
void display_dataframe(CDATAFRAME *dataframe);

#endif
