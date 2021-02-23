#include <stdio.h>

int main(){
	int x = 5;
	int y;
	y = 10;
	printf("it's gonna cost %d million Tomans\n", x + y);
	printf("%s, I don't think so.\n", "Really?");
	printf("How much do you think it is?\n");
	int value;
	scanf("%d", &value);
	if (value > 15){
		printf("I think it will cost more, maybe around %d million Tomans.\n",value);
	}
	if (value < 15){
		printf("That's too much. my guess is around %d million Tomans.\n",value);
	}
	if (value == 15){
		printf("Yeah, I think 15 is enough.\n");
	}
	printf("What was your name again?\n");
	char fname[20], lname[20]; // you cannot use all 20 spaces. only 19 characters.
	scanf("%19s %19s", fname, lname);
	printf("My name is %s %s, sir.\n", fname, lname);
	return 0;
}
