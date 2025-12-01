#include "common.h"

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
        i32 value = atoi(lines[i]);
        ans += value / 3 - 2;
	}

    printf("p1: %ld\n", ans);
}

i32 calc_fuel_p2(i32 mass)
{
    i32 required = mass / 3 - 2;
    if (required > 0) {
        required += calc_fuel_p2(required);
    }
    return required;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
        i32 value = atoi(lines[i]);
        ans += calc_fuel_p2(value);
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
