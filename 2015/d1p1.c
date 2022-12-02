#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
{
	int c;
	int floor = 0;
	while ((c = getchar()) != EOF) {
		if (c == '(')
			floor++;
		else if (c == ')')
			floor--;
	}
	printf("floor %d\n", floor);
	return 0;
}
