#include <stdio.h>
#include <string.h>


struct rectangle        // this is one way to define a struct.
{
    int length;
    int width;
};

typedef struct position // this is the other way. name "position" here is optional.
{
    int x;
    int y;
} position; //determines data type name

typedef struct buildingPlan // this is a struct of structs
{
    //a struct to define the owner, size, and position of a house
    char owner[30];
    position position; // type being same as identifier is ok
    struct rectangle rectangle; //could remove struct keyword if used typedef
    //but will leave for demenstration
} buildingPlan;

typedef struct
{
    int *a;
    int *b;
} pointers;

void logPosition(position pos)
{
    printf("Log - position: %d %d\n", pos.x, pos.y);
}

buildingPlan createPlan(char name[30], int length, int width, int x, int y)
{

    buildingPlan plan = {"", length, width, x, y};
    strcpy(plan.owner, name);
    return plan;
}


int main()
{
    struct rectangle house = {10, 20}; //non-standard initialization (compared to primitive types)
    position destination = {0,22}; // standard initialization (type identifier = value)

    house.length = 50; //can change values using dot operator
    destination.x = 70;
    printf("destination: %d %d\n", destination.x, destination.y);
    printf("+++++++++++++++++++++\n");

    buildingPlan myHouse = {"Ali Negary", {355235.1, 4738631.3}, {50, 70}};
    // myHouse.position.x = 30; //Now you can traverse structure using dot operator

    printf("The house at %d %d (size %d %d) is owned by %s\n", 
            myHouse.position.x, 
            myHouse.position.y,
            myHouse.rectangle.length,
            myHouse.rectangle.width,
            myHouse.owner);
    printf("+++++++++++++++++++++\n");
    //You can make arrays of the new data types:

    static int size = 4;
    position path[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};

    for (int i = 0; i < size; i++)
    {   
        if(i == 0)
        {
            printf("From ");
        } else
        {
            printf(" to ");
        }
        printf("(%d %d)", path[i].x, path[i].y);
    }
    printf(".\n");

    //You can pass structs to functions
    logPosition(destination);

    //You can return structs from functions
    buildingPlan myPlan = createPlan("Ali Negary", 10, 10, 30, 30);

    printf("The house at %d %d (size %d %d) is owned by %s\n", 
            myPlan.position.x, 
            myPlan.position.y,
            myPlan.rectangle.length,
            myPlan.rectangle.width,
            myPlan.owner);

    //You can have structs that contain pointers
    printf("+++++++++++++++++++++\n");

    int w = 10;
    int z = 10;
    pointers myPointers = { .a = &w, .b = &z }; // equals ==> pointers myPointers = { &w, &z };

    
    *(myPointers.a) = 9001; // equals ==> *myPointers.a = 9001;
    
    printf("value at destination of myPointers.a: %d\n", *myPointers.a);

    //And you can make pointers to structs
    printf("+++++++++++++++++++++\n");

    buildingPlan *pointerToStruct = &myPlan;
    printf("The owner is %s\n", pointerToStruct->owner); //arrow operator to navigate struct pointer
    // printf("The owner is %s\n", (*pointerToStruct).owner); // this line equals line 113.
    return 0;
}