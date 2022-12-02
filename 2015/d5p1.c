#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int isvowel(char c)
{
	if (c == 'a') return 1;
	if (c == 'e') return 1;
	if (c == 'i') return 1;
	if (c == 'o') return 1;
	if (c == 'u') return 1;
	return 0;
}

int isnice(char *s)
{
	int vowels = 0;
	int hasdouble = 0;
	int len = strlen(s);

	for (int i = 0; i < len; i++) {
		if (isvowel(s[i]))
			vowels++;

		if (i == len - 1) // bounds
			continue;

		if (s[i] == s[i + 1])
			hasdouble = 1;

		// handle the naughty strings
		if (strncmp(s + i, "ab", 2) == 0)
			return 0;
		if (strncmp(s + i, "cd", 2) == 0)
			return 0;
		if (strncmp(s + i, "pq", 2) == 0)
			return 0;
		if (strncmp(s + i, "xy", 2) == 0)
			return 0;
	}

	return vowels >= 3 && hasdouble;
}

int main(int argc, char **argv)
{
	int nicestrs = 0;
	char buf[512];

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		if (isnice(buf))
			nicestrs++;
	}

	printf("nice strings %d\n", nicestrs);

	return 0;
}
