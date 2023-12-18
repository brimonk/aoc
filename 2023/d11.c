#include "common.h"

char *copy_to_arr(char *s)
{
    char *t = NULL;
    while (*s) {
        arrput(t, *s);
        s++;
    }
    return t;
}

void expand_rows(char ***map)
{
    for (i64 i = 0; i < arrlen(*map); i++) {
        if (strchr((*map)[i], '#') == NULL) {
            arrins(*map, i, copy_to_arr((*map)[i]));
            i++;
        }
    }
}

void expand_cols(char ***map)
{
    for (i64 i = 0; i < strlen((*map)[0]); i++) { // for all cols
        i64 j;
        for (j = 0; j < arrlen((*map)); j++) { // check each row for '#'
            if ((*map)[j][i] == '#') {
                break;
            }
        }
        if (j == arrlen((*map))) {
            for (i64 k = 0; k < arrlen((*map)); k++) {
                arrins((*map)[k], i, '.');
            }
            i++;
        }
    }
}

void expand(char ***map)
{
    expand_rows(map);
    expand_cols(map);
}

typedef struct ivec2 {
    i64 x, y;
} ivec2;

typedef struct pair {
    ivec2 src;
    ivec2 dst;
    i64 cost;
} pair;

i64 calc_cost(ivec2 src, ivec2 dst)
{
    i64 ans = abs(dst.x - src.x) + abs(dst.y - src.y);
    // printf("(%ld, %ld) to (%ld, %ld) = %ld\n",
        // src.x, src.y, dst.x, dst.y, ans
    // );
    return ans;
}

void p1()
{
    i64 ans = 0;
    char buf[1024] = {0};

    char **map = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        arrput(map, copy_to_arr(buf));
    }

    expand(&map);

    ivec2 *galaxies = NULL;

    for (i64 i = 0; i < arrlen(map); i++) {
        for (i64 j = 0; j < arrlen(map[i]); j++) {
            if (map[i][j] == '#') {
                ivec2 v = { .x = j, .y = i };
                arrput(galaxies, v);
            }
        }
    }

    for (i64 i = 0; i < arrlen(galaxies); i++) {
        for (i64 j = 0; j < arrlen(galaxies); j++) {
            if (i == j) continue;
            ans += calc_cost(galaxies[i], galaxies[j]);
        }
    }

    ans /= 2;

#if 0
    for (i64 i = 0; i < arrlen(map); i++) {
        for (i64 j = 0; j < strlen(map[i]); j++) {
            putchar(map[i][j]);
        }
        putchar('\n');
    }
#endif

    printf("p1: %ld\n", ans);

    arrfree(galaxies);
    for (i64 i = 0; i < arrlen(map); i++)
        arrfree(map[i]);
    arrfree(map);
}

#define EXPAND_CONST (1000000 - 1)

void expand_dong(ivec2 *v, i64 *blank_rows, i64 *blank_cols)
{
    i64 rows = 0;
    for (i64 i = 0; i < arrlen(blank_rows); i++) {
        if (blank_rows[i] < v->y) {
            rows++;
        }
    }

    i64 cols = 0;
    for (i64 i = 0; i < arrlen(blank_cols); i++) {
        if (blank_cols[i] < v->x) {
            cols++;
        }
    }

    v->y += (rows * EXPAND_CONST);
    v->x += (cols * EXPAND_CONST);
}

void p2()
{
    i64 ans = 0;
    char buf[1024] = {0};

    char **map = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        arrput(map, copy_to_arr(buf));
    }

    i64 *blank_rows = NULL;
    i64 *blank_cols = NULL;

    for (i64 i = 0; i < arrlen(map); i++) {
        if (strchr(map[i], '#') == NULL)
            arrput(blank_rows, i);
    }

    for (i64 i = 0; i < arrlen(map[0]); i++) { // for all cols
        i64 j;
        for (j = 0; j < arrlen(map); j++) { // check each row for '#'
            if (map[j][i] == '#') {
                break;
            }
        }
        if (j == arrlen((*map))) {
            arrput(blank_cols, i);
        }
    }

#if 0
    printf("blank rows ");
    for (i64 i = 0; i < arrlen(blank_rows); i++)
        printf("%ld%s", blank_rows[i], i == arrlen(blank_rows) - 1 ? "\n" : ", ");

    printf("blank cols ");
    for (i64 i = 0; i < arrlen(blank_cols); i++)
        printf("%ld%s", blank_cols[i], i == arrlen(blank_cols) - 1 ? "\n" : ", ");
#endif

    ivec2 *galaxies = NULL;

    for (i64 i = 0; i < arrlen(map); i++) {
        for (i64 j = 0; j < arrlen(map[i]); j++) {
            if (map[i][j] == '#') {
                ivec2 v = { .x = j, .y = i };
                expand_dong(&v, blank_rows, blank_cols);
                arrput(galaxies, v);
            }
        }
    }

    for (i64 i = 0; i < arrlen(galaxies); i++) {
        for (i64 j = 0; j < arrlen(galaxies); j++) {
            if (i == j) continue;
            ans += calc_cost(galaxies[i], galaxies[j]);
        }
    }

    ans /= 2;

    printf("p2: %ld\n", ans);

    arrfree(blank_rows);
    arrfree(blank_cols);
    arrfree(galaxies);
    for (i64 i = 0; i < arrlen(map); i++)
        arrfree(map[i]);
    arrfree(map);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
