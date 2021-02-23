#include <stdio.h>

int main()
{
    // forloop();
    // whileloop();
    dowhileloop();
}

int forloop()
{
    // steps are intialize , compare , update.
    int stocks[] = {2, 570, 91, 84, 63};
    int calculated_size = sizeof(stocks) / sizeof(stocks[0]);
    for (int i = 0; i < calculated_size; i++)
    {
        // printf("%d ", i);
        printf("%d\n",stocks[i]);
    }
    return 0;
}

int whileloop()
{
    int i = 0;
    while(i<5)
    {
        printf("%d ", i);
        i++;
    }
    return 0;
}

int dowhileloop()
{
    int input_number;
    do
    {
        printf("Choose a number between 1 and 9: ");
        scanf("%d", &input_number);
    } while (input_number < 0 || input_number > 9);
    return 0;
}