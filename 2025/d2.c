#include "common.h"

int is_p1_invalid(i64 value)
{
    char buf[32];
    snprintf(buf, sizeof buf, "%ld", value);

    int len = strlen(buf);
    int halflen = strlen(buf) / 2;

    char *s = buf;
    char *t = buf + halflen;

    return len % 2 == 0 && strncmp(s, t, halflen) == 0;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
    autofreearr char **ids = find_all_strs_sep(lines[0], ",");

	for (i32 i = 0; i < arrlen(ids); i++) {
        i64 a = atol(ids[i]);
        i64 b = atol(strchr(ids[i], '-') + 1);

        for (i64 j = a; j <= b; j++) {
            if (is_p1_invalid(j)) {
                ans += j;
            }
        }
	}

    printf("p1: %ld\n", ans);
}

int is_p2_invalid(i64 value)
{
    char buf[32];
    snprintf(buf, sizeof buf, "%ld", value);

    int len = strlen(buf);
    int halflen = strlen(buf) / 2;

    char *s = buf;
    for (i32 i = 1; i <= halflen; i++) {
        if (len % i != 0)
            continue;

        int counts = 1;
        for (char *t = s + i; t < s + len; t += i) {
            if (strncmp(s, t, i) == 0) {
                counts++;
            } else {
                break;
            }
        }

        if (counts == len / i) {
            return true;
        }
    }

    return false;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
    autofreearr char **ids = find_all_strs_sep(lines[0], ",");

	for (i32 i = 0; i < arrlen(ids); i++) {
        i64 a = atol(ids[i]);
        i64 b = atol(strchr(ids[i], '-') + 1);

        for (i64 j = a; j <= b; j++) {
            if (is_p2_invalid(j)) {
                ans += j;
            }
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
