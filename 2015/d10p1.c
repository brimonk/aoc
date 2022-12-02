#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define PUZZLEINPUT 1113222113
#define BUFSIZE (1 << 20)

int countrun(char *s)
{
	int i;
	for (i = 0; s[i] && s[0] == s[i]; i++)
		;
	return i;
}

int main(int argc, char **argv)
{
	char *bbuf = calloc(1, BUFSIZE);
	char *fbuf = calloc(1, BUFSIZE);
	int i;
	char *s, *t;

#ifndef PUZZLEINPUT
	fgets(bbuf, BUFSIZE, stdin);
	bbuf[strlen(bbuf) - 1] = 0;
#else
	snprintf(bbuf, BUFSIZE, "%d", PUZZLEINPUT);
#endif

#ifdef PUZZLEINPUT
	for (i = 0; i < 40; i++) {
#endif
		s = bbuf;
		t = fbuf;
		while (*s) {
			int runlen = countrun(s);
			t += snprintf(t, BUFSIZE - (t - fbuf), "%d%d", runlen, *s - '0');
			s += runlen;
			assert(t - fbuf < BUFSIZE);
		}
		printf("%d %ld %s\n", i, strlen(fbuf), fbuf);
		memcpy(bbuf, fbuf, BUFSIZE);
#if PUZZLEINPUT
	}
#endif

	printf("result %s\n", bbuf);
	printf("result len %ld\n", strlen(bbuf));

	free(bbuf);
	free(fbuf);

	return 0;
}
