#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define TARGET_LITERS 150

int containers[TARGET_LITERS];
int containers_len = 0;

int combinations = 0;

void checkcombo(int start)
{
	for (int i = start; i < containers_len; i++) 
		;
}

void recurse(int target, int curr, int start)
{
}

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[32];
	int i;
	char *s;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " :,"); s; i++, s = strtok(NULL, " :,"))
			tokens[i] = s;
		tokens[i] = s;
	}

	return 0;
}
