#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(A, B)      ((A) < (B) ? (A) : (B))
#define MIN3(A, B, C)  (MIN(MIN((A), (B)), MIN((B), (C))))

int main(int argc, char **argv)
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

	printf("feet %ld\n", squarefeet);

	return 0;
}
