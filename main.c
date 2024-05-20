//
// Created by sanch on 26/04/2024.
//

#include "column.h"
#include "cdataframe.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int user_input;
    int dataframe_selected = 0;
    int running_menu = 1;
    int i, j;

    // Temporarily these values will be integers and have the value 0
    // (Not figured out how to get user input on unknown data from here yet,
    //  might have to implement new functions in column.h)
    int value = 0, new_value = 0;

    //char filename[20];

    CDATAFRAME *cdf;

    while (running_menu) {
        while (!(dataframe_selected) && running_menu) {
            printf("0. Exit\n");
            printf("1. Create New Dataframe\n");
            //printf("2. Load Dataframe From File\n");
            scanf("%d", &user_input);

            switch (user_input) {
                case 0: {
                    running_menu = 0;
                    break;
                }
                case 1: {
                    cdf = create_cdataframe();
                    fill_cdataframe(cdf);
                    dataframe_selected = 1;
                    break;
                }
                /*
                case 2:
                    printf("\nFilename: ");
                    gets(filename);
                    cdf = load_from_csv(filename);
                    dataframe_selected = 1;
                    break;
                */
                default:
                    printf("\nIncorrect Action\n\n");
            }
        }

        while (dataframe_selected && running_menu) {
            printf("\n\n");
            printf("0. Exit\n");
            printf("1. Display Dataframe\n");
            printf("2. Display Dataframe Size\n");
            printf("3. Add Column\n");
            printf("4. Add Row\n");
            printf("5. Display Value\n");
            printf("6. Set Value\n");
            printf("7. Display Column Titles\n");
            printf("8. Rename Column\n");
            printf("9. Display Occurrences of Value\n");
            printf("10. Display Less than Value\n");
            printf("11. Display Greater than Value\n");
            printf("12. Sort the DataFrame with respect to one column\n");
            //printf("12. Save Dataframe\n");
            //printf("13. Exit Current Dataframe (Will not save changes)\n");

            scanf("%d", &user_input);

            switch (user_input) {
                case 0: {
                    delete_cdataframe(&cdf);
                    running_menu = 0;
                    dataframe_selected = 0;
                    break;
                }
                case 1: {
                    display_cdataframe(cdf);
                    break;
                }
                case 2: {
                    printf("%d columns", get_cdataframe_cols_size(cdf));
                    printf(", %d rows\n", get_nb_rows(cdf));
                    break;
                }
                case 3: {
                    add_column_user(cdf);
                    break;
                }
                case 4: {
                    add_row_user(cdf);
                    break;
                }
                case 5: {
                    printf("Row Index: ");
                    scanf_s("%d", &i);
                    printf("Column Index: ");
                    scanf_s("%d", &j);
                    get_value_cdataframe(cdf, j, i);
                    break;
                }
                case 6: {
                    printf("Column Index: ");
                    scanf_s("%d", &j);
                    printf("Row Index: ");
                    scanf_s("%d", &i);
                    set_new_value_cdataframe(cdf, i, j);
                    break;
                }
                case 7: {
                    display_col_names(cdf);
                    break;
                }
                case 8: {
                    char* title = (char*) malloc(20 * sizeof(char));
                    char* new_title = (char*) malloc(20 * sizeof(char));
                    printf("Title of Column: ");
                    scanf("%19s", title);

                    printf("\n");

                    printf("New Title: ");
                    scanf("%19s", new_title);

                    rename_col_cdataframe(cdf, title, new_title);
                    free(title);
                    free(new_title);
                    break;
                }
                case 9: {
                    printf("\nSearch for the number of values equal to x in the CDF\n");
                    printf("[1.NULLVALUE, ");
                    printf("2.U_INT, ");
                    printf("3.INT, ");
                    printf("4.CHAR, ");
                    printf("5.FLOAT, ");
                    printf("6.DOUBLE, ");
                    printf("7.STRING]");
                    printf("\nType of the value : ");
                    int type;
                    scanf(" %d", &type);
                    printf("\n");
                    switch (type) {
                        case UINT:
                        {
                            unsigned long long int *value = (unsigned long long int*) malloc(sizeof(unsigned long long int));
                            printf("Enter value (uint): ");
                            scanf(" %llu", value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                        case INT: {
                            int *value = (int*) malloc(sizeof(int));
                            printf("Enter value (int): ");
                            scanf(" %d", value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                        case CHAR: {
                            char *value = (char*) malloc(sizeof(char));
                            printf("Enter value (char): ");
                            scanf(" %c", value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                        case FLOAT: {
                            float *value = (float*) malloc(sizeof(float));
                            printf("Enter value (float): ");
                            scanf(" %f", value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                        case DOUBLE: {
                            double *value = (double*) malloc(sizeof(double));
                            printf("Enter value (double): ");
                            scanf(" %lf", value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                        case STRING: {
                            char *value = (char*) malloc(20*sizeof(char));
                            printf("Enter value (string): ");
                            fflush(stdin);
                            gets(value);
                            printf("\n");
                            display_nb_equal_cdataframe(cdf, value, type);
                            break;
                        }
                    }
                    printf("---------------------------------------------------");
                    break;
                }
                case 10: {
                    printf("\nSearch for the number of values greater than x in the CDF\n");
                    printf("[1.NULLVALUE, ");
                    printf("2.U_INT, ");
                    printf("3.INT, ");
                    printf("4.CHAR, ");
                    printf("5.FLOAT, ");
                    printf("6.DOUBLE, ");
                    printf("7.STRING]");
                    printf("\nType of the value : ");
                    int type;
                    scanf(" %d", &type);
                    switch (type) {
                        case UINT: {
                            unsigned long long int *value = (unsigned long long int *) malloc(sizeof(unsigned long long int));
                            printf("\nEnter value (uint): ");
                            scanf(" %llu", value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                        case INT: {
                            int *value = (int *) malloc(sizeof(int));
                            printf("\nEnter value (int): ");
                            scanf(" %d", value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                        case CHAR: {
                            char *value = (char *) malloc(sizeof(char));
                            printf("\nEnter value (char): ");
                            scanf(" %c", value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                        case FLOAT: {
                            float *value = (float *) malloc(sizeof(float));
                            printf("\nEnter value (float): ");
                            scanf(" %f", value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                        case DOUBLE: {
                            double *value = (double *) malloc(sizeof(double));
                            printf("\nEnter value (double): ");
                            scanf(" %lf", value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                        case STRING: {
                            char *value = (char *) malloc(20 * sizeof(char));
                            printf("\nEnter value (string): ");
                            fflush(stdin);
                            gets(value);
                            display_nb_greater_cdataframe(cdf, value, type);
                            break;
                        }
                    }
                    break;
                }
                case 11: {
                    printf("\nSearch for the number of values lower than x in the CDF\n");
                    printf("[1.NULLVALUE, ");
                    printf("2.U_INT, ");
                    printf("3.INT, ");
                    printf("4.CHAR, ");
                    printf("5.FLOAT, ");
                    printf("6.DOUBLE, ");
                    printf("7.STRING]");
                    printf("\nType of the value : ");
                    int type;
                    scanf(" %d", &type);
                    switch (type) {
                        case UINT:
                        {
                            unsigned long long int *value = (unsigned long long int*) malloc(sizeof(unsigned long long int));
                            printf("\nEnter value (uint): ");
                            scanf(" %llu", value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                        case INT: {
                            int *value = (int*) malloc(sizeof(int));
                            printf("\nEnter value (int): ");
                            scanf(" %d", value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                        case CHAR: {
                            char *value = (char*) malloc(sizeof(char));
                            printf("\nEnter value (char): ");
                            scanf(" %c", value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                        case FLOAT: {
                            float *value = (float*) malloc(sizeof(float));
                            printf("\nEnter value (float): ");
                            scanf(" %f", value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                        case DOUBLE: {
                            double *value = (double*) malloc(sizeof(double));
                            printf("\nEnter value (double): ");
                            scanf(" %lf", value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                        case STRING: {
                            char *value = (char*) malloc(20*sizeof(char));
                            printf("\nEnter value (string): ");
                            fflush(stdin);
                            gets(value);
                            display_nb_less_cdataframe(cdf, value, type);
                            break;
                        }
                    }
                    break;
                }
                /*
                case 12:
                    printf("Enter Filename (<name>.csv):");
                    gets(filename);
                    save_into_csv(cdf, filename);
                    break;
                case 13:
                    delete_cdataframe(&cdf);
                    dataframe_selected = 0;
                */
                case 12:{
                    char* title = (char*) malloc(20 * sizeof(char));
                    printf("Title of column to sort: ");
                    scanf("%19s", title);
                    printf("\n");
                    int dir;
                    printf("Ascending order : 0\nDescending order : 1\nIn which order : ");
                    scanf("%d", &dir);
                    sort_dataframe_column(cdf, title, dir);
                }
                default:
                    printf("Incorrect Action");
            }
        }
    }

    if (dataframe_selected) {
        delete_cdataframe(&cdf);
    }
    return 0;
}