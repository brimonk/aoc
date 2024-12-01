#include "common.h"

void p1()
{
	i32 *a = NULL, *b = NULL;

    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (size_t i = 0; i < arrlen(lines); i++) {
		i32 x, y;
		sscanf(lines[i], "%d %d", &x, &y);
		arrput(a, x);
		arrput(b, y);
	}

	qsort(a, arrlen(a), sizeof(*a), comp_i32);
	qsort(b, arrlen(b), sizeof(*b), comp_i32);

	for (i32 i = 0; i < arrlen(a); i++) {
		ans += (i32)abs(a[i] - b[i]);
	}

    printf("p1: %ld\n", ans);

	arrfree(a);
	arrfree(b);
}

i32 count(i32 num, i32 *list)
{
	i32 times = 0;
	for (i32 i = 0; i < arrlen(list); i++)
		if (list[i] == num)
			times++;
	return times;
}

void p2()
{
	i32 *a = NULL, *b = NULL;

    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (size_t i = 0; i < arrlen(lines); i++) {
		i32 x, y;
		sscanf(lines[i], "%d %d", &x, &y);
		arrput(a, x);
		arrput(b, y);
	}

	for (i32 i = 0; i < arrlen(a); i++) {
		// ans += (i32)abs(a[i] - b[i]);
		ans += a[i] * count(a[i], b);
	}

    printf("p2: %ld\n", ans);

	arrfree(a);
	arrfree(b);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
