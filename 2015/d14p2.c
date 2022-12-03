#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

struct reindeer_t {
	char *name;
	int fly_rate;
	int fly_duration;
	int rest_duration;
	int is_flying;
	int curr;
	int traveled;
	int points;
};

struct reindeer_t reindeer[32];
int reindeer_len = 0;

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[32] = {0};
	char *s;
	int i, j;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		reindeer[reindeer_len].name = strdup(tokens[0]);
		reindeer[reindeer_len].fly_rate = atoi(tokens[3]);
		reindeer[reindeer_len].fly_duration = atoi(tokens[6]);
		reindeer[reindeer_len].rest_duration = atoi(tokens[13]);

		reindeer[reindeer_len].is_flying = 1;

		reindeer_len++;
	}

	for (i = 0; i < 2503; i++) { // test sim for 1000 seconds
		for (j = 0; j < reindeer_len; j++) {
			struct reindeer_t *r = &reindeer[j];
			r->curr++;
			if (r->is_flying) {
				r->traveled += r->fly_rate;
				if (r->fly_duration == r->curr) {
					r->curr = 0;
					r->is_flying = 0;
				}
			} else {
				if (r->rest_duration == r->curr) {
					r->curr = 0;
					r->is_flying = 1;
				}
			}

#if 0
			if (j == 0) {
				printf("time %d, idx %d, %s\n", i, j, r->name);
				printf("\trate %d, fly duration %d, rest duration %d\n",
					r->fly_rate, r->fly_duration, r->rest_duration);
				printf("\t%s\n", r->is_flying ? "is flying" : "not flying");
				printf("\ttraveled %d, curr %d\n", r->traveled, r->curr);
			}
#endif
		}

		int maxd = INT_MIN;
		for (int k = 0; k < reindeer_len; k++)
			if (maxd < reindeer[k].traveled)
				maxd = reindeer[k].traveled;
		for (int k = 0; k < reindeer_len; k++)
			if (maxd == reindeer[k].traveled)
				reindeer[k].points++;
	}

	int maxp = INT_MIN;
	for (i = 0; i < reindeer_len; i++)
		if (maxp < reindeer[i].points)
			maxp = reindeer[i].points;
	printf("winner's points %d\n", maxp);

	for (i = 0; i < reindeer_len; i++)
		free(reindeer[i].name);

	return 0;
}
