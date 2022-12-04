#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#define MAXCOOKIES   32
#define MAXTEASPOONS 5

struct cookie_t {
	int capacity;
	int durability;
	int flavor;
	int texture;
	int calories;
};

struct cookie_t cookies[32];
size_t cookies_len = 0;

int teaspoons[MAXTEASPOONS];
size_t teaspoons_len = 0;

int score = INT_MIN;

int getscore(int start)
{
	if (teaspoons_len - start != cookies_len)
		return INT_MIN;

	struct cookie_t tmp = {0};
	for (int i = 0, j = start; j < teaspoons_len; i++, j++) {
		tmp.capacity += cookies[i].capacity * teaspoons[j];
		tmp.durability += cookies[i].durability * teaspoons[j];
		tmp.flavor += cookies[i].flavor * teaspoons[j];
		tmp.texture += cookies[i].texture * teaspoons[j];
		// tmp.calories += cookies[i].calories * teaspoons[i];
	}

	if (tmp.capacity <= 0)
		return 0;
	if (tmp.durability <= 0)
		return 0;
	if (tmp.flavor <= 0)
		return 0;
	if (tmp.texture <= 0)
		return 0;
	// if (tmp.calories <= 0)
		// return 0;

	int tscore = tmp.capacity * tmp.durability * tmp.flavor * tmp.texture;
	if (score < tscore)
		tscore = score;
	return tscore;
}

void printteaspoons()
{
	printf("teaspoons ");
	for (int i = 0; i < teaspoons_len; i++)
		printf("%d%s", teaspoons[i], teaspoons_len - 1 == i ? "\n" : " ");
}

int recurse(int target, int curr, int start)
{
	int score = INT_MIN;

	printf("recursing curr %d start %d teaspoons_len %ld\n", curr, start, teaspoons_len);

	if (target == curr) {
		printteaspoons();
		score = getscore(start);
	}

	for (int i = start; i < target; i++) {
		int tsum = curr + 1;
		if (tsum <= target) {
			teaspoons[teaspoons_len++] = i;
			int iscore = recurse(target, tsum, i);
			if (iscore > score)
				score = iscore;
			teaspoons[teaspoons_len--] = 0;
		} else {
			break;
		}
	}

	return score; // ?
}

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[32] = {0};
	char *s;
	int i;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		cookies[cookies_len].capacity = atoi(tokens[2]);
		cookies[cookies_len].durability = atoi(tokens[4]);
		cookies[cookies_len].flavor = atoi(tokens[6]);
		cookies[cookies_len].texture = atoi(tokens[8]);
		cookies[cookies_len].calories = atoi(tokens[10]);
		cookies_len++;
	}

	recurse(MAXTEASPOONS, 0, 1);

	printf("score %d\n", score);

	return 0;
}
