#include "common.h"

void p1()
{
	char buf[1024];

	memset(buf, 0, sizeof buf);

    int game_id_sum = 0;

	for (int game = 1; buf == fgets(buf, sizeof buf, stdin); game++) {
		// buf[strlen(buf) - 1] = 0;

        // fprintf(stderr, "%s\n", buf);
        // fprintf(stderr, "%s", buf);

        int b = 0;
        int r = 0;
        int g = 0;

        int count = 0;

        int game_good = true;

        for (char *s = strchr(buf, ':') + 1; *s; s++) {
            if (isblank(*s) || *s == ',') {
                continue;
            } else if (*s == ';' || *s == '\n') {
                if (r > 12 || g > 13 || b > 14) {
                    game_good = false;
                    break;
                }
                r = 0;
                b = 0;
                g = 0;
            } else if (isdigit(*s)) {
                count = atoi(s);
                while (isdigit(*s)) // skip through the other digits
                    s++;
            } else {
                switch (*s) {
                    case 'r':
                        r += count;
                        break;
                    case 'b':
                        b += count;
                        break;
                    case 'g':
                        g += count;
                        break;
                    default:
                        printf("%s\n", s);
                        assert(0);
                }

                while (isalpha(*s) && *s != '\0') // skip through the other junk
                    s++;
                s--;
            }
        }

        if (game_good) {
            game_id_sum += game;
        }

        // fprintf(stderr, "\t%s\n", game_good ? "good" : "bad");

        // fprintf(stderr, "\t%s: %d, %s: %d, %s: %d\n", "red", r, "green", g, "blue", b);
	}

    printf("p1: %d\n", game_id_sum);
}

void p2()
{
	char buf[1024];

	memset(buf, 0, sizeof buf);

    int power_sum = 0;

	for (int game = 1; buf == fgets(buf, sizeof buf, stdin); game++) {
		// buf[strlen(buf) - 1] = 0;

        // fprintf(stderr, "%s\n", buf);
        // fprintf(stderr, "%s", buf);

        int min_b = 0;
        int min_r = 0;
        int min_g = 0;

        int b = 0;
        int r = 0;
        int g = 0;

        int count = 0;

        for (char *s = strchr(buf, ':') + 1; *s; s++) {
            if (isblank(*s) || *s == ',') {
                continue;
            } else if (*s == ';' || *s == '\n') {
                min_b = MAX(min_b, b);
                min_r = MAX(min_r, r);
                min_g = MAX(min_g, g);
                r = 0;
                b = 0;
                g = 0;
            } else if (isdigit(*s)) {
                count = atoi(s);
                while (isdigit(*s)) // skip through the other digits
                    s++;
            } else {
                switch (*s) {
                    case 'r':
                        r += count;
                        break;
                    case 'b':
                        b += count;
                        break;
                    case 'g':
                        g += count;
                        break;
                    default:
                        printf("%s\n", s);
                        assert(0);
                }

                while (isalpha(*s) && *s != '\0') // skip through the other junk
                    s++;
                s--;
            }
        }

        int power_set = min_b * min_r * min_g;

        // fprintf(stderr, "\t%d\n", power_set);

        power_sum += power_set;
	}

    printf("p2: %d\n", power_sum);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
