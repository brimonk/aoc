#include "common.h"

void p1()
{
    int ans;

    printf("p1: %d\n", ans);
}

void p2()
{
    int ans;

    printf("p2: %d\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
