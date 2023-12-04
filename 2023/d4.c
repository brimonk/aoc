#include "common.h"

void p1()
{
    int ans = 0;
	char buf[1024];

	memset(buf, 0, sizeof buf);

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = strchr(buf, ':');
        s += 2;

        int winners[100] = {0};
        size_t winners_len = 0;

        char *win_s = s;
        char *hav_s = strchr(win_s, '|');
        *hav_s = 0;
        hav_s++;

        int score = 0;

        for (char *t = strtok(win_s, " "); t; t = strtok(NULL, " ")) {
            winners[winners_len++] = atoi(t);
        }

        for (char *t = strtok(hav_s, " "); t; t = strtok(NULL, " ")) {
            int num = atoi(t);

            // check if it's in winners
            for (int i = 0; i < winners_len; i++) {
                if (num == winners[i]) {
                    if (score == 0) {
                        score = 1;
                    } else {
                        score *= 2;
                    }
                }
            }
        }

        // fprintf(stderr, "\tscore: %d\n", score);

        ans += score;
    }

    printf("p1: %d\n", ans);
}

void p2()
{
    int ans = 0;
	char buf[1024];

	memset(buf, 0, sizeof buf);

    int card_instances[300] = {0};

    card_instances[0] = 1;

    for (int i = 0; i < 300; i++) {
        card_instances[i] = 1;
    }

    int card;

    for (card = 1; buf == bfgets(buf, sizeof buf, stdin); card++) {
        char *s = strchr(buf, ':');
        s += 2;

        int winners[100] = {0};
        size_t winners_len = 0;

        char *win_s = s;
        char *hav_s = strchr(win_s, '|');
        *hav_s = 0;
        hav_s++;

        int winner_cnt = 0;

        for (char *t = strtok(win_s, " "); t; t = strtok(NULL, " ")) {
            winners[winners_len++] = atoi(t);
        }

        for (char *t = strtok(hav_s, " "); t; t = strtok(NULL, " ")) {
            int num = atoi(t);

            // check if it's in winners
            for (int i = 0; i < winners_len; i++) {
                if (num == winners[i]) {
                    winner_cnt++;
                }
            }
        }

        int copies = card_instances[card];

        // add 1 to to the next card instances
        for (int j = 0; j < copies; j++) {
            int matches = winner_cnt;
            for (int k = card + 1; matches > 0; k++, matches--) {
                card_instances[k]++;
            }
        }
    }

    for (int i = 1; i < 300 && i < card; i++) {
        // fprintf(stderr, "\t%d instances of %d\n", card_instances[i], i);
        ans += card_instances[i];
    }

    printf("p2: %d\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
