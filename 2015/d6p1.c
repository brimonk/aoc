#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DIMENSION 1000

int lights[DIMENSION][DIMENSION];

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

void flipem(int x0, int y0, int x1, int y1, int ison)
{
	for (int j = y0; j <= y1; j++) {
		for (int i = x0; i <= x1; i++) {
			switch (ison) {
				case OPERATION_OFF:
					lights[j][i] = 0;
					break;
				case OPERATION_ON:
					lights[j][i] = 1;
					break;
				case OPERATION_TOGGLE:
					lights[j][i] = !lights[j][i];
					break;
			}
		}
	}
}

int main(int argc, char **argv)
{
	int x0, y0, x1, y1;
	int rc;
	int oncount = 0;
	int ison;
	char buf[512];

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (int i = 0; i < OPERATION_TOTAL; i++) {
			rc = sscanf(buf, FORMATS[i], &x0, &y0, &x1, &y1);
			ison = i;
			if (rc == 4)
				break;
		}

		flipem(x0, y0, x1, y1, ison);
	}

	for (int j = 0; j < DIMENSION; j++)
		for (int i = 0; i < DIMENSION; i++)
			if (lights[j][i])
				oncount++;

	printf("lights on %d\n", oncount);

	return 0;
}
