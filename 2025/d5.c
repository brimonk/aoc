#include "common.h"

typedef struct Range {
    i64 lo;
    i64 hi;
} Range;

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    autofreearr Range *ranges = NULL;
    i32 in_ingredients = false;

	for (i32 i = 0; i < arrlen(lines); i++) {
        if (strlen(lines[i]) == 0) {
            in_ingredients = true;
            continue;
        }

        if (!in_ingredients) {
            Range z = {
                .lo = atol(lines[i]),
                .hi = atol(strchr(lines[i], '-') + 1)
            };
            arrput(ranges, z);
        } else {

            // scan through our ranges array determining if this is a valid ingredient or not

            i64 ingredient = atol(lines[i]);
            i32 is_spoiled = true;

            for (i32 j = 0; j < arrlen(ranges); j++) {
                if (ranges[j].lo <= ingredient && ingredient <= ranges[j].hi) {
                    is_spoiled = false;
                    break;
                }
            }

            if (!is_spoiled)
                ans++;
        }
	}

    printf("p1: %ld\n", ans);
}

int range_cmp(const void *a, const void *b)
{
    Range *ra = (void *)a;
    Range *rb = (void *)b;
    return -comp_i64(&ra->lo, &rb->lo);
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

    autofreearr Range *ranges = NULL;
    i32 in_ingredients = false;

	for (i32 i = 0; i < arrlen(lines); i++) {
        if (strlen(lines[i]) == 0) {
            in_ingredients = true;
            break;
        }

        if (!in_ingredients) {
            Range z = {
                .lo = atol(lines[i]),
                .hi = atol(strchr(lines[i], '-') + 1)
            };
            arrput(ranges, z);
        }
	}

    qsort(ranges, arrlen(ranges), sizeof(*ranges), range_cmp);

    for (i32 i = 0; i < arrlen(ranges) - 1; i++) {
        i64 lo0 = ranges[i].lo;
        i64 hi0 = ranges[i].hi;
        i64 lo1 = ranges[i + 1].lo;

        if (lo0 <= lo1 && lo1 <= hi0) {
            i64 hi = MAX(ranges[i].hi, ranges[i + 1].hi);
            i64 lo = MIN(ranges[i].lo, ranges[i + 1].lo);

            ranges[i].lo = lo;
            ranges[i].hi = hi;
            arrdel(ranges, i + 1);
            i--;
        }
    }

    for (i32 i = 0; i < arrlen(ranges); i++) {
        i64 lo = ranges[i].lo;
        i64 hi = ranges[i].hi;
        i64 curr_ans = hi - lo + (i64)1;
        ans += curr_ans;
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
