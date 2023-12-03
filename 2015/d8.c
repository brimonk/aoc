#include "common.h"

void p1()
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

	// printf("file %ld, memory %ld\n", filebytes, membytes);
	printf("p1: %ld\n", filebytes - membytes);
}

void p2()
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

	// printf("file %ld, encode %ld\n", filebytes, encodebytes);
	printf("p2: %ld\n", encodebytes - filebytes);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
