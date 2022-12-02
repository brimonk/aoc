#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
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
	printf("position %d\n", i);
	return 0;
}
