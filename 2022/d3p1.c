#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int pocket1[26 * 2] = {0};
int pocket2[26 * 2] = {0};

int getidx(int item)
{
	if ('a' <= item && item <= 'z')
		return item - 'a';
	else
		return item - 'A' + 26; // ?
}

int getpoints(int idx)
{
	return idx + 1;
}

int main(int argc, char **argv)
{
	char buf[1024] = {0};
	int sum = 0;
	int mid;
	int len;
	int i;

	assert(sizeof(pocket1) == sizeof(pocket2));

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		len = strlen(buf);
		mid = len / 2;

		assert(len % 2 == 0);

		memset(pocket1, 0, sizeof pocket1);
		memset(pocket2, 0, sizeof pocket2);

		for (i = 0; i < mid; i++)
			pocket1[getidx(buf[i])]++;
		for (; i < len; i++)
			pocket2[getidx(buf[i])]++;

		int currsum = 0;

		for (i = 0; i < (sizeof(pocket1)/sizeof(pocket1[0])); i++)
			if (pocket1[i] != 0 && pocket2[i] != 0)
				currsum += getpoints(i);

		assert(currsum < getpoints('Z'));

		sum += currsum;
	}

	printf("sum %d\n", sum);

	return 0;
}
