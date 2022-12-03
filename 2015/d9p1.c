#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define MAXCITIES (1 << 10)

char *CITIES[MAXCITIES] = {0};
size_t CITIES_LEN = 0;
int WEIGHTS[MAXCITIES][MAXCITIES] = {0};

int DIST[MAXCITIES];
int PREV[MAXCITIES];

struct queue_t *QUEUE;

struct queue_t {
	struct queue_t *next;
	int v;
};

int getcity(char *s)
{
	int i;
	for (i = 0; i < CITIES_LEN; i++)
		if (strcmp(CITIES[i], s) == 0)
			return i;
	assert(CITIES_LEN < MAXCITIES);
	CITIES[CITIES_LEN++] = strdup(s);
	return CITIES_LEN - 1;
}

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[8];
	char *s;
	int i;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		int c1 = getcity(tokens[0]);
		int c2 = getcity(tokens[2]);
		int cost = atoi(tokens[4]);

		WEIGHTS[c1][c2] = cost;
		WEIGHTS[c2][c1] = cost;
	}

	// NOTE (Brian) do Dijkstra's for each starting vertex (city) to find the min distance

#if 0

	// init for dijkstra's
	for (i = 0; i < CITIES_LEN; i++) {
		DIST[i] = INT_MAX;
		PREV[i] = -1;
		enqueue(i);
	}

	DIST[0] = 0;

	while (QUEUE != NULL) {
		struct queue_t *u = dequeue();
	}
#endif

	for (i = 0; i < CITIES_LEN; i++)
		free(CITIES[i]);

	return 0;
}
