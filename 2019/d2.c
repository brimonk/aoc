#include "common.h"

i32 intcode_read(i32 *intcodes, i32 p)
{
    if (arrlen(intcodes) < p)
        return 0;
    return intcodes[p];
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    for (i32 i = 0; i < strlen(lines[0]); i++)
        if (lines[0][i] == ',')
            lines[0][i] = ' ';

    autofreearr i32 *intcodes = find_all_i32s(lines[0]);

    i32 op = 0;
    i32 run = true;

    intcodes[1] = 12;
    intcodes[2] = 2;

    while (run && op < arrlen(intcodes)) {
        switch (intcodes[op]) {
            case 1: {
                i32 src1 = intcode_read(intcodes, op + 1);
                i32 src2 = intcode_read(intcodes, op + 2);
                i32 dst  = intcode_read(intcodes, op + 3);
                while (arrlen(intcodes) < dst)
                    arrput(intcodes, 0);
                intcodes[dst] = intcodes[src1] + intcodes[src2];
                op += 4;
                break;
            }

            case 2: {
                i32 src1 = intcodes[op + 1];
                i32 src2 = intcodes[op + 2];
                i32 dst  = intcodes[op + 3];
                while (arrlen(intcodes) < dst)
                    arrput(intcodes, 0);
                intcodes[dst] = intcodes[src1] * intcodes[src2];
                op += 4;
                break;
            }

            case 99:
                run = false;
                break;

            default:
                assert(0);
        }
    }

    ans = intcodes[0];

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
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
