#include "common.h"

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

void p1()
{
	int nicestrs = 0;
	char buf[512];

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		if (isnice(buf))
			nicestrs++;
	}

	printf("p1: %d\n", nicestrs);

	return 0;
}

int isnice2(char *s)
{
	int firstcase = 0;
	int secondcase = 0;
	int len = strlen(s);

	// first case
	for (int i = 0; i < len; i++) {
		for (int j = i + 2; j < len; j++) {
			if (s[i + 0] == s[j + 0] && s[i + 1] == s[j + 1]) {
				firstcase = 1;
				goto escape;
			}
		}
	}

	escape:

	// second case
	for (int i = 0; i < len - 1; i++) {
		if (s[i] == s[i + 2]) {
			secondcase = 1;
			break;
		}
	}

	return firstcase && secondcase;
}

void p2()
{
	int nicestrs = 0;
	char buf[512];

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		if (isnice2(buf))
			nicestrs++;
	}

	printf("p2: %d\n", nicestrs);

	return 0;
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
