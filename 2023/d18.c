#include "common.h"

typedef struct {
	int is_dug;
	int color;
} Hole;

typedef struct {
	i64 x, y;
} Direction;

typedef Direction Point;

Direction DIRECTIONS[] = {
	{  0, -1 },
	{  1,  0 },
	{  0,  1 },
	{ -1,  0 },
};

int absi(int z)
{
	return ~z + 1;
}

Point MakePoint(i64 x, i64 y)
{
	Point p = { x, y };
	return p;
}

i64 manhattan_distance(Point p1, Point p2)
{
	return (i64)abs(p1.x - p2.x) + (i64)abs(p1.y - p2.y);
}

i64 solve(Point *points)
{
	i64 len = arrlen(points);
	i64 area = 0;
	i64 perimiter = 0;

	// Pick's theorem can be used to solve this.
	//     A = i + b / 2 - 1
	//
	// Where A is area, i is number of interior points, b is the number of boundary points
	// (perimeter).
	//
	// We want the number of interior points, so we need to do a little algebra to get that.
	//
	//     i = (A + 1) - (b / 2)
	//
	// However, the problem asks us to give both the area of the internal points AND the outer
	// points (the trench is part of the answer).

	for (i64 i = 0; i < arrlen(points); i++) {
		Point *p1 = &points[i];
		Point *p2 = &points[(i + 1) % len];

		i64 p = manhattan_distance(*p1, *p2);
		i64 a = (p1->y * p2->x) - (p1->x * p2->y);

#if 1
		printf("(%ld, %ld) -> (%ld, %ld). A: %ld, P: %ld, NA: %ld, NP: %ld\n",
			p1->x, p1->y, p2->x, p2->y, a, p, area + a, perimiter + p
		);
#endif

		perimiter += p;
		area += a;
	}

	area = (i64)abs(area);

	return ((i64)abs(area) + perimiter) / 2 + 1;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	int x = 0, y = 0;
	Point *points = NULL;

	for (size_t i = 0; i < arrlen(lines); i++) {
		int steps = 0, color = 0, dir = 0;

		sscanf(lines[i], "%c %d (#%X)", (char *)&dir, &steps, &color);

		// printf("%c %d\n", (char)dir, steps);

		switch (dir) {
		case 'U': dir = 0; break;
		case 'R': dir = 1; break;
		case 'D': dir = 2; break;
		case 'L': dir = 3; break;
		default: assert(0);
		}

		x += DIRECTIONS[dir].x * steps;
		y += DIRECTIONS[dir].y * steps;

		arrput(points, MakePoint(x, y));
	}

	ans = solve(points);

	arrfree(points);

    printf("p1: %ld\n", ans);
}

Direction GetDirection(int d)
{
	switch (d) {
	case '0': return DIRECTIONS[0];
	case '1': return DIRECTIONS[2];
	case '2': return DIRECTIONS[3];
	case '3': return DIRECTIONS[1];
	case 'U': return DIRECTIONS[0];
	case 'R': return DIRECTIONS[1];
	case 'D': return DIRECTIONS[2];
	case 'L': return DIRECTIONS[3];
	default: assert(0);
	}
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	i64 num_points = 0;
	i64 x = 0, y = 0;
	Point *points = NULL;

	arrput(points, MakePoint(x, y));

	for (size_t i = 0; i < arrlen(lines); i++) {
		int steps = 0, dir = 0, trash, t2;

		sscanf(lines[i], "%c %d (#%5X%1c)", (char *)&trash, &t2, &steps, (char *)&dir);

		Direction d = GetDirection(dir);

		num_points += steps;

		x += d.x * (i64)steps;
		y += d.y * (i64)steps;

		printf("(%ld, %ld)\n", x, y);

		arrput(points, MakePoint(x, y));
	}

	ans = solve(points);

	arrfree(points);

    printf("p2: %ld\n", ans);
}

void test_solve(void)
{
	Point *points = NULL;
	arrput(points, MakePoint(0, 0));
	arrput(points, MakePoint(0, 2));
	arrput(points, MakePoint(2, 2));
	arrput(points, MakePoint(2, 0));
	assert(9 == solve(points));
	arrfree(points);

	points = NULL;
	arrput(points, MakePoint(0, 0));
	arrput(points, MakePoint(0, 4));
	arrput(points, MakePoint(4, 4));
	arrput(points, MakePoint(4, 0));
	assert(25 == solve(points));
	arrfree(points);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
