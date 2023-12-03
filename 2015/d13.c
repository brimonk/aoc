#include "common.h"

#define MAXPEOPLE (1 << 10)
#define MAXTOTALS (1 << 30)

char *people[MAXPEOPLE] = {0};
size_t people_len = 0;
int happy_delta[MAXPEOPLE][MAXPEOPLE];

int permutation[MAXPEOPLE] = {0};
int *totals = NULL;
int totals_len = 0;

int getperson(char *name)
{
	int i;
	for (i = 0; i < people_len; i++)
		if (strcmp(people[i], name) == 0)
			return i;
	people[i] = strdup(name);
	return people_len++;
}

void addconnection(char *n1, char *n2, int units)
{
	assert(people_len < MAXPEOPLE);
	int p1 = getperson(n1);
	int p2 = getperson(n2);
	happy_delta[p1][p2] = units;
}

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void compute_happiness()
{
	assert(totals_len < MAXTOTALS);

	int i, sum;

	for (i = sum = 0; i < people_len; i++) {
		int d1 = happy_delta[permutation[(i + 0) % people_len]][permutation[(i + 1) % people_len]];
		int d2 = happy_delta[permutation[(i + 1) % people_len]][permutation[(i + 0) % people_len]];
		sum += d1 + d2;
	}

	totals[totals_len++] = sum;
}

// permute : continually permutes the input order, storing totals for given iter in 'totals'
void permute(int *a, int lo, int hi)
{
	int i;
	if (lo == hi)
		return;

	compute_happiness(); // I think we do this here?

	for (i = lo; i <= hi; i++) {
		swap((a + lo), (a + hi));
		permute(a, lo + 1, hi);
		swap((a + lo), (a + i)); // backtrack
	}
}

void p1()
{
	char buf[512];
	char *tokens[32] = {0};
	char *s;
	int i;

	totals = calloc(MAXTOTALS, sizeof(*totals));

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		(*strchr(tokens[10], '.')) = 0;

		int units = atoi(tokens[3]) * (strcmp(tokens[2], "lose") == 0 ? -1 : 1);

		addconnection(tokens[0], tokens[10], units);
	}

	// build up all possible orders of people around the table (into a linked list)
	for (i = 0; i < people_len; i++)
		permutation[i] = i;

	permute(permutation, 0, people_len - 1);

	int max = INT_MIN;
	for (i = 0; i < totals_len; i++)
		if (max < totals[i])
			max = totals[i];

	printf("p1: %d\n", max);

	for (i = 0; i < people_len; i++)
		free(people[i]);
	free(totals);
}

void p2()
{
	char buf[512];
	char *tokens[32] = {0};
	char *s;
	int i;

	totals = calloc(MAXTOTALS, sizeof(*totals));

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		(*strchr(tokens[10], '.')) = 0;

		int units = atoi(tokens[3]) * (strcmp(tokens[2], "lose") == 0 ? -1 : 1);

		addconnection(tokens[0], tokens[10], units);
	}

#if 1
	int lenstore = people_len;
	for (i = 0; i < lenstore; i++) {
		addconnection("me", people[i], 0);
		addconnection(people[i], "me", 0);
	}
#endif

	// build up all possible orders of people around the table (into a linked list)
	for (i = 0; i < people_len; i++)
		permutation[i] = i;

	permute(permutation, 0, people_len - 1);

	int max = INT_MIN;
	for (i = 0; i < totals_len; i++)
		if (max < totals[i])
			max = totals[i];

	printf("p2: %d\n", max);

	for (i = 0; i < people_len; i++)
		free(people[i]);
	free(totals);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
