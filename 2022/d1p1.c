#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main(int argc, char **argv)
{
	long maxcals = LONG_MIN;
	long currcals = 0, n;
	int rc;
	char buf[1024];
	char *s;

	memset(buf, 0, sizeof buf);

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		if (strlen(buf) == 0) {
			if (maxcals < currcals)
				maxcals = currcals;
			currcals = 0;
		} else {
			rc = sscanf(buf, "%ld", &n);
			assert(rc == 1);
			currcals += n;
		}
	}

	printf("%ld\n", maxcals);

	return 0;
}
