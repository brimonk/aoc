#include "common.h"

// TODO put this in common.h
#define BETWEEN(x, min, max)  ((min) <= (x) && (x) < (max))

typedef struct Point {
	i32 x, y;
} Point;

typedef struct PointMap {
	Point key;
	i32 value; // if true, explored
} PointMap;

Point MkPoint(i32 x, i32 y)
{
	Point p = { x, y };
	return p;
}

i32 is_trail(i32 w, i32 h, i32 c, i32 n, i32 x, i32 y)
{
	return BETWEEN(y, 0, h) && BETWEEN(x, 0, w) && c + 1 == n;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr Point *starts = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '0') {
				Point p = { .x = j, .y = i };
				arrput(starts, p);
			}
		}
	}

	i32 w = strlen(lines[0]);
	i32 h = arrlen(lines);

	// perform BFS on our topography map
	for (i32 i = 0; i < arrlen(starts); i++) {
		autofreearr Point *queue = NULL;
		PointMap *explored = NULL;

		arrput(queue, starts[i]);
		hmput(explored, starts[i], true);

		while (arrlen(queue) > 0) {
			Point curr = arrpop(queue);

			if (lines[curr.y][curr.x] == '9') {
				ans++;
			}

			hmput(explored, curr, true);

			Point dirs[] = {
				{ -1,  0 },
				{  1,  0 },
				{  0, -1 },
				{  0,  1 },
			};

			i32 x = curr.x;
			i32 y = curr.y;

			for (i32 j = 0; j < ARRSIZE(dirs); j++) {
				i32 cx = curr.x + dirs[j].x;
				i32 cy = curr.y + dirs[j].y;

				int is_between = BETWEEN(cy, 0, h) && BETWEEN(cx, 0, w);
				Point z = { cx, cy };

				if (is_between && lines[y][x] + 1 == lines[cy][cx] && hmgeti(explored, z) == -1) {
					arrput(queue, z);
				}
			}
		}

		hmfree(explored);
	}

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr Point *starts = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '0') {
				Point p = { .x = j, .y = i };
				arrput(starts, p);
			}
		}
	}

	i32 w = strlen(lines[0]);
	i32 h = arrlen(lines);

	// perform BFS on our topography map
	for (i32 i = 0; i < arrlen(starts); i++) {
		autofreearr Point *queue = NULL;
		PointMap *explored = NULL;

		arrput(queue, starts[i]);
		hmput(explored, starts[i], true);

		while (arrlen(queue) > 0) {
			Point curr = arrpop(queue);

			if (lines[curr.y][curr.x] == '9') {
				ans++;
			}

			// hmput(explored, curr, true);

			Point dirs[] = {
				{ -1,  0 },
				{  1,  0 },
				{  0, -1 },
				{  0,  1 },
			};

			i32 x = curr.x;
			i32 y = curr.y;

			for (i32 j = 0; j < ARRSIZE(dirs); j++) {
				i32 cx = curr.x + dirs[j].x;
				i32 cy = curr.y + dirs[j].y;

				int is_between = BETWEEN(cy, 0, h) && BETWEEN(cx, 0, w);
				Point z = { cx, cy };

				if (is_between && lines[y][x] + 1 == lines[cy][cx]) {
					arrput(queue, z);
				}

#if 0
				if (is_between && lines[y][x] + 1 == lines[cy][cx] && hmgeti(explored, z) == -1) {
					arrput(queue, z);
				}
#endif
			}
		}

		hmfree(explored);
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
