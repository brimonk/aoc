#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main(int argc, char **argv)
{
	long filebytes = 0;
	long encodebytes = 0;
	char buf[512];
	char *s;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (s = buf; *s; ) {
			if (isblank(*s))
				continue;

			switch (*s) {
				case '\\':
					filebytes++;
					encodebytes += 2;
					s++;
					break;

				case '"':
					filebytes++;
					encodebytes += 2;
					s++;
					break;

				default:
					filebytes++;
					encodebytes++;
					s++;
					break;
			}
		}

		encodebytes += 2;
	}

	printf("file %ld, encode %ld\n", filebytes, encodebytes);
	printf("answer %ld\n", encodebytes - filebytes);

	return 0;
}
