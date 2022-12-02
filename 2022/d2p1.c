#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

// converts shape to points
int getpoints(int c)
{
	if ('A' <= c && c <= 'C')
		return 1 + c - 'A';
	if ('X' <= c && c <= 'Z')
		return 1 + c - 'X';
	return 0;
}

// return the point value from the outcome of this game
int outcome(int p1, int p2)
{
	int s1 = getpoints(p1);
	int s2 = getpoints(p2);
	if (s1 == s2)
		return 3;
	if (s1 == 1) {
		if (s2 == 2)
			return 6;
	} else if (s1 == 2) {
		if (s2 == 3)
			return 6;
	} else if (s1 == 3) {
		if (s2 == 1)
			return 6;
	}
	return 0;
}

int main(int argc, char **argv)
{
	char buf[1024];
	char *p1, *p2;
	int score = 0;

	memset(buf, 0, sizeof buf);

	p1 = &buf[0]; // input is very carefully crafted here
	p2 = &buf[2];

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		score += getpoints(*p2) + outcome(*p1, *p2);
#if 0
		printf("%c %c %d %d %d\n",
			(char)*p1, (char)*p2, getpoints(*p2), outcome(*p1, *p2), score
		);
#endif
	}

	printf("score %d\n", score);

	return 0;
}
