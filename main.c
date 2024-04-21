#include <stdio.h>
#include "column.c"


int main()
{
    COLUMN *mycol = create_column(CHAR, "My Column");
    printf("%s", mycol->title);
    printf("\n%d", mycol->max_size);
    printf("\n%d", mycol->size);
    printf("\n%d", mycol->column_type);
    printf("\n%llu", sizeof(COLUMN));
    printf("\n%llu", sizeof(mycol));
    char a = 'A', c = 'C';
    int test = insert_value(mycol, &a);
    printf("\n%d", test);
    printf("\n%c", *(mycol->data[0]));
    return 0;
}