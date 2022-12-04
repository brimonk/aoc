#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main(int argc, char **argv)
{
	int lo1, hi1, lo2, hi2;
	int contains = 0;

	while (4 == scanf("%d-%d,%d-%d\n", &lo1, &hi1, &lo2, &hi2)) {
		if (lo1 <= lo2 && hi2 <= hi1) {
			contains++;
			continue;
		}
		if (lo2 <= lo1 && hi1 <= hi2) {
			contains++;
			continue;
		}
	}

	printf("fully contained %d\n", contains);

	return 0;
}
