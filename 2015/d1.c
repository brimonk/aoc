#include "common.h"

void p1()
{
	int c;
	int floor = 0;
	while ((c = getchar()) != EOF) {
		if (c == '(')
			floor++;
		else if (c == ')')
			floor--;
	}
	printf("p1: %d\n", floor);
}

void p2()
{
	int c, i;
	int floor = 1;
	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c == '(')
			floor++;
		else if (c == ')')
			floor--;
		if (floor < 0)
			break;
	}
	printf("p2: %d\n", i);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
