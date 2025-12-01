#include "common.h"

int is_key(char *s)
{
    return strchr(s, '.') != NULL;
}

int is_lock(char *s)
{
    return !is_key(s);
}

i32 iabs(i32 v)
{
    return v < 0 ? -v : v;
}

typedef struct Schematic {
    i32 is_lock;
    i32 pins[5];
} Schematic;

int is_match(Schematic *a, Schematic *b)
{
    return iabs(a->pins[0]) + iabs(b->pins[0]) == 10 &&
        iabs(a->pins[1]) + iabs(b->pins[1]) == 10 &&
        iabs(a->pins[2]) + iabs(b->pins[2]) == 10 &&
        iabs(a->pins[3]) + iabs(b->pins[3]) == 10 &&
        iabs(a->pins[4]) + iabs(b->pins[4]) == 10;
}

void print_schematic(Schematic *schematic)
{
    printf("%s - [", schematic->is_lock ? "Lock" : "Key");
    for (i32 j = 0; j < ARRSIZE(schematic->pins); j++) {
        printf("%d%s", schematic->pins[j], j == ARRSIZE(schematic->pins) - 1 ? "" : ", ");
    }
    printf("]\n");
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
    autofreearr Schematic *schematics = NULL;

    i32 row = 0;
    i32 curr[5] = { 0 };
    i32 is_schematic_lock = false;

	for (i32 i = 0; i <= arrlen(lines); i++) {
        // NOTE locks have negative values
        if (i == arrlen(lines) || strlen(lines[i]) == 0) {
            if (!is_schematic_lock) {
                for (i32 j = 0; j < ARRSIZE(curr); j++) {
                    curr[j]--;
                }
            }

            Schematic curr_schematic = {
                .is_lock = is_schematic_lock,
                .pins[0] = curr[0],
                .pins[1] = curr[1],
                .pins[2] = curr[2],
                .pins[3] = curr[3],
                .pins[4] = curr[4],
            };
            print_schematic(&curr_schematic);
            arrput(schematics, curr_schematic);
            row = 0;
            memset(curr, 0, sizeof curr);
        } else if (row++ == 0) {
            is_schematic_lock = is_lock(lines[i]);
        } else {
            for (i32 j = 0; j < strlen(lines[i]); j++) {
                curr[j] += (is_schematic_lock ? -1 : 1) * (lines[i][j] == '#' ? 1 : 0);
            }
        }
	}

    // Try each key for each lock

    for (i32 i = 0; i < arrlen(schematics); i++) {
        for (i32 j = 0; j < arrlen(schematics); j++) {
            if (i == j)
                continue;

            Schematic *a = &schematics[i];
            Schematic *b = &schematics[j];
        }
    }

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
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
