#include "common.h"

int chkpass(char *s)
{
	assert(s != NULL);
	assert(strlen(s) == 8); // ?

	int i, len;
	int straight = 0;
	int pairs = 0;
	int lastpair = -2;

	for (i = 0, len = strlen(s); i < len; i++) {
		if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l')
			return 0;
		if (i - 2 < len) {
			if (s[i + 0] + 1 == s[i + 1] && s[i + 1] + 1 == s[i + 2])
				straight++;
		}
		if (i - 2 < len && i - lastpair >= 2) {
			if (s[i + 0] == s[i + 1]) {
				lastpair = i;
				pairs++;
			}
		}
	}

#if 0
	if (straight >= 1 || pairs >= 2)
		printf("%s%s%s\n",
			straight >= 1 ? "straight" : "",
			straight >= 1 ? " " : "",
			pairs >= 2 ? "pairs" : ""
		);
#endif

	return straight >= 1 && pairs >= 2;
}

void rectify(char *s)
{
	for (int i = strlen(s) - 1; 0 <= i && 'z' < s[i]; i--) {
		s[i] = 'a';
		if (0 < i)
			s[i - 1]++;
	}
}

int bigskip(char *s)
{
	// skip all i's, o's, and l's
	int didbig = 0;
	char *t;
	for (t = s + strlen(s) - 1; s <= t; t--) {
		if (*t == 'i' || *t == 'o' || *t == 'l') {
			didbig = 1;
			(*t)++;
		}
	}
	if (didbig)
		rectify(s);
	return didbig;
}

void nextpass(char *s)
{
	if (bigskip(s))
		return;
	s[strlen(s) - 1]++;
	rectify(s);
}

void p1()
{
	char buf[1024] = {0};
	char *s;

	fgets(buf, sizeof buf, stdin);
	buf[strlen(buf) - 1] = 0;

	s = buf;

	for (s = buf; !chkpass(s); nextpass(s))
		;

	printf("p1: %s\n", s);
}

void p2()
{
	char buf[1024] = {0};
	char *s;

	fgets(buf, sizeof buf, stdin);
	buf[strlen(buf) - 1] = 0;

	for (s = buf, nextpass(buf); !chkpass(s); nextpass(s))
		;
	for (s = buf, nextpass(buf); !chkpass(s); nextpass(s))
		;

	printf("p2: %s\n", s);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
