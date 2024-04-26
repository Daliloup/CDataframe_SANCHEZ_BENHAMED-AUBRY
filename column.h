//
// Created by Yannis on 29/03/2024.
//

#ifndef COLUMN_H
#define COLUMN_H

#define REALLOC_SIZE 256


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
    int valid_index;
    int sort_dir;
};
typedef struct column COLUMN;


int sizeof_coldata_ptr(COLUMN *col);


/**
* Create a new column
* @param1 Column type
* @param2 Column title
* @return Pointer to the created column
*/
COLUMN* create_column(ENUM_TYPE type, char *title);


/**
* @brief Insert a new value into a column
* @param1 Pointer to the column
* @param2 Pointer to the value to insert
* @return 1 if the value is correctly inserted 0 otherwise
*/
int insert_value(COLUMN *col, void *value);


/**
* @brief Free the space allocated by a column
* @param1 Pointer to the column
*/
void delete_column(COLUMN **col);


/**
* @brief Convert a value into a string
* @param1 Pointer to the column
* @param2 Position of the value in the data array
* @param3 The string in which the value will be written
* @param4 Maximum size of the string
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);


/**
* @brief Display the content of a column
* @param Pointer to the column to display
*/
void print_col(COLUMN* col);

/**
 *
 * @param col pointer to the column
 * @param value pointer to the value to count
 * @return The occurrence of the value in the column
 */
int occurrence(COLUMN *col, void *x);


/**
 *
 * @param col pointer to the column
 * @param pos index of an element in the column
 * @return the element pointed by the pointer at index pos in the column
 */
void* value_with_position(COLUMN *col, int pos);


/**
 *
 * @param col pointer to the column
 * @param x pointer to the value to compare
 * @return the number of values greater than x
 */
int greater_than(COLUMN *col, void *x);


/**
 *
 * @param col pointer to the column
 * @param x pointer to the value to compare
 * @return the number of values lower than x
 */
int lower_than(COLUMN *col, void *x);


/**
* @brief Sort a column according to a given order
* @param1 Pointer to the column to sort
* @param2 Sort type (ASC or DESC)
*/
void sort(COLUMN* col, int sort_dir);


/**
* @brief Display the content of a sorted column
* @param1 Pointer to a column
*/
void print_col_by_index(COLUMN *col);


/**
* @brief Remove the index of a column
* @param1 Pointer to the column
*/
void erase_index(COLUMN *col);


/**
* @brief Check if an index is correct
* @param1 Pointer to the column
* @return 0: index not existing,
-1: the index exists but invalid,
1: the index is correct
*/
int check_index(COLUMN *col);


/**
* @brief Update the index
* @param1 Pointer to the column
*/
void update_index(COLUMN *col);


/**
* @brief Check if a value exists in a column
* @param1 Pointer to the column
* @param2 Pointer to the value to search for
* @return -1: column not sorted,
0: value not found
1: value found
*/
int search_value_in_column(COLUMN *col, void *val);


/**
* @brief Replaces a certain value in a column with user input
* @param col Pointer to the column
* @param   i Index of value to be changed
*/
void replace_value_column(COLUMN *col, int i);  // User Input

#endif //COLUMN_H
