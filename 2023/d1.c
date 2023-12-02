#include "common.h"

void p1()
{
    int sum = 0;
	char buf[1024];

	memset(buf, 0, sizeof buf);

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

        int d1 = 0;
        int d2 = 0;

        // find first
        for (int i = 0; i < strlen(buf); i++) {
            if (isdigit(buf[i])) {
                d1 = buf[i] - '0';
                break;
            }
        }

        for (int i = strlen(buf) - 1; i >= 0; i--) {
            if (isdigit(buf[i])) {
                d2 = buf[i] - '0';
                break;
            }
        }

        int v = d1 * 10 + d2;
        // fprintf(stderr, "%s\n\t%d\n", buf, v);
        sum += v;
	}

	printf("p1: %d\n", sum);
}

int is_digit_word(char *s)
{
    char *digit_words[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    size_t len = strlen(s);

    for (size_t i = 0; i < 10; i++) {
        if (len < strlen(digit_words[i])) {
            continue;
        }

        if (strncmp(s, digit_words[i], MIN(len, strlen(digit_words[i]))) == 0) {
            // fprintf(stderr, "found '%s'\n", digit_words[i]);
            return i;
        }
    }

    return -1;
}

void p2()
{
    int sum = 0;
	char buf[1024];

	memset(buf, 0, sizeof buf);

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

        int d1 = 0;
        int d2 = 0;

        // find first
        for (int i = 0; i < strlen(buf); i++) {
            int dword = is_digit_word(buf + i);
            if (dword != -1) {
                d1 = dword;
                break;
            } else if (isdigit(buf[i])) {
                d1 = buf[i] - '0';
                break;
            }
        }

        for (int i = strlen(buf) - 1; i >= 0; i--) {
            int dword = is_digit_word(buf + i);
            if (dword != -1) {
                d2 = dword;
                break;
            } else if (isdigit(buf[i])) {
                d2 = buf[i] - '0';
                break;
            }
        }

        int v = d1 * 10 + d2;
        // fprintf(stderr, "%s\n\t%d\n", buf, v);
        sum += v;
	}

	printf("p2: %d\n", sum);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
