#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(A, B)      ((A) < (B) ? (A) : (B))
#define MIN3(A, B, C)  (MIN(MIN((A), (B)), MIN((B), (C))))

int main(int argc, char **argv)
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

	printf("square feet %ld\n", squarefeet);

	return 0;
}
