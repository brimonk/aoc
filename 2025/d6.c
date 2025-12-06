#include "common.h"

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    autofreearr i64 **numbers = NULL;
    autofreearr i32 *operators = NULL;

	for (i32 i = 0; i < arrlen(lines); i++) {
        if (i < arrlen(lines) - 1) {
            i64 *line_numbers = find_all_i64s(lines[i]);
            arrput(numbers, line_numbers);
        } else { // last line has the operators
            for (char *s = strtok(lines[i], " "); s; s = strtok(NULL, " ")) {
                arrput(operators, *s);
            }
        }
	}

    for (i32 j = 0; j < arrlen(numbers[0]); j++) {
        i64 interim = 0;
        for (i32 i = 0; i < arrlen(numbers); i++) {
            if (operators[j] == '+') {
                interim += numbers[i][j];
            } else if (operators[j] == '*') {
                if (interim == 0)
                    interim = 1;
                interim *= numbers[i][j];
            }
        }
        ans += interim;
    }

    printf("p1: %ld\n", ans);
}

i32 number_len(char *s)
{
    char *t = strchr(s, ' ');
    char *z = strchr(s, '\0');
    return t ? t - s : z - s;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////// WE LOVE THE GRID PROBLEMS ///////////////////////////// //
    ///////////////////////////////////////////////////////////////////////////////////////////////

    char **ptrs = NULL;
    for (i32 i = 0; i < arrlen(lines); i++) {
        arrput(ptrs, lines[i]);
    }

    char *operator = ptrs[arrlen(ptrs) - 1];

    while (*ptrs[0]) {
        i32 max_len = INT_MIN;
        for (i32 i = 0; i < arrlen(ptrs) - 1; i++) {
            max_len = MAX(max_len, number_len(ptrs[i]));
        }

        i64 interim_total = 0;

        for (i32 i = 0; i < max_len; i++) { // for each digit in the current column
            i32 interim = 0;
            for (i32 j = 0; j < arrlen(ptrs) - 1; j++) { // 
                if (*ptrs[j] == ' ') {
                    ptrs[j]++;
                } else {
                    interim *= 10;
                    interim += *ptrs[j]++ - '0';
                }
            }

            if (*operator == '+') {
                interim_total += interim;
            } else if (*operator == '*') {
                if (interim_total == 0)
                    interim_total = 1;
                interim_total *= interim;
            }
        }

        ans += interim_total;

        // scoot our pointers forward

        for (i32 i = 0; i < arrlen(ptrs) - 1; i++) {
            ptrs[i]++;
        }

        // operator is special, we do this one manually

        operator++;
        while (*operator && isspace(*operator)) {
            operator++;
        }
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
