#include "common.h"

#define BETWEEN(x, min, max)  ((min) <= (x) && (x) < (max))

typedef struct Plot {
	i32 x, y;
} Plot;

typedef struct Visited {
	Plot key;
	int value;
} Visited;

void p1_work(Visited **map, char **lines, i32 x, i32 y, i32 *area, i32 *perimeter)
{
	i64 area_ans = 0;
	i64 perimeter_ans = 0;
	Plot start = { .x = x, .y = y };

	Plot *queue = NULL;
	arrput(queue, start);

#define VISITED(p, m)        (hmgeti((m), (p)) >= 0)
#define IN_BOUNDS(p, g)      (BETWEEN((p).x, 0, strlen((g)[0])) && BETWEEN((p).y + 0, 0, arrlen((g))))

	while (arrlen(queue) > 0) {
		Plot curr = arrpop(queue);

		hmput(*map, curr, 1);
		area_ans++;

		Plot n = { curr.x + 0, .y = curr.y - 1 };
		Plot e = { .x = curr.x + 1, .y = curr.y + 0 };
		Plot w = { curr.x - 0, .y = curr.y + 0 };
		Plot s = { curr.x + 0, .y = curr.y + 1 };

		// we compute perimeter by counting the number of non-lines[y][x] shapes there are next to me.
		// brace yourselves

		if (!IN_BOUNDS(n, lines) || (IN_BOUNDS(n, lines) && lines[curr.y][curr.x] != lines[n.y][n.x])) {
			perimeter_ans++;
		}

		if (!IN_BOUNDS(e, lines) || (IN_BOUNDS(e, lines) && lines[curr.y][curr.x] != lines[e.y][e.x])) {
			perimeter_ans++;
		}

		if (!IN_BOUNDS(s, lines) || (IN_BOUNDS(s, lines) && lines[curr.y][curr.x] != lines[s.y][s.x])) {
			perimeter_ans++;
		}

		if (!IN_BOUNDS(w, lines) || (IN_BOUNDS(w, lines) && lines[curr.y][curr.x] != lines[w.y][w.x])) {
			perimeter_ans++;
		}

		// finally, we return to enqueue more coordinates for traversal

		if (!VISITED(n, *map) && IN_BOUNDS(n, lines) && lines[curr.y][curr.x] == lines[n.y][n.x]) {
			arrput(queue, n);
		}

		if (!VISITED(e, *map) && IN_BOUNDS(e, lines) && lines[curr.y][curr.x] == lines[e.y][e.x]) {
			arrput(queue, e);
		}

		if (!VISITED(s, *map) && IN_BOUNDS(s, lines) && lines[curr.y][curr.x] == lines[s.y][s.x]) {
			arrput(queue, s);
		}

		if (!VISITED(w, *map) && IN_BOUNDS(w, lines) && lines[curr.y][curr.x] == lines[w.y][w.x]) {
			arrput(queue, w);
		}
	}

	*area = area_ans;
	*perimeter = perimeter_ans;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	Visited *visited = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			Plot curr = { .x = j, .y = i };
			if (hmgeti(visited, curr) == -1) { // unvisited space in the garden
				i32 area_ans = 0, perimeter_ans = 0;
				p1_work(&visited, lines, j, i, &area_ans, &perimeter_ans);
				printf("region %c %d * %d = %d\n", lines[j][i], area_ans, perimeter_ans, area_ans * perimeter_ans);
				ans += area_ans * perimeter_ans;
			}
		}
	}

	hmfree(visited);

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
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
