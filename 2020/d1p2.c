#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

#define EXPENSES (1 << 12)

int expenses[EXPENSES] = {0};
int expenses_len = 0;

int main(int argc, char **argv)
{
	while (1 == scanf("%d\n", &expenses[expenses_len++]))
		;

	for (int i = 0; i < expenses_len; i++) {
		for (int j = 0; j < expenses_len; j++) {
			for (int k = 0; k < expenses_len; k++) {
				if (i == j || j == k || i == k)
					continue;
				if (expenses[i] + expenses[j] + expenses[k] == 2020) {
					printf("answer %d\n", expenses[i] * expenses[j] * expenses[k]);
					goto END;
				}
			}
		}
	}

END:
	return 0;
}
