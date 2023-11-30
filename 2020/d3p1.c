#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

char trees[1024][32] = {0};
int trees_len = 0;

int main(int argc, char **argv)
{
	char buf[1024] = {0};
	int collisions = 0;
	int px, py;
	int mx, my;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		memcpy(&trees[trees_len++], buf, strlen(buf));
	}

	px = 0;
	py = 0;

	mx = 3;
	my = 1;

	while (py < trees_len) {
		if (trees[py][px] == '#')
			collisions++;
		px = (px + mx) % strlen(trees[py]);
		py += my;
	}

	printf("collisions %d\n", collisions);

	return 0;
}
