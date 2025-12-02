#include "common.h"

enum {
    INTCODES_MODE_POSITION,
    INTCODES_MODE_IMMEDIATE
};

i32 dereference(i32 *intcodes, i32 mode, i32 value)
{
    if (mode == INTCODES_MODE_IMMEDIATE) {
        return value;
    } else if (mode == INTCODES_MODE_POSITION) {
        return intcodes[value];
    } else {
        assert(0);
        return 0xffffffff;
    }
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
    autofreearr i32 *intcodes = find_all_i32s(lines[0]);

    i32 pc = 0;
    i32 run = true;

    while (run && pc < arrlen(intcodes)) {
        i32 op = intcodes[pc] % 100;

        i32 modep1 = intcodes[pc] %   1000 /   100;
        i32 modep2 = intcodes[pc] %  10000 /  1000;
        i32 modep3 = intcodes[pc] % 100000 / 10000;

        switch (op) {
            case 1: {
                i32 src1 = dereference(intcodes, modep1, op + 1);
                i32 src2 = dereference(intcodes, modep1, op + 2);
                i32 dst  = dereference(intcodes, modep1, op + 3);
                intcodes[dst] = intcodes[src1] + intcodes[src2];
                pc += 4;
                break;
            }

            case 2: {
                i32 src1 = intcodes[op + 1];
                i32 src2 = intcodes[op + 2];
                i32 dst  = intcodes[op + 3];
                intcodes[dst] = intcodes[src1] * intcodes[src2];
                pc += 4;
                break;
            }

            case 3: {
                i32 pos = dereference(intcodes, modep1, op + 1);
                pc += 2;
                break;
            }

            case 4: {
                i32 pos = dereference(intcodes, modep1, op + 1);
                pc += 2;
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
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
