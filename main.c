//
// Created by sanch on 26/04/2024.
//

#include "column.h"
#include <stdio.h>

int main()
{
    COLUMN *col = create_column(INT, "COLUMN 1");
    int v0 = 0, v1 = 1, v2 = 2, v3 = 3;

    insert_value(col, &v1);
    for (int i = 0; i < col->size; i++) {
        printf("%d ", *col->data[i]);
    }

    printf("\n");
    insert_value(col, &v2);
    insert_value(col, &v3);
    for (int i = 0; i < col->size; i++) {
        printf("%d ", *col->data[i]);
    }
    printf("\n");

    //replace_value_column(col, 1);
    //for (int i = 0; i < col->size; i++) {
    //    printf("%d ", *col->data[i]);
    //}

    //printf("%d", data_cmp(UINT, &v3, &v2));

    //printf("\n%d\n", v2);
    //printf("Occurrences: %d\n", occurrence(col, &v2));
    //printf("Greater: %d\n", greater_than(col, &v2));
    //printf("Lower: %d", lower_than(col, &v2));
    return 0;
}