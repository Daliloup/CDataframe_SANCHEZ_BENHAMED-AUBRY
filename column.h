//
// Created by Yannis on 29/03/2024.
//

#ifndef CDATAFRAME_SANCHEZ_BENHAMED_AUBRY_COLUMN_H
#define CDATAFRAME_SANCHEZ_BENHAMED_AUBRY_COLUMN_H


enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;


union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;


struct column {
    char *title;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;


#endif //CDATAFRAME_SANCHEZ_BENHAMED_AUBRY_COLUMN_H
