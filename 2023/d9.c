#include "common.h"

i32 all_zeroes(i64 *arr)
{
    for (size_t i = 0; i < arrlen(arr); i++) {
        if (arr[i] != 0)
            return false;
    }
    return true;
}

i64 find_next_number(i64 *arr)
{
    i64 *diff = NULL;

    for (i64 i = 1; i < arrlen(arr); i++) {
        arrput(diff, arr[i] - arr[i - 1]);
    }

    i64 ans;

    if (all_zeroes(diff)) {
        ans = arr[0];
    } else {
        ans = arr[arrlen(arr) - 1] + find_next_number(diff);
    }

    arrfree(diff);

    return ans;
}

void p1()
{
    i64 ans = 0;
    char buf[1024] = {0};

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        i64 *arr = find_all_i64s(buf);
        ans += find_next_number(arr);
        arrfree(arr);
    }

    printf("p1: %ld\n", ans);
}

i64 find_prev_number(i64 *arr)
{
    i64 *diff = NULL;

    for (i64 i = 1; i < arrlen(arr); i++) {
        arrput(diff, arr[i] - arr[i - 1]);
    }

    i64 ans;

    if (all_zeroes(diff)) {
        ans = arr[0];
    } else {
        ans = arr[0] - find_prev_number(diff);
    }

    arrfree(diff);

    return ans;
}

void p2()
{
    i64 ans = 0;
    char buf[1024] = {0};

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        i64 *arr = find_all_i64s(buf);
        ans += find_prev_number(arr);
        arrfree(arr);
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
