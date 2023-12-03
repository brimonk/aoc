#include "common.h"

#define MIN3(A, B, C)  (MIN(MIN((A), (B)), MIN((B), (C))))

void p1()
{
	long squarefeet = 0;
	long l, w, h, s;
	long a1, a2, a3;
	char buf[1024] = {0};

	while (buf == fgets(buf, sizeof buf, stdin)) {
		sscanf(buf, "%ldx%ldx%ld", &l, &w, &h);
		a1 = l * w;
		a2 = w * h;
		a3 = h * l;
		s = MIN3(a1, a2, a3);
		squarefeet += (2 * a1) + (2 * a2) + (2 * a3) + s;
	}

	printf("p1: %ld\n", squarefeet);
}

void p2()
{
	long squarefeet = 0;
	long l, w, h, s;
	long p1, p2, p3;
	char buf[1024] = {0};

	while (buf == fgets(buf, sizeof buf, stdin)) {
		sscanf(buf, "%ldx%ldx%ld", &l, &w, &h);
		p1 = 2 * l + 2 * w;
		p2 = 2 * w + 2 * h;
		p3 = 2 * h + 2 * l;
		s = MIN3(p1, p2, p3);
		squarefeet += (l * w * h) + s;
	}

	printf("p2: %ld\n", squarefeet);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
