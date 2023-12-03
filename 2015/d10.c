#include "common.h"

// #define PUZZLEINPUT 1113222113
#define BUFSIZE (1 << 30)

int countrun(char *s)
{
	int i;
	for (i = 0; s[i] && s[0] == s[i]; i++)
		;
	return i;
}

void p1()
{
	char *bbuf = calloc(1, BUFSIZE);
	char *fbuf = calloc(1, BUFSIZE);
	char *s, *t;
    int i;

	fgets(bbuf, BUFSIZE, stdin);
	bbuf[strlen(bbuf) - 1] = 0;

	for (i = 0; i < 40; i++) {
		s = bbuf;
		t = fbuf;
		while (*s) {
			int runlen = countrun(s);
			t += snprintf(t, BUFSIZE - (t - fbuf), "%d%d", runlen, *s - '0');
			s += runlen;
			assert(t - fbuf < BUFSIZE);
		}
		// fprintf(stderr, "%ld %s\n", strlen(fbuf), fbuf);
		memcpy(bbuf, fbuf, BUFSIZE);
	}

	printf("p1: %ld\n", strlen(bbuf));

	free(bbuf);
	free(fbuf);
}

void p2()
{
	char *bbuf = calloc(1, BUFSIZE);
	char *fbuf = calloc(1, BUFSIZE);
    int i;
	char *s, *t;

	fgets(bbuf, BUFSIZE, stdin);
	bbuf[strlen(bbuf) - 1] = 0;

	for (i = 0; i < 50; i++) {
		s = bbuf;
		t = fbuf;
		while (*s) {
			int runlen = countrun(s);
			t += snprintf(t, BUFSIZE - (t - fbuf), "%d%d", runlen, *s - '0');
			s += runlen;
			assert(t - fbuf < BUFSIZE);
		}
		memcpy(bbuf, fbuf, BUFSIZE);
	}

	printf("p2: %ld\n", strlen(bbuf));

	free(bbuf);
	free(fbuf);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
