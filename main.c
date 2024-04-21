#include <stdio.h>
#include "cdataframe.h"
#include "column.h"


// Comment
//  The Menu system is beginning to take a lot of space and to be less readable
//  We will surely have to find a way to make it more compact in the future.
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

    char title[20], new_title[20];
    char filename[20];

    CDATAFRAME *cdf;

    while (running_menu) {
        while (!(dataframe_selected) && running_menu) {
            printf("0. Exit\n");
            printf("1. Create New Dataframe\n");
            printf("2. Load Dataframe From File\n");
            scanf_s("%d", &user_input);

            switch (user_input) {
                case 0: running_menu = 0; break;
                case 1:
                    cdf = create_cdataframe();
                    fill_cdataframe(cdf);
                    dataframe_selected = 1;
                    break;
                case 2:
                    printf("\nFilename: ");
                    gets(filename);
                    cdf = load_from_csv(filename);
                    dataframe_selected = 1;
                    break;
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
            printf("10. Display Greater than Value\n");
            printf("11. Display Less than Value\n");
            printf("12. Save Dataframe\n");
            printf("13. Exit Current Dataframe (Will not save changes)\n");

            scanf_s("%d", &user_input);

            switch (user_input) {
                case 0:
                    delete_cdataframe(&cdf);
                    running_menu = 0;
                    dataframe_selected = 0;
                    break;
                case 1: display_partial_cdataframe(cdf); break;
                case 2:
                    printf("(");
                    display_nb_columns(cdf);
                    printf(", ");
                    display_nb_rows(cdf);
                    printf(")");
                    break;
                case 3: add_column_user(cdf);         break;
                case 4: add_row_user(cdf);            break;
                case 5:
                    printf("Column Index: "); scanf_s("%d", &i);
                    printf("Row Index: ");    scanf_s("%d", &j);
                    get_value_cdataframe(cdf, i, j);
                    break;
                case 6:
                    printf("Column Index: "); scanf_s("%d", &i);
                    printf("Row Index: ");    scanf_s("%d", &j);
                    set_new_value_cdataframe(cdf, i, j);
                    break;
                case 7: display_col_names(cdf);       break;
                case 8:
                    printf("Title of Column: "); gets(title);
                    printf("New Title: ");       gets(new_title);
                    rename_col_cdataframe(cdf, title, new_title);
                    break;
                case 9:
                    printf("Enter Value:");
                    // scanf_s("%d", value);
                    display_nb_equal_cdataframe(cdf, &value);
                    break;
                case 10:
                    printf("Enter Value:");
                    // scanf_s("%d", value);
                    display_nb_greater_cdataframe(cdf, &value);
                    break;
                case 11:
                    printf("Enter Value:");
                    // scanf_s("%d", value);
                    display_nb_less_cdataframe(cdf, &value);
                    break;
                case 12:
                    printf("Enter Filename (<name>.csv):");
                    gets(filename);
                    save_into_csv(cdf, filename);
                    break;
                case 13:
                    delete_cdataframe(&cdf);
                    dataframe_selected = 0;
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