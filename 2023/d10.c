#include "common.h"

struct node {
    i32 c;
    i32 d;
    i32 inside;
};

int connects_to_me(int s, i32 sx, i32 sy, i32 x, i32 y)
{
    if (sy - 1 == y) {
        if (s == '|' || s == 'F' || s == '7')
            return true;
    } else if (sy + 1 == y) {
        if (s == '|' || s == 'L' || s == 'J')
            return true;
    } else if (sx - 1 == x) {
        if (s == '-' || s == 'F' || s == 'L')
            return true;
    } else if (sx + 1 == x) {
        if (s == '-' || s == 'J' || s == '7')
            return true;
    }
    return false;
}

i32 dfs(struct node **nodes, i32 x, i32 y, i32 d)
{
    if (y < 0 || arrlen(nodes) < y)
        return -1;
    if (x < 0 || arrlen(nodes[0]) < x)
        return -1;

    if (nodes[y][x].d == -1) {
        nodes[y][x].d = d;

        switch (nodes[y][x].c) {
            case 'S': {
                if (y > 0 && connects_to_me(nodes[y - 1][x].c, x, y - 1, x, y)) {
                    return dfs(nodes, x, y - 1, d + 1);
                } else if (y < arrlen(nodes) && connects_to_me(nodes[y + 1][x].c, x, y + 1, x, y)) {
                    return dfs(nodes, x, y + 1, d + 1);
                } else if (x > 0 && connects_to_me(nodes[y][x - 1].c, x - 1, y, x, y)) {
                    return dfs(nodes, x - 1, y, d + 1);
                } else if (x < arrlen(nodes[y]) && connects_to_me(nodes[y][x + 1].c, x + 1, y, x, y)) {
                    return dfs(nodes, x + 1, y, d + 1);
                } else {
                    assert(0);
                }
                break;
            }
            case '|': {
                i32 a = dfs(nodes, x, y - 1, d + 1);
                i32 b = dfs(nodes, x, y + 1, d + 1);
                return MAX(a, b);
            }
            case '-': {
                i32 a = dfs(nodes, x - 1, y, d + 1);
                i32 b = dfs(nodes, x + 1, y, d + 1);
                return MAX(a, b);
            }
            case 'L': {
                i32 a = dfs(nodes, x, y - 1, d + 1);
                i32 b = dfs(nodes, x + 1, y, d + 1);
                return MAX(a, b);
            }
            case 'J': {
                i32 a = dfs(nodes, x, y - 1, d + 1);
                i32 b = dfs(nodes, x - 1, y, d + 1);
                return MAX(a, b);
            }
            case '7': {
                i32 a = dfs(nodes, x - 1, y, d + 1);
                i32 b = dfs(nodes, x, y + 1, d + 1);
                return MAX(a, b);
            }
            case 'F': {
                i32 a = dfs(nodes, x, y + 1, d + 1);
                i32 b = dfs(nodes, x + 1, y, d + 1);
                return MAX(a, b);
            }
        }
    } else {
        return d;
    }

    return -1;
}

void p1()
{
    i64 ans = 0;
    char buf[1024] = {0};
    struct node **nodes = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = buf;

        struct node *temp = NULL;

        for (size_t i = 0; i < strlen(s); i++) {
            struct node n = { .c = s[i], .d = -1 };
            arrput(temp, n);
        }

        arrput(nodes, temp);
    }

    i32 x = -1, y = -1;

    // find 'S'
    for (size_t j = 0; j < arrlen(nodes); j++) {
        for (size_t i = 0; i < arrlen(nodes[i]); i++) {
            if (nodes[j][i].c == 'S') {
                y = j;
                x = i;
                break;
            }
        }
    }

    ans = dfs(nodes, x, y, 0);
    ans /= 2;

    printf("p1: %ld\n", ans);

    for (size_t i = 0; i < arrlen(nodes); i++) {
        arrfree(nodes[i]);
    }
    arrfree(nodes);
}

