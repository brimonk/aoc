#include "common.h"

// We do like, N^rules complexity here - no interesting data structures - loops go brrr

typedef struct OrderingRule {
	int p1, p2;
} OrderingRule;

int is_print_order_valid(OrderingRule *rules, i32 p1, i32 p2)
{
	for (i32 i = 0; i < arrlen(rules); i++) {
		// check for rules that would INVALIDATE this ordering
		if (rules[i].p2 == p1 && rules[i].p1 == p2) {
			return false;
		}
	}
	return true;
}

i32 *local_find_all_i32s(char *s)
{
    i32 *arr = NULL;
	char *v = strdup(s);
	for (char *t = strtok(v, ","); t; t = strtok(NULL, ",")) {
        arrput(arr, atoi(t));
	}
	free(v);
    return arr;
}


void p1()
{
    i64 ans = 0;

	autofreearr OrderingRule *rules = NULL;

	autofreelines char **lines = read_all_lines();
	int parsing_rules = true;

	for (i32 i = 0; i < arrlen(lines); i++) {
		if (strlen(lines[i]) == 0) {
			parsing_rules = false;
			continue;
		}

		if (parsing_rules) {
			i32 a, b;
			int rc = sscanf(lines[i], "%d|%d", &a, &b);
			assert(rc == 2);
			OrderingRule z = { .p1 = a, .p2 = b };
			arrput(rules, z);
		} else {
			autofreearr i32 *pages = local_find_all_i32s(lines[i]);
			int is_valid = true;
			for (i32 j = 0; j < arrlen(pages) && is_valid; j++) {
				for (i32 k = j + 1; k < arrlen(pages) && is_valid; k++) {
					if (!is_print_order_valid(rules, pages[j], pages[k])) {
						is_valid = false;
					}
				}
			}
			if (is_valid) {
				ans += pages[arrlen(pages) / 2];
			}
		}
	}

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;

	autofreearr OrderingRule *rules = NULL;

	autofreelines char **lines = read_all_lines();
	int parsing_rules = true;

	for (i32 i = 0; i < arrlen(lines); i++) {
		if (strlen(lines[i]) == 0) {
			parsing_rules = false;
			continue;
		}

		if (parsing_rules) {
			i32 a, b;
			int rc = sscanf(lines[i], "%d|%d", &a, &b);
			assert(rc == 2);
			OrderingRule z = { .p1 = a, .p2 = b };
			arrput(rules, z);
		} else {
			autofreearr i32 *pages = local_find_all_i32s(lines[i]);

			// I'm going to try just swapping the values, and we're going to see where we get.

			int is_valid = true;

			for (i32 j = 0; j < arrlen(pages); j++) {
				for (i32 k = j + 1; k < arrlen(pages); k++) {
					if (!is_print_order_valid(rules, pages[j], pages[k])) {
						is_valid = false;
						i32 tmp = pages[j];
						pages[j] = pages[k];
						pages[k] = tmp;
					}
				}
			}

			if (!is_valid) {
				ans += pages[arrlen(pages) / 2];
			}
		}
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
