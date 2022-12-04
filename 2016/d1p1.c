#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main(int argc, char **argv)
{
	char buf[2048] = {0};
	char *s;
	char dir;
	int amt;

	fgets(buf, sizeof buf, stdin);
	buf[strlen(buf) - 1] = 0;

	for (s = strtok(buf, " ,"); s; s = strtok(NULL, " ,")) {
		sscanf(s, "%c%d", &dir, &amt);
	}

	return 0;
}
