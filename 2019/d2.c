#include "common.h"

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
    autofreearr i32 *intcodes = find_all_i32s(lines[0]);

    i32 op = 0;
    i32 run = true;

    intcodes[1] = 12;
    intcodes[2] = 2;

    while (run && op < arrlen(intcodes)) {
        switch (intcodes[op]) {
            case 1: {
                i32 src1 = intcodes[op + 1];
                i32 src2 = intcodes[op + 2];
                i32 dst  = intcodes[op + 3];
                intcodes[dst] = intcodes[src1] + intcodes[src2];
                op += 4;
                break;
            }

            case 2: {
                i32 src1 = intcodes[op + 1];
                i32 src2 = intcodes[op + 2];
                i32 dst  = intcodes[op + 3];
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

    for (i32 i = 0; i <= 99; i++) {
        for (i32 j = 0; j <= 99; j++) {
            autofreearr i32 *intcodes = find_all_i32s(lines[0]);

            i32 op = 0;
            i32 run = true;

            intcodes[1] = i;
            intcodes[2] = j;

            while (run && op < arrlen(intcodes)) {
                switch (intcodes[op]) {
                    case 1: {
                        i32 src1 = intcodes[op + 1];
                        i32 src2 = intcodes[op + 2];
                        i32 dst  = intcodes[op + 3];
                        intcodes[dst] = intcodes[src1] + intcodes[src2];
                        op += 4;
                        break;
                    }

                    case 2: {
                        i32 src1 = intcodes[op + 1];
                        i32 src2 = intcodes[op + 2];
                        i32 dst  = intcodes[op + 3];
                        intcodes[dst] = intcodes[src1] * intcodes[src2];
                        op += 4;
                        break;
                    }

                    case 99:
                        run = false;
                        break;

                    default:
                        fprintf(stderr, "op = %d, intcodes[op] = %d\n", op, intcodes[op]);
                        assert(0);
                }
            }

            if (intcodes[0] == 19690720) {
                ans = 100 * i + j;
                goto p2_end;
            }
        }
    }

p2_end:
    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
