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
    insert_value(col, &value2);
    insert_value(col, &value3);
    insert_value(col, &value4);
    insert_value(col, &value5);
    insert_value(col, &value6);
    insert_value(col, &value7);
    insert_value(col, &value8);
    insert_value(col, &value9);

    printf("----------------------------------\nprint_col\n");
    print_col(col);
    printf("print_col_by_index\n");
    print_col_by_index(col);

    printf("----------------------------------\n");


    sort(col, ASC);
    printf("After sorting :\nprint_col\n");
    print_col(col);
    printf("print_col_by_index\n");
    print_col_by_index(col);
    printf("----------------------------------\nAfter reversing :\n");
    /*
    reverse(col);
    printf("print_col\n");
    print_col(col);
    printf("print_col_by_index\n");
    print_col_by_index(col);
    printf("----------------------------------\n");
    printf("index : value\n");
    for (int i=0 ; i<col->size ; i++){
        printf("%llu : %d\n", col->index[i], *col->data[col->index[i]]);
    }

    insert_value(col, &value5);
    insert_value(col, &value6);
    insert_value(col, &value7);
    insert_value(col, &value8);
    insert_value(col, &value9);
     */
    int a=1, b=5, c=10, d=55, e=26;
    printf("----------------------------\n");
    printf("%d\n", search_value_in_column(col, &a));
    printf("%d\n", search_value_in_column(col, &b));
    printf("%d\n", search_value_in_column(col, &c));
    printf("%d\n", search_value_in_column(col, &d));
    printf("%d\n", search_value_in_column(col, &e));

    insert_value(col, &value5);
    printf("%d\n", search_value_in_column(col, &e));

    sort(col, ASC);
    printf("After sorting :\nprint_col\n");
    print_col_by_index(col);

    printf("Trying to delete an index\n");
    delete_with_index(col, 7);
    delete_with_index(col, 5);
    print_col_by_index(col);
    return 0;
}