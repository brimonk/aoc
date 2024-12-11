#include "common.h"

i32 number_length(i64 a)
{
	char z[64];
	snprintf(z, sizeof z, "%ld", a);
	return strlen(z);
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr i64 *stones = find_all_i64s(lines[0]);

	int digits;

	for (i32 i = 0; i < 25; i++) {
		i64 *next = NULL;

		for (i32 j = 0; j < arrlen(stones); j++) {
			if (stones[j] == 0) {
				arrput(next, 1);
			} else if ((digits = number_length(stones[j])) % 2 == 0) {
				i64 divisor = (i64)pow(10, digits / 2);
				i64 left = stones[j] / divisor;
				i64 right = stones[j] % divisor;
				arrput(next, left);
				arrput(next, right);
			} else {
				arrput(next, stones[j] * 2024);
			}
		}

		arrfree(stones);
		stones = next;
	}

	ans = arrlen(stones);

    printf("p1: %ld\n", ans);
}

typedef struct StoneKey {
	i64 stone;
	i64 iters;
} StoneKey;

typedef struct StoneValue {
	i64 count;
	i64 stones[2];
} StoneValue;

typedef struct StoneBlink {
	StoneKey key;
	StoneValue value;
} StoneBlink;

StoneValue GetStoneValue(StoneBlink **map, i64 stone, i64 iters)
{
	int digits;
	StoneValue sv = { 0 };

	StoneKey sk = { .stone = stone, .iters = iters };

	if (hmgeti(*map, sk) >= 0) {
		return hmget(*map, sk);
	}

	if (stone == 0) {
		sv.count = 1;
		sv.stones[0] = 1;
	} else if ((digits = number_length(stone)) % 2 == 0) {
		i64 divisor = (i64)pow(10, digits / 2);
		sv.count = 2;
		sv.stones[0] = stone / divisor;
		sv.stones[1] = stone % divisor;
	} else {
		sv.count = 1;
		sv.stones[0] = stone * 2024;
	}

	if (iters > 1) {
		if (sv.count == 2) {
			StoneValue a = GetStoneValue(map, sv.stones[0], iters - 1);
			StoneValue b = GetStoneValue(map, sv.stones[1], iters - 1);
			sv.count = a.count + b.count;
		} else {
			sv = GetStoneValue(map, sv.stones[0], iters - 1);
		}
	}

	hmput(*map, sk, sv);

	return sv;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();
	autofreearr i64 *stones = find_all_i64s(lines[0]);
	StoneBlink *map = NULL;

	// in part 2, because of the storage requirements of going to 75 for this one, we actually
	// just ask the same question repeatedly

	for (i32 i = 0; i < arrlen(stones); i++) {
		StoneValue curr = GetStoneValue(&map, stones[i], 75);
		printf("Stone %ld has a 'count' of %ld\n", stones[i], curr.count);
		ans += curr.count;
	}

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
