#include "common.h"

void tilt_north(char **puzzle)
{
    // tilt the platform to the north
    for (i64 x = 0; x < strlen(puzzle[0]); x++) {
        for (i64 y = 0; y < arrlen(puzzle); y++) {
            for (i64 k = y; k < arrlen(puzzle) && puzzle[y][x] == '.'; k++) {
                if (puzzle[k][x] == '#') {
                    break;
                } else if (puzzle[k][x] == 'O') {
                    puzzle[y][x] = 'O';
                    puzzle[k][x] = '.';
                }
            }
        }
    }
}

void print_puzzle(char **puzzle, char *context)
{
    printf("%s\n", context);
    for (int i = 0; i < arrlen(puzzle); i++) {
        printf("%s\n", puzzle[i]);
    }
}

void spin_cycle(char **puzzle)
{
    // north
    for (i64 x = 0; x < strlen(puzzle[0]); x++) {
        for (i64 y = 0; y < arrlen(puzzle); y++) {
            for (i64 k = y; k < arrlen(puzzle) && puzzle[y][x] == '.'; k++) {
                if (puzzle[k][x] == '#') {
                    break;
                } else if (puzzle[k][x] == 'O') {
                    puzzle[y][x] = 'O';
                    puzzle[k][x] = '.';
                }
            }
        }
    }

    // print_puzzle(puzzle, "north");

    // west
    for (i64 y = 0; y < arrlen(puzzle); y++) {
        for (i64 x = 0; x < strlen(puzzle[0]); x++) {
            for (i64 k = x; k < arrlen(puzzle) && puzzle[y][x] == '.'; k++) {
                if (puzzle[y][k] == '#') {
                    break;
                } else if (puzzle[y][k] == 'O') {
                    puzzle[y][x] = 'O';
                    puzzle[y][k] = '.';
                }
            }
        }
    }

    // print_puzzle(puzzle, "west");

    // south
    for (i64 x = 0; x < strlen(puzzle[0]); x++) {
        for (i64 y = arrlen(puzzle) - 1; y >= 0; y--) {
            for (i64 k = y; k >= 0 && puzzle[y][x] == '.'; k--) {
                if (puzzle[k][x] == '#') {
                    break;
                } else if (puzzle[k][x] == 'O') {
                    puzzle[y][x] = 'O';
                    puzzle[k][x] = '.';
                }
            }
        }
    }

    // print_puzzle(puzzle, "south");

    // east
    for (i64 y = 0; y < arrlen(puzzle); y++) {
        for (i64 x = strlen(puzzle[0]) - 1; x >= 0; x--) {
            for (i64 k = x; k >= 0 && puzzle[y][x] == '.'; k--) {
                if (puzzle[y][k] == '#') {
                    break;
                } else if (puzzle[y][k] == 'O') {
                    puzzle[y][x] = 'O';
                    puzzle[y][k] = '.';
                }
            }
        }
    }

    // print_puzzle(puzzle, "east");
}

i64 compute_north_load(char **puzzle)
{
    i64 ans = 0;
    // do the summing
    for (i64 y = 0; y < arrlen(puzzle); y++) {
        for (i64 x = 0; x < strlen(puzzle[0]); x++) {
            if (puzzle[y][x] == 'O') {
                ans += arrlen(puzzle) - y;
            }
        }
    }
    return ans;
}

void p1()
{
    i64 ans = 0;
    char buf[1024] = {0};

    char **puzzle = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        arrput(puzzle, strdup(buf));
    }

    tilt_north(puzzle);

    // do the summing
    for (i64 y = 0; y < arrlen(puzzle); y++) {
        for (i64 x = 0; x < strlen(puzzle[0]); x++) {
            if (puzzle[y][x] == 'O') {
                ans += arrlen(puzzle) - y;
            }
        }
    }

    printf("p1: %ld\n", ans);

    for (size_t i = 0; i < arrlen(puzzle); i++)
        free(puzzle[i]);
    arrfree(puzzle);
}

void free_puzzle(char **puzzle)
{
    for (size_t i = 0; i < arrlen(puzzle); i++)
        free(puzzle[i]);
    arrfree(puzzle);
}

i64 has_duplicates(char ***all, char **puzzle)
{
    i64 i, j;

    for (i = 0; i < arrlen(all); i++) {
        for (j = 0; j < arrlen(all[i]); j++) {
            if (strcmp(all[i][j], puzzle[j]) != 0) {
                break;
            }
        }
        if (j == arrlen(all[i])) {
            return i;
        }
    }

    return -1;
}

void store_me_daddy(char ****all, char **puzzle)
{
    char **copy = NULL;
    for (size_t i = 0; i < arrlen(puzzle); i++) {
        arrput(copy, strdup(puzzle[i]));
    }
    arrput(*all, copy);
}

void p2()
{
    i64 ans = 0;
    char buf[1024] = {0};

    char **puzzle = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        arrput(puzzle, strdup(buf));
    }

    // const i64 cycles = 1000000000;

    char ***all = NULL;

    i64 cycles = 0;
    for (cycles = 0; has_duplicates(all, puzzle) < 0; cycles++) {
#if 0
        char b[20];
        snprintf(b, sizeof b, "%ld", cycles + 1);
        print_puzzle(puzzle, b);
#endif

        store_me_daddy(&all, puzzle);
        spin_cycle(puzzle);
    }

    i64 first = has_duplicates(all, puzzle);
    i64 idx = (1000000000 - first) % (cycles - first);
    ans = compute_north_load(all[first + idx]);

    printf("p2: %ld\n", ans);

    free_puzzle(puzzle);

    for (size_t i = 0; i < arrlen(all); i++) {
        free_puzzle(all[i]);
    }
    arrfree(all);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
