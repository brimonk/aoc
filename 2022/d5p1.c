#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLEN 1024

int crates[32][MAXLEN] = {0};
int crates_sizes[32] = {0};
int stack_count = 0;

struct instruction_t {
	int number;
	int from;
	int to;
};

struct instruction_t instructions[MAXLEN];
size_t instructions_len;

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void printall()
{
	printf("PRINTALL\n");
	for (int i = 0; i < stack_count; i++) {
		printf("stack %d\n", i + 1);
		for (int j = 0; j < crates_sizes[i]; j++) {
			printf("\t%c\n", (char)crates[i][j]);
		}
	}
}

int pop(int stack)
{
	int crate = crates[stack][crates_sizes[stack] - 1];
	crates[stack][--crates_sizes[stack]] = 0;
	return crate;
}

void push(int stack, int val)
{
	assert(crates_sizes[stack] + 1 < MAXLEN);
	crates[stack][crates_sizes[stack]++] = val;
}

int main(int argc, char **argv)
{
	int len;
	char buf[512];
	int is_container;
	int is_instruction;
	char *s;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		len = strlen(buf);
		buf[strlen(buf) - 1] = 0;

		is_container = strchr(buf, '[') != NULL;
		is_instruction = strstr(buf, "move") != NULL;

		if (!stack_count)
			stack_count = len / 4;

		if (is_container) {
			for (s = strchr(buf, '['); s; s = strchr(s + 1, '[')) {
				int i = (s - buf) / 4;
				crates[i][crates_sizes[i]++] = *(s + 1);
			}
		} else if (is_instruction) {
			assert(instructions_len < MAXLEN);
			int rc = sscanf(strstr(buf, "move"), "move %d from %d to %d",
				&instructions[instructions_len].number,
				&instructions[instructions_len].from,
				&instructions[instructions_len].to);
			instructions[instructions_len].from--;
			instructions[instructions_len].to--;
			instructions_len++;
			assert(rc == 3);
		}
	}

	for (int i = 0; i < stack_count; i++) { // swap 'em
		for (int j = 0; j < crates_sizes[i] / 2; j++) {
			swap(&crates[i][j], &crates[i][crates_sizes[i] - 1 - j]);
		}
	}

	for (int i = 0; i < instructions_len; i++) {
		for (int j = 0; j < instructions[i].number; j++) {
			int val = pop(instructions[i].from);
			push(instructions[i].to, val);
			// printall();
		}
	}

	for (int i = 0; i < stack_count; i++)
		putchar((char)crates[i][crates_sizes[i] - 1]);
	putchar('\n');

	return 0;
}
