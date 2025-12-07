#include "common.h"

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    char *S = strchr(lines[0], 'S');
    lines[1][S - lines[0]] = '|';

	for (i32 i = 1; i < arrlen(lines); i++) { // propagate to the next line, count the splits
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            if (lines[i][j] == '|') {
                if (i + 1 < arrlen(lines)) {
                    if (lines[i + 1][j] == '^') { // split
                        ans++;
                        if (0 <= j - 1 && lines[i + 1][j - 1] == '.')
                            lines[i + 1][j - 1] = '|';
                        if (j + 1 < strlen(lines[i + 1]) && lines[i + 1][j + 1] == '.')
                            lines[i + 1][j + 1] = '|';
                    } else {
                        lines[i + 1][j] = '|';
                    }
                }
            }
        }
	}

    printf("p1: %ld\n", ans);
}

typedef struct LookupKey {
    i32 x, y;
} LookupKey;

typedef struct Lookup {
    LookupKey key;
    i64 value;
} Lookup;

Lookup *lookup = NULL;

i64 recurse_quantum_beam(char **lines, i32 x, i32 y)
{
    i64 ans = 0;

    if (arrlen(lines) <= y) {
        return 0;
    }

    if (lines[y][x] == '^') { // split, look up cost
        LookupKey key = { x, y };
        Lookup *cost = hmgetp_null(lookup, key);
        if (cost == NULL) {
            ans = recurse_quantum_beam(lines, x - 1, y) + recurse_quantum_beam(lines, x + 1, y) + 1;
            hmput(lookup, key, ans);
        } else {
            ans = cost->value;
        }
    } else {
        ans = recurse_quantum_beam(lines, x, y + 1);
    }

    return ans;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    char *S = strchr(lines[0], 'S');

    ans = recurse_quantum_beam(lines, S - lines[0], 1) + 1;

    printf("p2: %ld\n", ans);

    hmfree(lookup);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
