#include <stdio.h>
int main(int argc, char **argv)
{
	int lo1, hi1, lo2, hi2, c = 0;
	while (4 == scanf("%d-%d,%d-%d\n", &lo1, &hi1, &lo2, &hi2)) {
		if (lo1 <= lo2 && lo2 <= hi1) { c++; continue; }
		if (lo2 <= lo1 && lo1 <= hi2) { c++; continue; }
		if (lo1 <= hi2 && hi2 <= hi1) { c++; continue; }
		if (lo2 <= hi1 && hi1 <= hi2) { c++; continue; }
	}
	printf("fully contained %d\n", c);
	return 0;
}
