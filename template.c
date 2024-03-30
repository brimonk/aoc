#include "common.h"

void p1()
{
    i64 ans = 0;

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
