#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define CHARACTERS 14

int checkchars(int *chars)
{
	for (int i = 0; i < CHARACTERS; i++) {
		for (int j = 0; j < CHARACTERS; j++) {
			if (i != j && chars[i] == chars[j])
				return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	int chars[CHARACTERS] = {0};
	int curr = 0;
	int i;

	for (i = 0; (curr = fgetc(stdin)) != EOF; i++) {
		if (isblank(curr))
			continue;
		chars[i % CHARACTERS] = curr;
		if (i >= CHARACTERS && checkchars(chars))
			break;
	}

	printf("position %d\n", i + 1);

	return 0;
}
