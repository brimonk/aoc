#include "common.h"

#define BETWEEN(x, min, max)  ((min) <= (x) && (x) < (max))

i32 horizontal(char **lines)
{
	i32 count = 0;
	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (strncmp(lines[i] + j, "XMAS", 4) == 0) {
				count++;
			}
			
			if (strncmp(lines[i] + j, "SAMX", 4) == 0) {
				count++;
			}
		}
	}
	return count;
}

i32 vertical(char **lines)
{
	i32 count = 0;
	for (i32 j = 0; j < strlen(lines[0]); j++) {
		for (i32 i = 0; i < arrlen(lines); i++) {
			if ((i + 0) < arrlen(lines) && lines[i + 0][j] == 'X')
			if ((i + 1) < arrlen(lines) && lines[i + 1][j] == 'M')
			if ((i + 2) < arrlen(lines) && lines[i + 2][j] == 'A')
			if ((i + 3) < arrlen(lines) && lines[i + 3][j] == 'S') {
				count++;
			}

			if ((i + 0) < arrlen(lines) && lines[i + 0][j] == 'S')
			if ((i + 1) < arrlen(lines) && lines[i + 1][j] == 'A')
			if ((i + 2) < arrlen(lines) && lines[i + 2][j] == 'M')
			if ((i + 3) < arrlen(lines) && lines[i + 3][j] == 'X') {
				count++;
			}
		}
	}
	return count;
}

i32 diagonal(char **lines)
{
	i32 count = 0;
	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {

			{
				// down and to the right
				if (BETWEEN(i + 0, 0, arrlen(lines)) && BETWEEN(j + 0, 0, strlen(lines[i])) && lines[i + 0][j + 0] == 'X')
				if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i + 1][j + 1] == 'M')
				if (BETWEEN(i + 2, 0, arrlen(lines)) && BETWEEN(j + 2, 0, strlen(lines[i])) && lines[i + 2][j + 2] == 'A')
				if (BETWEEN(i + 3, 0, arrlen(lines)) && BETWEEN(j + 3, 0, strlen(lines[i])) && lines[i + 3][j + 3] == 'S') {
					count++;
				}
			}

			{
				// down and to the left
				if (BETWEEN(i + 0, 0, arrlen(lines)) && BETWEEN(j - 0, 0, strlen(lines[i])) && lines[i + 0][j - 0] == 'X')
				if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i + 1][j - 1] == 'M')
				if (BETWEEN(i + 2, 0, arrlen(lines)) && BETWEEN(j - 2, 0, strlen(lines[i])) && lines[i + 2][j - 2] == 'A')
				if (BETWEEN(i + 3, 0, arrlen(lines)) && BETWEEN(j - 3, 0, strlen(lines[i])) && lines[i + 3][j - 3] == 'S') {
					count++;
				}
			}

			{
				// down and to the right
				if (BETWEEN(i - 0, 0, arrlen(lines)) && BETWEEN(j + 0, 0, strlen(lines[i])) && lines[i - 0][j + 0] == 'X')
				if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i - 1][j + 1] == 'M')
				if (BETWEEN(i - 2, 0, arrlen(lines)) && BETWEEN(j + 2, 0, strlen(lines[i])) && lines[i - 2][j + 2] == 'A')
				if (BETWEEN(i - 3, 0, arrlen(lines)) && BETWEEN(j + 3, 0, strlen(lines[i])) && lines[i - 3][j + 3] == 'S') {
					count++;
				}
			}

			{
				// down and to the left
				if (BETWEEN(i - 0, 0, arrlen(lines)) && BETWEEN(j - 0, 0, strlen(lines[i])) && lines[i - 0][j - 0] == 'X')
				if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i - 1][j - 1] == 'M')
				if (BETWEEN(i - 2, 0, arrlen(lines)) && BETWEEN(j - 2, 0, strlen(lines[i])) && lines[i - 2][j - 2] == 'A')
				if (BETWEEN(i - 3, 0, arrlen(lines)) && BETWEEN(j - 3, 0, strlen(lines[i])) && lines[i - 3][j - 3] == 'S') {
					count++;
				}
			}
		}
	}
	return count;
}

void p1()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	ans += horizontal(lines);
	ans += vertical(lines);
	ans += diagonal(lines);

    printf("p1: %ld\n", ans);
}

i32 x_mas_search(char **lines)
{
	i32 count = 0;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {

			if (lines[i][j] != 'A')
				continue;

			// 1 3
			//  A
			// 2 4

			// M S
			//  A
			// M S

			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i - 1][j - 1] == 'M') // 1
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i + 1][j - 1] == 'M') // 2
			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i - 1][j + 1] == 'S') // 3
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i + 1][j + 1] == 'S') { // 4
				count++;
			}

			// M M
			//  A
			// S S

			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i - 1][j - 1] == 'M')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i + 1][j - 1] == 'S')
			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i - 1][j + 1] == 'M')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i + 1][j + 1] == 'S') {
				count++;
			}

			// S M
			//  A
			// S M

			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i - 1][j - 1] == 'S')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i + 1][j - 1] == 'S')
			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i - 1][j + 1] == 'M')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i + 1][j + 1] == 'M') {
				count++;
			}

			// S S
			//  A
			// M M

			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i - 1][j - 1] == 'S')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j - 1, 0, strlen(lines[i])) && lines[i + 1][j - 1] == 'M')
			if (BETWEEN(i - 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i - 1][j + 1] == 'S')
			if (BETWEEN(i + 1, 0, arrlen(lines)) && BETWEEN(j + 1, 0, strlen(lines[i])) && lines[i + 1][j + 1] == 'M') {
				count++;
			}

		}
	}

	return count;
}

void p2()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();
	ans = x_mas_search(lines);

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
