#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXCOORDS (1 << 20)

struct coord_t {
	int x, y;
};

// coordcmp : sorts in x, then y, lo to hi
int coordcmp(const void *a, const void *b)
{
	struct coord_t *ca = (void *)a;
	struct coord_t *cb = (void *)b;

	if (ca->x < cb->x)
		return -1;
	if (ca->x > cb->x)
		return 1;
	if (ca->y < cb->y)
		return -1;
	if (ca->y > cb->y)
		return 1;
	return 0;
}

int main(int argc, char **argv)
{
	int c;
	int i = 0;
	int x[2] = {0};
	int y[2] = {0};
	int len;
	int distinct = 0;
	struct coord_t *coords = calloc(MAXCOORDS, sizeof(*coords));

	coords[i].x = x[i % 2];
	coords[i].y = y[i % 2];
	i++;
	coords[i].x = x[i % 2];
	coords[i].y = y[i % 2];
	i++;

	while ((c = getchar()) != EOF) {
		switch (c) {
			case '^':
				y[i % 2]++;
				break;
			case '>':
				x[i % 2]++;
				break;
			case 'v':
				y[i % 2]--;
				break;
			case '<':
				x[i % 2]--;
				break;
			default: // newline or something
				continue;
		}

		coords[i].x = x[i % 2];
		coords[i].y = y[i % 2];

		assert(i < MAXCOORDS);
		i++;
	}

	len = i;

	qsort(coords, len, sizeof(*coords), coordcmp);

	struct coord_t *curr = coords + 0;
	distinct = 1;

	for (i = 0; i < len; i++) {
		if (curr->x != coords[i].x || curr->y != coords[i].y) {
			distinct++;
			curr = coords + i;
		}
	}

	printf("distinct coordinates %d\n", distinct);

	free(coords);

	return 0;
}
