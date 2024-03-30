#include "common.h"

typedef struct Ingredient {
	i64 capacity;
	i64 durability;
	i64 flavor;
	i64 texture;
	i64 calories;
} Ingredient;

i32 arrsum(i32 *arr)
{
	i32 sum = 0;
	for (i32 i = 0; i < arrlen(arr); i++) {
		sum += arr[i];
	}
	return sum;
}

void permute(i32 start, i32 curr, i32 end, i32 lim, i32 teaspoons, i32 **vals, Ingredient *ingredients, i64 *ans)
{
	if (curr == lim && lim == arrlen(*vals)) {
		if (arrsum(*vals) != teaspoons)
			return;

		for (i32 j = 0; j < arrlen(*vals); j++)
			fprintf(stderr, "%d%s", (*vals)[j], j < lim - 1 ? " " : "");
		fprintf(stderr, "\n");

		Ingredient totals = { 0 };

		for (i32 j = 0; j < arrlen(*vals); j++) {
			totals.capacity += ingredients[j].capacity * (*vals)[j];
			totals.durability += ingredients[j].durability * (*vals)[j];
			totals.flavor += ingredients[j].flavor * (*vals)[j];
			totals.texture += ingredients[j].texture * (*vals)[j];
		}

		if (totals.capacity < 0 || totals.durability < 0 || totals.flavor < 0 || totals.texture < 0) {
			return;
		}

		i64 total = totals.capacity * totals.durability * totals.flavor * totals.texture;

		if (*ans < total) {
			*ans = total;
		}

		return;
	}

	for (i32 i = start; i <= end; i++) {
		arrput(*vals, i);
		permute(start, curr + 1, end, lim, teaspoons, vals, ingredients, ans);
		arrpop(*vals);
	}
}

void p1()
{
    i64 ans = 0;
	char buf[1024];

	Ingredient *ingredients = NULL;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		char **strs = find_all_strs_sep(buf, ": ,");

		Ingredient ing = {
			.capacity = atoi(strs[2]),
			.durability = atoi(strs[4]),
			.flavor = atoi(strs[6]),
			.texture = atoi(strs[8]),
			.calories = atoi(strs[10]),
		};

		arrput(ingredients, ing);

		arrfree(strs);
	}

	i32 *vals = NULL;
	permute(1, 0, 100, arrlen(ingredients), 100, &vals, ingredients, &ans);
	arrfree(vals);

    printf("p1: %ld\n", ans);

	arrfree(ingredients);
}

void permute2(i32 start, i32 curr, i32 end, i32 lim, i32 teaspoons, i32 **vals, Ingredient *ingredients, i64 *ans)
{
	if (curr == lim && lim == arrlen(*vals)) {
		if (arrsum(*vals) != teaspoons)
			return;

		for (i32 j = 0; j < arrlen(*vals); j++)
			fprintf(stderr, "%d%s", (*vals)[j], j < lim - 1 ? " " : "");
		fprintf(stderr, "\n");

		Ingredient totals = { 0 };

		for (i32 j = 0; j < arrlen(*vals); j++) {
			totals.capacity += ingredients[j].capacity * (*vals)[j];
			totals.durability += ingredients[j].durability * (*vals)[j];
			totals.flavor += ingredients[j].flavor * (*vals)[j];
			totals.texture += ingredients[j].texture * (*vals)[j];
			totals.calories += ingredients[j].calories * (*vals)[j];
		}

		if (totals.capacity < 0 || totals.durability < 0 || totals.flavor < 0 || totals.texture < 0 || totals.calories != 500) {
			return;
		}

		i64 total = totals.capacity * totals.durability * totals.flavor * totals.texture;

		if (*ans < total) {
			*ans = total;
		}

		return;
	}

	for (i32 i = start; i <= end; i++) {
		arrput(*vals, i);
		permute2(start, curr + 1, end, lim, teaspoons, vals, ingredients, ans);
		arrpop(*vals);
	}
}

void p2()
{
    i64 ans = 0;
	char buf[1024];

	Ingredient *ingredients = NULL;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		char **strs = find_all_strs_sep(buf, ": ,");

		Ingredient ing = {
			.capacity = atoi(strs[2]),
			.durability = atoi(strs[4]),
			.flavor = atoi(strs[6]),
			.texture = atoi(strs[8]),
			.calories = atoi(strs[10]),
		};

		arrput(ingredients, ing);

		arrfree(strs);
	}

	// ans = get_max_score(ingredients, 100);
	i32 *vals = NULL;
	permute2(1, 0, 100, arrlen(ingredients), 100, &vals, ingredients, &ans);
	arrfree(vals);

    printf("p2: %ld\n", ans);

	arrfree(ingredients);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
