#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main(int argc, char **argv)
{
	long filebytes = 0;
	long membytes = 0;
	char buf[512];
	char *s;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (s = buf; *s; ) {
			if (isblank(*s))
				continue;

			switch (*s) {
				case '\\': {
					if (s[1] == '\\' || s[1] == '"') {
						filebytes += 2;
						membytes++;
						s += 2;
					} else if (s[1] == 'x') {
						filebytes += 4;
						membytes++;
						s += 4;
					} else {
						assert(0);
					}
					break;
				}

				default:
					filebytes++;
					membytes++;
					s++;
					break;
			}
		}

		membytes -= 2; // every string is double quoted
	}

	printf("file %ld, memory %ld\n", filebytes, membytes);
	printf("answer %ld\n", filebytes - membytes);

	return 0;
}
