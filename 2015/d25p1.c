#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define MAXDIMS 4096

#if 0
#define TARGET_ROW 2981
#define TARGET_COL 3075
#else
#define TARGET_ROW 10
#define TARGET_COL 10
#endif

// col x row
int grid[MAXDIMS][MAXDIMS] = {0};

int main(int argc, char **argv)
{
	int i;
	int row, col;

	row = 0;
	col = 0;

	grid[0][0] = 1;

	printf("grid[4][4] = %d\n", grid[4 - 1][4 -1]);

	return 0;
}
