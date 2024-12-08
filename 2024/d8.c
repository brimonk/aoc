#include "common.h"

#define BETWEEN(x, min, max)  ((min) <= (x) && (x) < (max))

typedef struct Antennae {
	i32 symbol;
	i32 x;
	i32 y;
} Antennae;

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr Antennae *antennae = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] != '.') {
				Antennae c = { .symbol = lines[i][j], .x = j, .y = i };
				arrput(antennae, c);
			}
		}
	}

	for (i32 i = 0; i < arrlen(antennae); i++) {
		Antennae *curr = &antennae[i];
		for (i32 j = 0; j < arrlen(antennae); j++) {
			if (i == j)
				continue;

			Antennae *check = &antennae[j];

			if (curr->symbol == check->symbol) { // same symbol
				i32 dx = check->x - curr->x;
				i32 dy = check->y - curr->y;

				i32 x = check->x + dx;
				i32 y = check->y + dy;

				if (BETWEEN(x, 0, strlen(lines[0])) && BETWEEN(y, 0, arrlen(lines))) {
					lines[y][x] = '#';
				}
			}
		}
	}

	for (i32 i = 0; i < arrlen(lines); i++) {
		// printf("%s\n", lines[i]);
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '#') {
				ans++;
			}
		}
	}

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr Antennae *antennae = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] != '.') {
				Antennae c = { .symbol = lines[i][j], .x = j, .y = i };
				arrput(antennae, c);
			}
		}
	}

	for (i32 i = 0; i < arrlen(antennae); i++) {
		Antennae *curr = &antennae[i];
		for (i32 j = 0; j < arrlen(antennae); j++) {
			if (i == j)
				continue;

			Antennae *check = &antennae[j];

			if (curr->symbol == check->symbol) { // same symbol
				i32 dx = check->x - curr->x;
				i32 dy = check->y - curr->y;

				i32 x = check->x;
				i32 y = check->y;

				do {
					if (!(BETWEEN(x, 0, strlen(lines[0])) && BETWEEN(y, 0, arrlen(lines)))) {
						break;
					}

					lines[y][x] = '#';
					x += dx;
					y += dy;
				} while (BETWEEN(x, 0, strlen(lines[0])) && BETWEEN(y, 0, arrlen(lines)));
			}
		}
	}

	for (i32 i = 0; i < arrlen(lines); i++) {
		// printf("%s\n", lines[i]);
		for (i32 j = 0; j < strlen(lines[i]); j++) {
			if (lines[i][j] == '#') {
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
