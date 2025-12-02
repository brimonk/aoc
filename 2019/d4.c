#include "common.h"

i32 is_p1_pass(char *s)
{
    i32 has_double = false;
    i32 has_only_increase = true;

    for (i32 i = 0; i < strlen(s) - 1; i++) {
        if (s[i] == s[i + 1]) {
            has_double = true;
        }

        if (s[i] > s[i + 1]) {
            has_only_increase = false;
        }
    }

    return has_double && has_only_increase;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    i32 lo = atoi(lines[0]);
    i32 hi = atoi(strchr(lines[0], '-') + 1);

    for (i32 i = lo; i <= hi; i++) {
        char buf[8];
        snprintf(buf, sizeof buf, "%d", i);
        if (is_p1_pass(buf)) {
            ans++;
        }
    }

    printf("p1: %ld\n", ans);
}

i32 is_p2_pass(char *s)
{
    i32 has_double = false;
    i32 has_only_increase = true;
    i32 digits[10] = { 0 };

    for (i32 i = 0; i < strlen(s) - 1; i++) {
        digits[s[i] - '0']++;

        if (s[i] == s[i + 1]) {
            has_double = true;
        }

        if (s[i] > s[i + 1]) {
            has_only_increase = false;
        }
    }

    i32 doubles_count = 0;
    for (i32 i = 0; i < ARRSIZE(digits); i++) {
        if (digits[i] == 2)
            doubles_count++;
    }

    i32 cond = has_double && has_only_increase && doubles_count == 1;

    printf("%s %d\n", s, cond);

    return cond;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    i32 lo = atoi(lines[0]);
    i32 hi = atoi(strchr(lines[0], '-') + 1);

    for (i32 i = lo; i <= hi; i++) {
        char buf[8];
        snprintf(buf, sizeof buf, "%d", i);
        if (is_p2_pass(buf)) {
            ans++;
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
