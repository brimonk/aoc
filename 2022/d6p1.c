#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void swap(char *a, char *b)
{
	char c = *b;
	*b = *a;
	*a = c;
}

int checkchars(int chars[4])
{
	return chars[0] != chars[1]
		&& chars[0] != chars[2]
		&& chars[0] != chars[3]
		&& chars[1] != chars[2]
		&& chars[1] != chars[3]
		&& chars[2] != chars[3];
}

int main(int argc, char **argv)
{
	int chars[4] = {0};
	int curr = 0;
	int i;

	for (i = 0; (curr = fgetc(stdin)) != EOF; i++) {
		if (isblank(curr))
			continue;
		chars[i % 4] = curr;
		if (i >= 4 && checkchars(chars))
			break;
	}

	printf("position %d\n", i + 1);

	return 0;
}
