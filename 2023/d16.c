#include "common.h"

#include <unistd.h>

enum {
	BEAMDIR_NONE,
	BEAMDIR_N,
	BEAMDIR_E,
	BEAMDIR_S,
	BEAMDIR_W,
	BEAMDIR_TOTAL
};

typedef struct Direction {
	int x, y;
} Direction;
Direction directions[] = {
	{  0,  0 },
	{  0, -1 },
	{  1,  0 },
	{  0,  1 },
	{ -1,  0 },
};

typedef struct Beam {
	int x, y;
	int dir; // BEAMDIR
} Beam;

typedef struct Energy {
	int dir[BEAMDIR_TOTAL];
} Energy;

int IsOOB(Beam *beam, size_t w, size_t h)
{
	return beam->x < 0 || beam->x >= w || beam->y < 0 || beam->y >= h;
}

int IsEnergizedSameDir(Energy *energy, Beam *beam, size_t stride)
{
	return energy[beam->y * stride + beam->x].dir[beam->dir];
}

int NumberOfDirs(Energy energy)
{
	int sum = 0;
	if (energy.dir[1]) sum++;
	if (energy.dir[2]) sum++;
	if (energy.dir[3]) sum++;
	if (energy.dir[4]) sum++;
	return sum;
}

int IsEnergized(Energy energy)
{
	return NumberOfDirs(energy) > 0;
}

