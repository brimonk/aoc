#include "common.h"

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    i32 dial = 50;

	for (i32 i = 0; i < arrlen(lines); i++) {
        int clicks = atoi(lines[i] + 1);
        if (lines[i][0] == 'L') {
            dial -= clicks;
        } else if (lines[i][0] == 'R') {
            dial += clicks;
        } else {
            assert(0);
        }

        while (dial < 0) {
            dial += 100;
        }
        dial %= 100;

        if (dial == 0) {
            ans++;
        }
	}

    printf("p1: %ld\n", ans);
}

i32 rotate(i32 *dial, i32 clicks, i32 dir)
{
    i32 zeroes = 0;

    for (i32 i = 0; i < clicks; i++) {
        *dial += dir;
        if (*dial == -1) {
            *dial = 99;
        }

        *dial %= 100;

        if (*dial == 0) {
            zeroes++;
        }

    }

    return zeroes;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    i32 dial = 50;

	for (i32 i = 0; i < arrlen(lines); i++) {
        i32 clicks = atoi(lines[i] + 1);
        i32 direction = lines[i][0] == 'L' ? -1 : 1;
        ans += rotate(&dial, clicks, direction);
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