void fix_s(struct node **nodes, i32 x, i32 y)
{
    assert(nodes[y][x].c == 'S');

    i32 n = 0, s = 0, e = 0, w = 0;

    do {
        if (y == 0) break;
        i32 c = nodes[y - 1][x].c;
        if (c == '|' || c == '7' || c == 'F') {
            n = true;
        }
    } while (0);

    // that was the wife :)

    do {
        if (y == arrlen(nodes)) break;
        i32 c = nodes[y + 1][x].c;
        if (c == '|' || c == 'J' || c == 'L') {
            s = true;
        }
    } while (0);

    do {
        if (x == arrlen(nodes[y])) break;
        i32 c = nodes[y][x + 1].c;
        if (c == '-' || c == '7' || c == 'J') {
            e = true;
        }
    } while (0);

    do {
        if (x == 0) break;
        i32 c = nodes[y][x - 1].c;
        if (c == '-' || c == 'L' || c == 'F') {
            w = true;
        }
    } while (0);

    if (n && e) nodes[y][x].c = 'L';
    if (n && s) nodes[y][x].c = '|';
    if (n && w) nodes[y][x].c = 'J';
    if (w && s) nodes[y][x].c = '7';
    if (w && e) nodes[y][x].c = '-';
    if (s && e) nodes[y][x].c = 'F';
}

i32 is_inside(struct node **nodes, i32 x, i32 y)
{
    i32 crosses = 0;
    i32 expects = 0;

    // we only go east
    for (; x < arrlen(nodes[y]); x++) {
        if (nodes[y][x].d == -1)
            continue;

        int c = nodes[y][x].c;
        if (c == 'S') {
            fix_s(nodes, x, y);
            c = nodes[y][x].c;
        }

        if (c == '|') {
            crosses++;
        } else if (c == 'L') {
            expects = '7';
        } else if (c == '7') {
            if (expects == '7')
                crosses++;
            expects = 0;
        } else if (c == 'F') {
            expects = 'J';
        } else if (c == 'J') {
            if (expects == 'J')
                crosses++;
            expects = 0;
        }
    }

    return crosses % 2 == 1;
}

void annotate_non_traversed(struct node **nodes)
{
    for (size_t y = 0; y < arrlen(nodes); y++) {
        for (size_t x = 0; x < arrlen(nodes[y]); x++) {
            if (nodes[y][x].d == -1) {
                nodes[y][x].inside = is_inside(nodes, x, y);
            }
        }
    }
}

void p2()
{
    i64 ans = 0;
    char buf[1024] = {0};
    struct node **nodes = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = buf;

        struct node *temp = NULL;

        for (size_t i = 0; i < strlen(s); i++) {
            struct node n = { .c = s[i], .d = -1, .inside = false };
            arrput(temp, n);
        }

        arrput(nodes, temp);
    }

    i32 x = -1, y = -1;

    // find 'S'
    for (size_t j = 0; j < arrlen(nodes); j++) {
        for (size_t i = 0; i < arrlen(nodes[j]); i++) {
            if (nodes[j][i].c == 'S') {
                y = j;
                x = i;
                break;
            }
        }
    }

    dfs(nodes, x, y, 0);
    annotate_non_traversed(nodes);

    // count inside nodes
    for (size_t j = 0; j < arrlen(nodes); j++) {
        for (size_t i = 0; i < arrlen(nodes[j]); i++) {
            if (nodes[j][i].inside) {
                ans++;
            }
        }
    }

    printf("p2: %ld\n", ans);

#if 0
    for (size_t i = 0; i < arrlen(nodes); i++) {
        for (size_t j = 0; j < arrlen(nodes[i]); j++) {
            if (nodes[i][j].inside)
                putchar('I');
            else
                putchar(nodes[i][j].c);
        }
        putchar('\n');
    }
#endif

    for (size_t i = 0; i < arrlen(nodes); i++) {
        arrfree(nodes[i]);
    }
    arrfree(nodes);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
