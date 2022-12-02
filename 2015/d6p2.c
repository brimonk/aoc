#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DIMENSION 1000

long lights[DIMENSION][DIMENSION];

enum {
	OPERATION_OFF,
	OPERATION_ON,
	OPERATION_TOGGLE,
	OPERATION_TOTAL
};

char *FORMATS[] = {
	"turn off %d,%d through %d,%d",
	"turn on %d,%d through %d,%d",
	"toggle %d,%d through %d,%d",
};

void flipem(int x0, int y0, int x1, int y1, int op)
{
	for (int j = y0; j <= y1; j++) {
		for (int i = x0; i <= x1; i++) {
			switch (op) {
				case OPERATION_OFF: {
					if (lights[j][i] > 0)
						lights[j][i]--;
					break;
				}
				case OPERATION_ON:
					lights[j][i]++;
					break;
				case OPERATION_TOGGLE:
					lights[j][i] += 2;
					break;
			}
		}
	}
}

int main(int argc, char **argv)
{
	int x0, y0, x1, y1;
	int rc;
	int brightness = 0;
	int op;
	char buf[512];

	memset(lights, 0, sizeof lights);

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (int i = 0; i < OPERATION_TOTAL; i++) {
			rc = sscanf(buf, FORMATS[i], &x0, &y0, &x1, &y1);
			op = i;
			if (rc == 4)
				break;
		}

		assert(rc == 4);

		assert(x0 <= x1);
		assert(y0 <= y1);

		flipem(x0, y0, x1, y1, op);
	}

	for (int j = 0; j < DIMENSION; j++)
		for (int i = 0; i < DIMENSION; i++)
			brightness += lights[j][i];

	printf("total brightness %d\n", brightness);

	return 0;
}
