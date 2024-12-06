#include "common.h"

#define BETWEEN(x, min, max)  ((min) <= (x) && (x) < (max))

enum {
	DIR_N,
	DIR_E,
	DIR_S,
	DIR_W,
	DIR_TOTAL
};

struct {
	int x, y;
} dirs[] = {
	{  0, -1 },
	{  1,  0 },
	{  0,  1 },
	{ -1,  0 },
};

char DIRS_CHAR[] = { '^', '>', 'v', '<' };

void p1()
{
	i32 dir = DIR_N;
	i32 x = 0, y = 0;

    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines) && x == 0 && y == 0; i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '^') {
				y = i;
				x = j;
				dir = DIR_N;
			}
		}
	}

	while (BETWEEN(x, 0, strlen(lines[0])) && BETWEEN(y, 0, arrlen(lines))) {
		lines[y][x] = 'X';

		i32 nx = 0, ny = 0;

		switch (dir) {
			case DIR_N:
				nx = x;
				ny = y - 1;
				break;
			case DIR_E:
				nx = x + 1;
				ny = y;
				break;
			case DIR_S:
				nx = x;
				ny = y + 1;
				break;
			case DIR_W:
				nx = x - 1;
				ny = y;
				break;
		}

		if (!(BETWEEN(nx, 0, strlen(lines[0])) && BETWEEN(ny, 0, arrlen(lines)))) { // left the map
			break;
		}

		if (lines[ny][nx] == '#') {
			dir = (dir + 1) % DIR_TOTAL;
		} else {
			x = nx;
			y = ny;
		}
	}

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == 'X')
				ans++;
		}
	}

    printf("p1: %ld\n", ans);
}


int this_map_loops(char **lines, int x, int y)
{
	int dir = DIR_N;

	struct { char *key; struct { int dirs[DIR_TOTAL]; } value; } *visits = NULL, v;
	sh_new_strdup(visits);

	int loop = false;

	while (BETWEEN(x, 0, strlen(lines[0])) && BETWEEN(y, 0, arrlen(lines))) {
		lines[y][x] = DIRS_CHAR[dir];

		char tbuf[32];
		snprintf(tbuf, sizeof tbuf, "%d-%d", x, y);

		if (shgeti(visits, tbuf) >= 0) {
			if (shget(visits, tbuf).dirs[dir]) { // loop, as we've visited this square in this dir?
				loop = true;
				break;
			} else {
				shget(visits, tbuf).dirs[dir] = 1; // been here, but not in this direction
			}
		} else {
			memset(&v, 0, sizeof v);
			v.key = tbuf;
			v.value.dirs[dir] = 1;
			shputs(visits, v);
		}

		i32 nx = 0, ny = 0;

		switch (dir) {
			case DIR_N:
				nx = x;
				ny = y - 1;
				break;
			case DIR_E:
				nx = x + 1;
				ny = y;
				break;
			case DIR_S:
				nx = x;
				ny = y + 1;
				break;
			case DIR_W:
				nx = x - 1;
				ny = y;
				break;
		}

		if (!(BETWEEN(nx, 0, strlen(lines[0])) && BETWEEN(ny, 0, arrlen(lines)))) { // left the map
			loop = false;
			break;
		}

		if (lines[ny][nx] == '#') {
			dir = (dir + 1) % DIR_TOTAL;
			continue;
		} else {
			x = nx;
			y = ny;
		}
	}

	shfree(visits);

	return loop;
}

void p2()
{
	i32 x = 0, y = 0;

    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines) && x == 0 && y == 0; i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '^') {
				y = i;
				x = j;
				lines[y][x] = '.';
			}
		}
	}

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] != '#') {
				// printf("Checking for a wall at %d, %d\n", j, i);

				autofreelines char **copy = copy_lines(lines);
				copy[i][j] = '#';

				if (this_map_loops(copy, x, y)) {
					ans++;
				}
			}
		}
	}

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
