#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define MAXSUES 1024

struct sue_t {
	// these are all of the fields for each sue
	int children;
	int cats;
	int samoyeds;
	int pomeranians;
	int akitas;
	int vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;

	// these are the working variables, so to speak
	int is_suspect;
};

struct sue_t aunties[MAXSUES] = {0};
size_t aunties_len = 0;

struct sue_t target =
{
	.children = 3,
	.cats = 7,
	.samoyeds = 2,
	.pomeranians = 3,
	.akitas = 0,
	.vizslas = 0,
	.goldfish = 5,
	.trees = 3,
	.cars = 2,
	.perfumes = 1
};

void parse_sue(char *tokens[32])
{
	memset(&aunties[aunties_len], 0xff, sizeof(aunties[aunties_len]));
	for (int i = 2; i < 32 && tokens[i]; i += 2) {
		if (strcmp(tokens[i], "children") == 0)
			aunties[aunties_len].children = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "cats") == 0)
			aunties[aunties_len].cats = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "samoyeds") == 0)
			aunties[aunties_len].samoyeds = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "pomeranians") == 0)
			aunties[aunties_len].pomeranians = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "akitas") == 0)
			aunties[aunties_len].akitas= atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "vizslas") == 0)
			aunties[aunties_len].vizslas = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "goldfish") == 0)
			aunties[aunties_len].goldfish = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "trees") == 0)
			aunties[aunties_len].trees = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "cars") == 0)
			aunties[aunties_len].cars = atoi(tokens[i + 1]);
		if (strcmp(tokens[i], "perfumes") == 0)
			aunties[aunties_len].perfumes = atoi(tokens[i + 1]);
	}
	aunties_len++;
}

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[32] = {0};
	char *s;
	int i;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " :,"); s; i++, s = strtok(NULL, " :,"))
			tokens[i] = s;
		tokens[i] = s;

		parse_sue(tokens);
	}

	for (i = 0; i < aunties_len; i++)
		aunties[i].is_suspect = 1;

	// Iterate through the entire list of aunties for everything in our list that's non-zero, and
	// whenever the number in our target is NONZERO and is NOT EQUAL, mark them as a non-suspect.
	//
	// We're just going to try this out, and see what happens. I have no idea if this approach will
	// really work.

	for (i = 0; i < aunties_len && target.children != 0; i++)
		if (aunties[i].is_suspect && aunties[i].children >= 0)
			if (target.children != aunties[i].children)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.cats != 0; i++)
		if (aunties[i].is_suspect && aunties[i].cats >= 0)
			if (target.cats >= aunties[i].cats)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.samoyeds != 0; i++)
		if (aunties[i].is_suspect && aunties[i].samoyeds >= 0)
			if (target.samoyeds != aunties[i].samoyeds)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.pomeranians != 0; i++)
		if (aunties[i].is_suspect && aunties[i].pomeranians >= 0)
			if (target.pomeranians <= aunties[i].pomeranians)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.akitas != 0; i++)
		if (aunties[i].is_suspect && aunties[i].akitas>= 0)
			if (target.akitas != aunties[i].akitas)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.vizslas != 0; i++)
		if (aunties[i].is_suspect && aunties[i].vizslas>= 0)
			if (target.vizslas != aunties[i].vizslas)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.goldfish != 0; i++)
		if (aunties[i].is_suspect && aunties[i].goldfish >= 0)
			if (target.goldfish <= aunties[i].goldfish)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.trees != 0; i++)
		if (aunties[i].is_suspect && aunties[i].trees >= 0)
			if (target.trees >= aunties[i].trees)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.cars != 0; i++)
		if (aunties[i].is_suspect && aunties[i].cars >= 0)
			if (target.cars != aunties[i].cars)
				aunties[i].is_suspect = 0;

	for (i = 0; i < aunties_len && target.perfumes != 0; i++)
		if (aunties[i].is_suspect && aunties[i].perfumes >= 0)
			if (target.perfumes != aunties[i].perfumes)
				aunties[i].is_suspect = 0;

	// Now, we'll print out the sues that are suspects (and hope there's only 1 in the end)
	for (i = 0; i < aunties_len; i++)
		if (aunties[i].is_suspect)
			printf("auntie %d\n", i + 1);

	return 0;
}
