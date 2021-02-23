#include <stdio.h>

int main(){

    printf("Unary minus:\n");
    int a = 5;

    int b = -a;
    printf("b = %d\n", b);
    printf("a = %d\n", a); // A doesn't change

    printf("post increment:\n");
    a = 5;
    b = 5;
    b = a++; 
    printf("b = %d\n", b); //b gets assigned to first
    printf("a = %d\n", a); //Then A is incremented

    b = 5;
    a = 5; //start fresh
    b = ++a;

    printf("Pre increment:\n");
    printf("b = %d\n", b); //B gets assigned to second
    printf("a = %d\n", a); //A is incremented first

    return 0;
}