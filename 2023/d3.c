#include "common.h"

char map[1024][1024];

int has_digit(int i, int j)
{
    if (i < 0) return false;
    if (i >= sizeof map[i]) return false;
    if (j < 0) return false;
    if (j >= sizeof map[j]) return false;

    int res = isdigit(map[j][i]);
    return res;
}

int get_pos(int i, int j)
{
    while (0 <= i && isdigit(map[j][i])) {
        i--;
    }
    return i + 1;
}

// NOTE this function writes PERIODS '.' over the number to avoid checking in the future
int read_number(int i, int j)
{
    int num = 0;
    while (isdigit(map[j][i])) {
        num *= 10;
        num += map[j][i] - '0';
        map[j][i] = '.';
        i++;
    }
    return num;
}

void handle_symbols(int *ans, int i, int j)
{
#define DO_THE_THING(x, y) \
    do { \
        if (has_digit((x), (y))) { \
            /* fprintf(stderr, "\tfound number at (%d, %d)\n", (x), (y)); */ \
            int pos = get_pos((x), (y)); \
            /* fprintf(stderr, "\tfound: %*s\n", 5, &map[(y)][pos]); */ \
            int number = read_number(pos, y); \
            /* fprintf(stderr, "\tread number %d at (%d, %d)\n", number, (x), (y)); */ \
            *ans += number; \
        } \
    } while (0)

    DO_THE_THING(i - 1, j - 1);
    DO_THE_THING(i + 0, j - 1);
    DO_THE_THING(i + 1, j - 1);

    DO_THE_THING(i - 1, j + 0);
    DO_THE_THING(i + 1, j + 0);

    DO_THE_THING(i - 1, j + 1);
    DO_THE_THING(i + 0, j + 1);
    DO_THE_THING(i + 1, j + 1);

#undef DO_THE_THING
}

void p1()
{
	char buf[1024];
    int ans = 0;

	memset(buf, 0, sizeof buf);

    memset(map, 0, sizeof map);

    int i, j;

    int rows = 0;
	for (i = 0; buf == fgets(buf, sizeof buf, stdin); i++) {
		buf[strlen(buf) - 1] = 0;
        strncpy(map[i], buf, sizeof map[i]);
	}
    rows = i;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < sizeof map[i] && map[i][j] != '\0'; j++) {
            if (map[i][j] != '.' && !isdigit(map[i][j]) && ispunct(map[i][j])) {
                handle_symbols(&ans, j, i);
            }
        }
    }

    printf("p1: %d\n", ans);
}

void handle_gear_ratios(int *ans, int i, int j)
{
    int value = 1;
    int cnt = 0;

#define DO_THE_THING(x, y) \
    do { \
        if (has_digit((x), (y))) { \
            /* fprintf(stderr, "\tfound number at (%d, %d)\n", (x), (y)); */ \
            int pos = get_pos((x), (y)); \
            /* fprintf(stderr, "\tfound: %*s\n", 5, &map[(y)][pos]); */ \
            int number = read_number(pos, y); \
            /* fprintf(stderr, "\tread number %d at (%d, %d)\n", number, (x), (y)); */ \
            value *= number; \
            cnt++; \
        } \
    } while (0)

    DO_THE_THING(i - 1, j - 1);
    DO_THE_THING(i + 0, j - 1);
    DO_THE_THING(i + 1, j - 1);

    DO_THE_THING(i - 1, j + 0);
    DO_THE_THING(i + 1, j + 0);

    DO_THE_THING(i - 1, j + 1);
    DO_THE_THING(i + 0, j + 1);
    DO_THE_THING(i + 1, j + 1);

    if (cnt == 2)
        *ans += value;

#undef DO_THE_THING
}

void p2()
{
	char buf[1024];
    int ans = 0;

	memset(buf, 0, sizeof buf);

    memset(map, 0, sizeof map);

    int i, j;

    int rows = 0;
	for (i = 0; buf == fgets(buf, sizeof buf, stdin); i++) {
		buf[strlen(buf) - 1] = 0;
        strncpy(map[i], buf, sizeof map[i]);
	}
    rows = i;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < sizeof map[i] && map[i][j] != '\0'; j++) {
            if (map[i][j] == '*') {
                handle_gear_ratios(&ans, j, i);
            }
        }
    }

    printf("p2: %d\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
