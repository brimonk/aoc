#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

int isvalid(int c, int lo, int hi, char *s)
{
	int times = 0;
	for (; *s; s++)
		if (*s == c)
			times++;

	return lo <= times && times <= hi;
}

int main(int argc, char **argv)
{
	char buf[1024] = {0};
	char *tokens[32] = {0};
	int valid = 0;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		int i;
		char *s;
		for (i = 0, s = strtok(buf, "-: "); s; i++, s = strtok(NULL, "-: "))
			tokens[i] = s;
		tokens[i] = s;

		if (isvalid(tokens[2][0], atoi(tokens[0]), atoi(tokens[1]), tokens[3]))
			valid++;
	}

	printf("valid %d\n", valid);

	return 0;
}