void PrintGrid(char **grid, Energy *energy, size_t grid_w, size_t grid_h)
{
	for (size_t i = 0; i < grid_h * grid_w; i++) {
		char *newline = i > 0 && (i + 1) % grid_w == 0 ? "\n" : "";
		char chr = IsEnergized(energy[i]) ? '#' : '.';

		if (IsEnergized(energy[i])) {
			chr = '#';
		} else {
			chr = '.';
		}

		if (grid[i / grid_w][i % grid_w] != '.') {
			chr = grid[i / grid_w][i % grid_w];
		} else if (IsEnergized(energy[i])) {
			char nums[] = {
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'
			};

#if 1
			if (grid[i / grid_w][i % grid_w] == '.') {
				int dirs = NumberOfDirs(energy[i]);
				if (dirs == 1) {
					if (energy[i].dir[1]) chr = '^';
					if (energy[i].dir[2]) chr = '>';
					if (energy[i].dir[3]) chr = 'v';
					if (energy[i].dir[4]) chr = '<';
				} else if (dirs >= 10) {
					chr = 'X';
				} else {
					chr = nums[dirs];
				}
			} else {
				chr = grid[i / grid_w][i % grid_w];
			}
#endif
		} else {
			chr = grid[i / grid_w][i % grid_w];
		}

		printf("%c%s", chr, newline);
	}
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	assert(arrlen(lines) > 0);

	size_t grid_h = arrlen(lines);
	size_t grid_w = strlen(lines[0]);

	Energy *energy = calloc(1, grid_h * grid_w * sizeof(*energy));
	Beam *beams = NULL;

	{
		arrsetlen(beams, 1);
		Beam *first = &beams[0];
		first->x = 0;
		first->y = 0;
		first->dir = BEAMDIR_E;
	}

	while (arrlen(beams) > 0) {
		for (size_t i = 0; i < arrlen(beams); i++) {
			Beam *curr = &beams[i];
			if (IsOOB(curr, grid_w, grid_h) || IsEnergizedSameDir(energy, curr, grid_w)) {
				arrdel(beams, i);
				i--;
				continue;
			}

			// If the current square is already energized, we've (probably) found some kind of a
			// loop, and we can quit out right here.

			Beam new = { 0 };
			int do_split = false;

			char square = lines[curr->y][curr->x];
			// printf("found %c\n", square);

			energy[curr->y * grid_w + curr->x].dir[curr->dir] = true;

			switch (square) {
				case '.': // do nothing
					break;

				case '-': {
					if (curr->dir == BEAMDIR_N || curr->dir == BEAMDIR_S) {
						do_split = true;
						curr->dir = BEAMDIR_W;
						new = *curr;
						new.dir = BEAMDIR_E;
					}
					break;
				}

				case '|': {
					if (curr->dir == BEAMDIR_E || curr->dir == BEAMDIR_W) {
						do_split = true;
						new = *curr;
						new.dir = BEAMDIR_N;
						curr->dir = BEAMDIR_S;
					}
					break;
				}

				case '\\': {
					if (curr->dir == BEAMDIR_N) { curr->dir = BEAMDIR_W; } else
					if (curr->dir == BEAMDIR_E) { curr->dir = BEAMDIR_S; } else
					if (curr->dir == BEAMDIR_S) { curr->dir = BEAMDIR_E; } else
					if (curr->dir == BEAMDIR_W) { curr->dir = BEAMDIR_N; }
					break;
				}

				case '/': {
					if (curr->dir == BEAMDIR_N) { curr->dir = BEAMDIR_E; } else
					if (curr->dir == BEAMDIR_E) { curr->dir = BEAMDIR_N; } else
					if (curr->dir == BEAMDIR_S) { curr->dir = BEAMDIR_W; } else
					if (curr->dir == BEAMDIR_W) { curr->dir = BEAMDIR_S; }
					break;
				}

				default:
					assert(0);
			}

			// Update the move, and energize the energized grid
			curr->x += directions[curr->dir].x;
			curr->y += directions[curr->dir].y;

			if (do_split) arrput(beams, new);
		}

		// PrintGrid(lines, energy, grid_w, grid_h);
		// usleep(1 * 1000 * 1000);
	}

#if 0
	for (size_t i = 0; i < arrlen(lines); i++) {
		printf("%s\n", lines[i]);
	}
#endif

	i64 energized = 0;

	for (size_t i = 0; i < grid_h * grid_w; i++) {
		// char *newline = i > 0 && (i + 1) % grid_w == 0 ? "\n" : "";
		char chr = IsEnergized(energy[i]) ? '#' : '.';

		if (IsEnergized(energy[i])) {
			chr = '#';
			energized++;
		} else {
			chr = '.';
		}

#if 0
		if (lines[i / grid_w][i % grid_w] != '.') {
			chr = lines[i / grid_w][i % grid_w];
		} else if (IsEnergized(energy[i])) {
			char nums[] = {
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'
			};

#if 0
			if (lines[i / grid_w][i % grid_w] == '.') {
				int dirs = NumberOfDirs(energy[i]);
				if (dirs == 1) {
					if (energy[i].dir[1]) chr = '^';
					if (energy[i].dir[2]) chr = '>';
					if (energy[i].dir[3]) chr = 'v';
					if (energy[i].dir[4]) chr = '<';
				} else if (dirs >= 10) {
					chr = 'X';
				} else {
					chr = nums[dirs];
				}
			} else {
				chr = lines[i / grid_w][i % grid_w];
			}
#endif
		} else {
			chr = lines[i / grid_w][i % grid_w];
		}
#endif

		chr++;

		// printf("%c%s", chr, newline);
	}

	ans = energized;

    printf("p1: %ld\n", ans);

	arrfree(beams);
	free(energy);
}

