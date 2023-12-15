#include "common.h"

void p1()
{
    i64 ans = 0;
    char buf[8192] = {0};
    while (buf == bfgets(buf, sizeof buf, stdin)) {
        for (char *s = strtok(buf, ","); s; s = strtok(NULL, ",")) {
            i64 n = 0;
            for (char *t = s; *t; t++) {
                n += *t;
                n *= 17;
                n %= 256;
            }
            ans += n;
        }
    }

    printf("p1: %ld\n", ans);
}

struct box {
    char key[6];
    i32 length;
};

void p2()
{
    i64 ans = 0;

    char buf[8192] = {0};
    struct box **boxes = NULL;

    // arrsetcap(boxes, 256);
    for (i64 i = 0; i < 256; i++)
        arrput(boxes, NULL);

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        for (char *s = strtok(buf, ","); s; s = strtok(NULL, ",")) {
            char *t;
            i64 n = 0;
            for (t = s; isalpha(*t); t++) {
                n += *t;
                n *= 17;
                n %= 256;
            }

            if (*t == '=') {
                struct box b = {0};
                strncpy(b.key, s, t - s);
                b.length = atoi(t + 1);

                size_t i;
                for (i = 0; i < arrlen(boxes[n]); i++) {
                    if (strncmp(boxes[n][i].key, s, t - s) == 0) {
                        break;
                    }
                }
                if (i == arrlen(boxes[n])) {
                    arrput(boxes[n], b);
                } else {
                    boxes[n][i].length = b.length;
                }
            } else if (*t == '-') {
                size_t i;
                for (i = 0; i < arrlen(boxes[n]); i++) {
                    if (strncmp(boxes[n][i].key, s, t - 1 - s) == 0) {
                        break;
                    }
                }
                if (i < arrlen(boxes[n]))
                    arrdel(boxes[n], i);
            }
        }
    }

    for (size_t i = 0; i < arrlen(boxes); i++) {
        for (size_t j = 0; j < arrlen(boxes[i]); j++) {
            // fprintf(stderr, "\t%s %ld %ld %d\n", boxes[i][j].key, i + 1, j + 1, boxes[i][j].length);
            ans += (i + 1) * (j + 1) * boxes[i][j].length;
        }
    }

    printf("p2: %ld\n", ans);

    for (size_t i = 0; i < arrlen(boxes); i++) {
        arrfree(boxes[i]);
    }
    arrfree(boxes);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
