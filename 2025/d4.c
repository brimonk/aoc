#include "common.h"

i32 DIRS[8][2] = {
    { -1, -1 },
    {  0, -1 },
    {  1, -1 },
    { -1,  0 },
    {  1,  0 },
    { -1,  1 },
    {  0,  1 },
    {  1,  1 }
};

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            i32 surrounding = 0;

            for (i32 k = 0; lines[i][j] == '@' && k < ARRSIZE(DIRS); k++) {
                i32 y = i + DIRS[k][1];
                i32 x = j + DIRS[k][0];

                if (!(0 <= y && y < arrlen(lines)))
                    continue;

                if (!(0 <= x && x < strlen(lines[i])))
                    continue;

                if (lines[y][x] == '@') {
                    surrounding++;
                }
            }

            if (lines[i][j] == '@' && surrounding < 4) {
                ans++;
            }
        }
	}

    printf("p1: %ld\n", ans);
}

i32 get_total_papers(char **lines)
{
    i32 sum = 0;
    for (i32 i = 0; i < arrlen(lines); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            if (lines[i][j] == '@')
                sum++;
        }
    }
    return sum;
}

void print_puzzle(char **lines)
{
    for (i32 i = 0; i < arrlen(lines); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            putchar(lines[i][j]);
        }
        putchar('\n');
    }
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    i32 curr_total = get_total_papers(lines);
    i32 next_total = -1;

    while (curr_total != next_total) {
        next_total = curr_total;
        i32 remove = 0;

        // print_puzzle(lines);

        for (i32 i = 0; i < arrlen(lines); i++) {
            for (i32 j = 0; j < strlen(lines[i]); j++) {
                i32 surrounding = 0;

                for (i32 k = 0; lines[i][j] == '@' && k < ARRSIZE(DIRS); k++) {
                    i32 y = i + DIRS[k][1];
                    i32 x = j + DIRS[k][0];

                    if (!(0 <= y && y < arrlen(lines)))
                        continue;

                    if (!(0 <= x && x < strlen(lines[i])))
                        continue;

                    if (lines[y][x] == '@') {
                        surrounding++;
                    }
                }

                if (lines[i][j] == '@' && surrounding < 4) {
                    lines[i][j] = '.';
                    remove++;
                }
            }
        }
        // printf("remove %d\n", remove);
        ans += remove;
        curr_total = get_total_papers(lines);
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
