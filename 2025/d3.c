#include "common.h"

i32 max_joltage(char *s)
{
    i32 max = INT_MIN;
    for (i32 i = 0; i < strlen(s); i++) {
        for (i32 j = i + 1; j < strlen(s); j++) {
            int test = ((s[i] - '0') * 10) + (s[j] - '0');
            if (test > max) {
                max = test;
            }
        }
    }
    return max;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
        i32 joltage = max_joltage(lines[i]);
        ans += joltage;
	}

    printf("p1: %ld\n", ans);
}

#define MAXN 1000 // needs to be bigger than the largest input
#define K   12
#define DIG 10

i64 max_joltage2(const char *s)
{
    i32 n = strlen(s);
    int next_pos[MAXN+1][DIG];
    char out[K + 1] = { 0 };

    memset(next_pos, 0xff, sizeof next_pos);

    // fill in our "next occurrence" table (next_pos[i][d] = next index >= i, where digit d appears
    // -1 if not found

    for (i32 i = n - 1; i >= 0; i--) {
        for (i32 d = 0; d < 10; d++) {
            next_pos[i][d] = next_pos[i + 1][d];
        }

        i32 digit = s[i] - '0';
        next_pos[i][digit] = i;
    }

    i32 pos = 0;
    i32 out_idx = 0;

    for (i32 pick = 0; pick < K; pick++) {
        for (i32 d = 9; d >= 0; d--) { // Try digits from 9 to 0
            i32 p = next_pos[pos][d];
            if (p < 0)
                continue;

            // check feasibility: remaining characters >= remaining picks
            i32 remaining_needed = K - (pick + 1);
            i32 remaining_available = n - (p + 1);

            if (remaining_available >= remaining_needed) {
                out[out_idx++] = d + '0';
                pos = p + 1;
                break;
            }
        }
    }

    return atol(out);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
        i64 joltage = max_joltage2(lines[i]);
        ans += joltage;
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
