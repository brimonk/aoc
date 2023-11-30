#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

char trees[1024][32] = {0};
int trees_len = 0;

int count_collisions(int mx, int my)
{
	int px = 0, py = 0;
	int collisions = 0;

	while (py < trees_len) {
		if (trees[py][px] == '#')
			collisions++;
		px = (px + mx) % strlen(trees[py]);
		py += my;
	}

	return collisions;
}

int main(int argc, char **argv)
{
	char buf[1024] = {0};
	int collisions = 0;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		memcpy(&trees[trees_len++], buf, strlen(buf));
	}

	collisions =
		count_collisions(1, 1)
		* count_collisions(3, 1)
		* count_collisions(5, 1)
		* count_collisions(7, 1)
		* count_collisions(1, 2);

	printf("collisions %d\n", collisions);

	return 0;
}
