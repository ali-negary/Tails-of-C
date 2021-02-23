#include <stdio.h>

int main()
{
    int const rows = 3;
    int const columns = 4;
    int studentGrades[rows][columns];  // defining and initialization cannot happen in the same step.
    // int studentGrades[rows][columns]={
    //                         {1, 2, 3, 4},
    //                         {2, 3, 4, 5},
    //                         {3, 4, 5, 6}
    //                         };
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", studentGrades[i][j]);
        }
        printf("\n");
    }
    return 0;
}