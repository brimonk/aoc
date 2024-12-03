#include "common.h"

void p1()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	for (i32 i = 0; i < arrlen(lines); i++) {
		char *s = lines[i];
		while (*s) {
			int x = 0, y = 0;

			if (*s++ == 'm') {
				if (*s++ == 'u') {
					if (*s++ == 'l') {
						if (*s++ == '(') {
							while (isdigit(*s)) {
								x = (x * 10) + (*s - '0');
								s++;
							}
							if (*s++ != ',') {
								goto terminate;
							}
							while (isdigit(*s)) {
								y = (y * 10) + (*s - '0');
								s++;
							}
							if (*s++ == ')') {
								ans += x * y;
							}
						}
					}
				}
			}

			terminate:
			continue;
		}
	}

    printf("p1: %ld\n", ans);
}

void p2()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	int mul_enabled = true;

	for (i32 i = 0; i < arrlen(lines); i++) {
		char *s = lines[i];
		while (*s) {
			int x = 0, y = 0;

			if (*s == 'm') {
				s++;
				if (*s++ == 'u') {
					if (*s++ == 'l') {
						if (*s++ == '(') {
							while (isdigit(*s)) {
								x = (x * 10) + (*s - '0');
								s++;
							}
							if (*s++ != ',') {
								continue;
							}
							while (isdigit(*s)) {
								y = (y * 10) + (*s - '0');
								s++;
							}
							if (*s++ == ')') {
								if (mul_enabled)
									ans += x * y;
							}
						}
					}
				}
			} else if (*s == 'd') {
				s++;
				if (*s++ == 'o') {
					if (*s == 'n') {
						s++;
						if (*s++ == '\'') {
							if (*s++ == 't') {
								if (*s++ == '(') {
									if (*s++ == ')') {
										mul_enabled = false;
									}
								}
							}
						}
					} else if (*s == '(') {
						s++;
						if (*s++ == ')') {
							mul_enabled = true;
						}
					} else {
						continue;
					}
				}
			} else {
				s++;
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
