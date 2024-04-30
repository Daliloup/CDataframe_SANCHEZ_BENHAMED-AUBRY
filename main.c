//
// Created by sanch on 26/04/2024.
//

#include "column.h"
#include <stdio.h>

int main()
{
    COLUMN *col = create_column(INT, "COLUMN 1");
    int value = 1, value2=2, value3=3;

    insert_value(col, &value);
    for (int i = 0; i < col->size; i++) {
        printf("%d\n\n", *col->data[i]);
    }

    insert_value(col, &value2);
    insert_value(col, &value3);
    for (int i = 0; i < col->size; i++) {
        printf("%d\n\n", *col->data[i]);
    }

    print_col(col);
    return 0;
}