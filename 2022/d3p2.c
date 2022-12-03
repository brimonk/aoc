#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define ITEMTYPES (26 * 2)

int rucksack[3][ITEMTYPES] = {0};

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
	int len;
	int i;
	int j;

	for (j = 0; buf == fgets(buf, sizeof buf, stdin); j++) {
		buf[strlen(buf) - 1] = 0;

		len = strlen(buf);

		assert(len % 2 == 0);

		if (j % 3 == 0) {
			memset(rucksack, 0, sizeof rucksack);
		}

		for (i = 0; i < len; i++)
			rucksack[j % 3][getidx(buf[i])]++;

		if (j > 0 && j % 3 == 2)
			for (i = 0; i < ITEMTYPES; i++)
				if (rucksack[0][i] && rucksack[1][i] && rucksack[2][i])
					sum += getpoints(i);
	}

	printf("sum %d\n", sum);

	return 0;
}
