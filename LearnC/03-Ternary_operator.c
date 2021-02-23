#include <stdio.h>
#include <stdbool.h>

int main()
{
    /////////////   Conditional Operator (ternary operator)  /////////////
   
    double balance = -5000;
    
    balance > 0 ? printf("You have money\n") : printf("You have no money\n");

    //can also use ternary operator for more general things (like assignment) 
    //Basically returns one value if true. other if false.
    bool hasMoney;
    hasMoney = balance > 0 ? 1 : 0;

    printf("HasMoney? 1 is yes 0 is no: %d\n", hasMoney);
}