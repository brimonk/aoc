#include "common.h"

i64 f(i64 b, i64 tt, i64 d)
{
    return b * (tt - b);
}

void p1()
{
    i64 ans = 0;
    char buf[1024];

    i64 *t = NULL;
    i64 *d = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = strchr(buf, ':') + 1;
        if (t == NULL) {
            t = find_all_i64s(s);
        } else {
            d = find_all_i64s(s);
        }
    }

    assert(arrlen(t) == arrlen(d));

    i64 *ways = NULL;

    for (size_t i = 0; i < arrlen(t); i++) {
        arrput(ways, 0);
        for (i64 j = 0; j <= t[i]; j++) {
            if (d[i] < f(j, t[i], d[i])) {
                ways[i]++;
            }
        }
    }

    ans = 1;
    for (i64 i = 0; i < arrlen(ways); i++) {
        // fprintf(stderr, "\t%ld\n", ways[i]);
        ans *= ways[i];
    }

    arrfree(t);
    arrfree(d);
    arrfree(ways);

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
    char buf[1024];

    i64 t = 0;
    i64 d = 0;
    char tbuf[1024] = {0};

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        memset(tbuf, 0, sizeof tbuf);
        char *s = strchr(buf, ':') + 1;
        if (t == 0) {
            char *z = tbuf;
            while (s && *s) {
                if (isdigit(*s))
                    *z++ = *s;
                s++;
            }
            t = atoll(tbuf);
        } else {
            char *z = tbuf;
            while (s && *s) {
                if (isdigit(*s))
                    *z++ = *s;
                s++;
            }
            d = atoll(tbuf);
        }
    }

    for (size_t i = 0; i < t; i++) {
        if (d < f(i, t, d)) {
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
