#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define ARRSIZE(Q_) (sizeof((Q_))/sizeof((Q_)[0]))

long calories[1024] = { 0 };

int calsort(const void *a, const void *b)
{
	long la = *(long *)a;
	long lb = *(long *)b;
	return lb - la;
}

int main(int argc, char **argv)
{
	long currcals = 0, n;
	int rc, i;
	char buf[1024];

	memset(buf, 0, sizeof buf);

	for (i = 0; i < ARRSIZE(calories); i++)
		calories[i] = LONG_MIN;

	for (i = 0; i < ARRSIZE(calories) && buf == fgets(buf, sizeof buf, stdin);) {
		buf[strlen(buf) - 1] = 0;
		if (strlen(buf) == 0) {
			calories[i++] = currcals;
			currcals = 0;
		} else {
			rc = sscanf(buf, "%ld", &n);
			assert(rc == 1);
			currcals += n;
		}
	}

	qsort(calories, i, sizeof(long), calsort);

	printf("total calories: %ld\n", calories[0] + calories[1] + calories[2]);

	return 0;
}
