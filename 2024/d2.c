#include "common.h"

enum {
	DIRECTION_NONE,
	DIRECTION_INCREASING,
	DIRECTION_DECREASING
};

int is_safe(i32 *arr)
{
	int dir = 0;
	int safe = true;

	if (arr[0] < arr[1]) {
		dir = DIRECTION_INCREASING;
	} else if (arr[0] > arr[1]) {
		dir = DIRECTION_DECREASING;
	}

	for (i32 j = 0; j < arrlen(arr) - 1; j++) {
		if (dir == DIRECTION_INCREASING && !(arr[j + 0] < arr[j + 1])) {
			// printf("NOT ALL INCREASING\t");
			safe = false;
			break;
		}

		if (dir == DIRECTION_DECREASING && !(arr[j + 0] > arr[j + 1])) {
			// printf("NOT ALL DECREASING\t");
			safe = false;
			break;
		}

		i32 diff = (int)abs(arr[j + 0] - arr[j + 1]);
		if (!(1 <= diff && diff <= 3)) {
			// printf("DIFF WRONG (%d)\t", diff);
			safe = false;
			break;
		}
	}

	return safe;
}

void p1()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		autofreearr i32 *arr = find_all_i32s(lines[i]);
		if (is_safe(arr)) {
			ans++;
		}
	}

    printf("p1: %ld\n", ans);
}

i32 *clone_except_for(i32 *arr, i32 idx)
{
	i32 *new = NULL;
	for (i32 i = 0; i < arrlen(arr); i++) {
		if (i != idx) {
			arrput(new, arr[i]);
		}
	}
	return new;
}

void p2()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	// create a zillion new arrays, checking if each is safe if we remove but a single element,
	// ONLY if the first one isn't safe to begin with

	for (i32 i = 0; i < arrlen(lines); i++) {
		autofreearr i32 *arr = find_all_i32s(lines[i]);
		if (is_safe(arr)) {
			printf("S %s\n", lines[i]);
			ans++;
		} else {
			i32 safe_removals = false;
			for (i32 j = 0; j < arrlen(arr); j++) {
				autofreearr i32 *clone = clone_except_for(arr, j);
				if (is_safe(clone)) {
					printf("remove %d (%d) is SAFE\n", j, arr[j]);
					safe_removals = true;
					break;
				}
			}

			printf("%s %s (%d) *\n", safe_removals ? "S" : "U", lines[i], safe_removals);
			if (safe_removals) {
				ans++;
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
