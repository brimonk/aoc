#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int isnice(char *s)
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
