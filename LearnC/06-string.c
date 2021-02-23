#include <stdio.h>
#include <string.h>

int main()
{
    char firstname[20];
    char lastname[20] = "Negary";
    printf(" Please enter your firstname: \n");
    scanf("%19s", firstname);
    printf("Hi %s! you name has %lu characters ", firstname, strlen(firstname));
    char name[20]; // to copy a string in another string...
    strcpy(name, firstname);
    printf("You name was copied in the system: %s \n", name);
    // strcmp returns 0 on matching strings. to ignore case sensetivity use strcasecmp.
    if (strcasecmp(name, "Ali") == 0)
    {
        printf("Ver well. Your last name must be Negary. Correct?\n");
        char answer[3];
        scanf("%3s", answer);
        if (strcasecmp(answer, "yes") == 0)
        {
            strcat(name, lastname);
            printf("Welcome Mr. %s!\n", name);
        }
    }
    else
    {
        printf("Sorry! But I cannot find your name in the list.\n");
    }

    return 0;
}