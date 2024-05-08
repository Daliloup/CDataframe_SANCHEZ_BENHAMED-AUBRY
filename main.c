//
// Created by sanch on 26/04/2024.
//

#include "column.h"
#include <stdio.h>

int main()
{
    COLUMN *col = create_column(INT, "COLUMN 1");
    int value1 = 8, value2=2, value3=3, value4 = 16, value5=12, value6=26, value7 = 29, value8=17, value9=1;

    insert_value(col, &value1);
    for (int i = 0; i < col->size; i++) {
        printf("%d\n\n", *col->data[i]);
    }

    insert_value(col, &value2);
    insert_value(col, &value3);
    insert_value(col, &value4);
    insert_value(col, &value5);
    insert_value(col, &value6);
    insert_value(col, &value7);
    insert_value(col, &value8);
    insert_value(col, &value9);
    for (int i = 0; i < col->size; i++) {
        printf("%d\n", *col->data[i]);
    }
    printf("----------------------------------\n");
    print_col(col);
    printf("\n");
    print_col_by_index(col);

    printf("----------------------------------\n");

    for (int i = 0; i < col->size; i++) {
        printf("%d\n", *col->data[col->index[i]]);
    }
    printf("After sorting :\n");
    insertion_sort(col);
    for (int i=0; i<col->size; i++){
        printf("%d\n", *col->data[col->index[i]]);
    }

    printf("----------------------------------\n");
    print_col(col);
    printf("\n");
    print_col_by_index(col);
    printf("----------------------------------\n");

    return 0;
}