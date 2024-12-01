#include "common.h"

// . - operational
// # - damaged
// ? - unknown

// does not accept unknown - we brute force with this
int check_record_match(char *record, i32 *contiguous)
{
	int curr = 0;

	assert(strchr(record, '?') == NULL);

	// The current algorithm will scan for '#' (damaged) runs, and determine if the 'curr' index
	// of the 'contiguous' array fits the current run. If it doesn't, then we reject the string. If
	// it does, then we continue until we run out of record string.

	// printf("TESTING: %s\t", record);

	char *s = record;

	while (s && *s && curr < arrlen(contiguous)) {
		char *t = strchr(s, '#');
		if (t == NULL) {
			break;
		}

		char *e = strchr(t, '.');
		if (e == NULL) { // find the end of the run regardless of string length
			e = t + strlen(t);
		}

		if (contiguous[curr] == e - t) { // it's good
			curr++;
		} else {
			// printf("FAIL (damaged length incorrect)\n");
			return false;
		}

		// update 's' so we keep scanning the string
		s = e;
	}

	if (curr == arrlen(contiguous)) {
		// printf("PASS\n");
		return true;
	} else {
		// printf("FAIL (insufficient damaged sections)\n");
		return false;
	}
}

i32 count_arrangments(char *record, i32 *contiguous)
{
	i32 arrangments = 0;
	char *s = strchr(record, '?');

	if (s) {
		char *t = record;
		*s = '.';
		arrangments += count_arrangments(t, contiguous);

		*s = '#';
		arrangments += count_arrangments(t, contiguous);

		*s = '?';
	} else {
		arrangments += check_record_match(record, contiguous);
	}

	return arrangments;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		autofreearr i32 *contiguous = NULL;
		char *record = lines[i];
		char *s = strchr(record, ' ');
		assert(s);
		*s = 0;
		s++;

		for (s = strtok(s, ","); s; s = strtok(NULL, ",")) {
			arrput(contiguous, atoi(s));
		}

		i64 z = count_arrangments(record, contiguous);

#if 0
		printf("TESTING: %s\t", record);
		for (int i = 0; i < arrlen(contiguous); i++)
			printf("%d%s", contiguous[i], i == arrlen(contiguous) - 1 ? "" : ",");
		printf("\n");

		printf("arrangments: %ld\n", z);
#endif

		ans += z;
	}

    printf("p1: %ld\n", ans);
}

char *unfold(char *input)
{
	char *p1 = input;
	char *p2 = strchr(input, ' ');
	*p2 = 0;
	p2++;

	char *str = NULL;
	size_t len = 0;

	FILE *fp = open_memstream(&str, &len);

	fprintf(fp, "%s?", p1);
	fprintf(fp, "%s?", p1);
	fprintf(fp, "%s?", p1);
	fprintf(fp, "%s?", p1);
	fprintf(fp, "%s ", p1);

	fprintf(fp, "%s,", p2);
	fprintf(fp, "%s,", p2);
	fprintf(fp, "%s,", p2);
	fprintf(fp, "%s,", p2);
	fprintf(fp, "%s",  p2);

	fclose(fp);

	return str;
}

typedef struct Cache {
	char *key;
	i64 value;
} Cache;

i64 count2(char *record, i32 i, i32 j, i32 len, i32 *contiguous, Cache **cache)
{
	if (j == arrlen(contiguous) || (j == arrlen(contiguous) - 1 && contiguous[j] == len)) {
		return (strlen(record) == i || strchr(record + i, '#') == NULL) ? 1 : 0;
	}

	if (i == strlen(record)) {
		return 0;
	}

	char key[128] = {0};
	snprintf(key, sizeof key, "%d-%d-%d", i, len, j);
	if (shgeti(*cache, key) != -1) {
		return shget(*cache, key);
	}

	i64 res = 0;

	if (len == contiguous[j] && (record[i] == '.' || record[i] == '?')) {
		res = count2(record, i + 1, j + 1, 0, contiguous, cache);
	} else if (len == 0) {
		if (record[i] == '?') {
			i64 c1 = count2(record, i + 1, j, 1, contiguous, cache);
			i64 c2 = count2(record, i + 1, j, 0, contiguous, cache);
			res = c1 + c2;
		} else if (record[i] == '#') {
			res = count2(record, i + 1, j, 1, contiguous, cache);
		} else {
			res = count2(record, i + 1, j, 0, contiguous, cache);
		}
	} else if (record[i] == '#' || record[i] == '?') {
		res = count2(record, i + 1, j, len + 1, contiguous, cache);
	}

	shput(*cache, key, res);
	return res;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		autofreearr i32 *contiguous = NULL;

		autofree char *record = unfold(lines[i]);
		char *s = strchr(record, ' ');
		assert(s);
		*s = 0;
		s++;

		for (s = strtok(s, ","); s; s = strtok(NULL, ",")) {
			arrput(contiguous, atoi(s));
		}

		Cache *cache = NULL;
		sh_new_strdup(cache);

		i64 z = count2(record, 0, 0, 0, contiguous, &cache);

		shfree(cache);

#if 0
		printf("TESTING: %s\t", record);
		for (int i = 0; i < arrlen(contiguous); i++)
			printf("%d%s", contiguous[i], i == arrlen(contiguous) - 1 ? "" : ",");
		printf("\n");

		printf("arrangments: %ld\n", z);
#endif

		ans += z;
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
