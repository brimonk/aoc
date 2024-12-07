#include "common.h"

// We attempt to recursively evaluate every single math operation ('+' and '*').
i64 is_calibration_possible(i64 *arr, i64 ans, i64 idx, i64 curr)
{
	if (arrlen(arr) - 1 == idx) { // at the end, base case, do we have an answer?
		return ans == curr;
	}

	if (idx == 0)
		return is_calibration_possible(arr, ans, idx + 1, arr[idx + 1]);

	return is_calibration_possible(arr, ans, idx + 1, curr + arr[idx + 1]) ||
		   is_calibration_possible(arr, ans, idx + 1, curr * arr[idx + 1]);
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		char *s = strchr(lines[i], ':');
		*s = ' ';

		autofreearr i64 *nums = find_all_i64s(lines[i]);

		int is_possible = is_calibration_possible(nums, nums[0], 0, 0);
		if (is_possible) {
			ans += nums[0];
		}
	}

    printf("p1: %ld\n", ans);
}

i64 num_concat(i64 a, i64 b)
{
	char n[32];
	snprintf(n, sizeof n, "%ld%ld", a, b);
	i64 z = atoll(n);
	return z;
}

// We attempt to recursively evaluate every single math operation ('+' and '*' and '||').
i64 is_calibration_possible2(i64 *arr, i64 ans, i64 idx, i64 curr)
{
	if (arrlen(arr) - 1 == idx) { // at the end, base case, do we have an answer?
		return ans == curr;
	}

	if (idx == 0)
		return is_calibration_possible2(arr, ans, idx + 1, arr[idx + 1]);

	return 
		is_calibration_possible2(arr, ans, idx + 1, num_concat(curr, arr[idx + 1])) ||
		is_calibration_possible2(arr, ans, idx + 1, curr + arr[idx + 1]) ||
		is_calibration_possible2(arr, ans, idx + 1, curr * arr[idx + 1]);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		char *s = strchr(lines[i], ':');
		*s = ' ';

		autofreearr i64 *nums = find_all_i64s(lines[i]);

		int is_possible = is_calibration_possible2(nums, nums[0], 0, 0);
		printf("%s %s\n", lines[i], is_possible ? "POSSIBLE" : "NOT POSSIBLE");
		if (is_possible) {
			ans += nums[0];
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