void RunSimulation(char **lines, Energy *energy, Beam **beams, size_t grid_w, size_t grid_h)
{
	while (arrlen((*beams)) > 0) {
		for (size_t i = 0; i < arrlen((*beams)); i++) {
			Beam *curr = &(*beams)[i];
			if (IsOOB(curr, grid_w, grid_h) || IsEnergizedSameDir(energy, curr, grid_w)) {
				arrdel((*beams), i);
				i--;
				continue;
			}

			// If the current square is already energized, we've (probably) found some kind of a
			// loop, and we can quit out right here.

			Beam new = { 0 };
			int do_split = false;

			char square = lines[curr->y][curr->x];

			energy[curr->y * grid_w + curr->x].dir[curr->dir] = true;

			switch (square) {
				case '.': // do nothing
					break;

				case '-': {
					if (curr->dir == BEAMDIR_N || curr->dir == BEAMDIR_S) {
						do_split = true;
						curr->dir = BEAMDIR_W;
						new = *curr;
						new.dir = BEAMDIR_E;
					}
					break;
				}

				case '|': {
					if (curr->dir == BEAMDIR_E || curr->dir == BEAMDIR_W) {
						do_split = true;
						new = *curr;
						new.dir = BEAMDIR_N;
						curr->dir = BEAMDIR_S;
					}
					break;
				}

				case '\\': {
					if (curr->dir == BEAMDIR_N) { curr->dir = BEAMDIR_W; } else
					if (curr->dir == BEAMDIR_E) { curr->dir = BEAMDIR_S; } else
					if (curr->dir == BEAMDIR_S) { curr->dir = BEAMDIR_E; } else
					if (curr->dir == BEAMDIR_W) { curr->dir = BEAMDIR_N; }
					break;
				}

				case '/': {
					if (curr->dir == BEAMDIR_N) { curr->dir = BEAMDIR_E; } else
					if (curr->dir == BEAMDIR_E) { curr->dir = BEAMDIR_N; } else
					if (curr->dir == BEAMDIR_S) { curr->dir = BEAMDIR_W; } else
					if (curr->dir == BEAMDIR_W) { curr->dir = BEAMDIR_S; }
					break;
				}

				default:
					assert(0);
			}

			// Update the move, and energize the energized grid
			curr->x += directions[curr->dir].x;
			curr->y += directions[curr->dir].y;

			if (do_split) arrput((*beams), new);
		}
	}
}

i64 CountEnergized(Energy *energy, size_t grid_w, size_t grid_h)
{
	i64 ans = 0;
	for (size_t i = 0; i < grid_h * grid_w; i++)
		if (IsEnergized(energy[i]))
			ans++;
	return ans;
}

i64 RunSimWithDirection(char **lines, size_t grid_w, size_t grid_h, size_t x, size_t y, int dir)
{
	Energy *energy = calloc(1, grid_h * grid_w * sizeof(*energy));
	Beam *beams = NULL;

	{
		arrsetlen(beams, 1);
		Beam *first = &beams[0];
		first->x = x;
		first->y = y;
		first->dir = dir;
	}

	RunSimulation(lines, energy, &beams, grid_w, grid_h);

	i64 ans = CountEnergized(energy, grid_w, grid_h);

	arrfree(beams);
	free(energy);

	return ans;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	assert(arrlen(lines) > 0);

	size_t grid_h = arrlen(lines);
	size_t grid_w = strlen(lines[0]);

	for (size_t i = 0; i < grid_w; i++) {
		i64 new_ans = RunSimWithDirection(lines, grid_w, grid_h, i, 0, BEAMDIR_S);
		ans = MAX(ans, new_ans);
	}

	for (size_t i = 0; i < grid_w; i++) {
		i64 new_ans = RunSimWithDirection(lines, grid_w, grid_h, i, grid_h - 1, BEAMDIR_N);
		ans = MAX(ans, new_ans);
	}

	for (size_t i = 0; i < grid_h; i++) {
		i64 new_ans = RunSimWithDirection(lines, grid_w, grid_h, 0, i, BEAMDIR_E);
		ans = MAX(ans, new_ans);
	}

	for (size_t i = 0; i < grid_h; i++) {
		i64 new_ans = RunSimWithDirection(lines, grid_w, grid_h, grid_w - 1, i, BEAMDIR_W);
		ans = MAX(ans, new_ans);
	}

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
	assert(ARRSIZE(directions) == BEAMDIR_TOTAL);

    p1();
    rewind(stdin);
    p2();
    return 0;
}
