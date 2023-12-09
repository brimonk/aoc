#include "common.h"

enum {
    HANDKIND_HI,
    HANDKIND_ONE,
    HANDKIND_TWO,
    HANDKIND_THREE,
    HANDKIND_FULL,
    HANDKIND_FOUR,
    HANDKIND_FIVE,
    HANDKIND_TOTAL
};

struct hand {
    char cards[5];
    int hand_vals[5];
    int kind;
    int bet;
};

int HEX[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

int card_2_hex(char c)
{
    switch (c) {
        case 'A': return HEX[14];
        case 'K': return HEX[13];
        case 'Q': return HEX[12];
        case 'J': return HEX[11];
        case 'T': return HEX[10];
        default: return HEX[c - '0'];
    }
}

int hand_kind(struct hand *h)
{
    int slots[15] = {0};
    for (int i = 0; i < 5; i++) {
        slots[h->hand_vals[i]]++;
    }
    int combos[HANDKIND_TOTAL] = {0};
    for (int i = 0; i < 15; i++) {
        switch (slots[i]) {
            case 0: combos[HANDKIND_HI]++; break;
            case 1: combos[HANDKIND_ONE]++; break;
            case 2: combos[HANDKIND_TWO]++; break;
            case 3: combos[HANDKIND_THREE]++; break;
            case 4: combos[HANDKIND_FOUR]++; break;
            case 5: combos[HANDKIND_FIVE]++; break;
        }
    }
    if (combos[HANDKIND_FIVE]) return HANDKIND_FIVE;
    if (combos[HANDKIND_FOUR]) return HANDKIND_FOUR;
    if (combos[HANDKIND_THREE] && combos[HANDKIND_TWO]) return HANDKIND_FULL;
    if (combos[HANDKIND_THREE]) return HANDKIND_THREE;
    if (combos[HANDKIND_TWO]) return HANDKIND_TWO;
    if (combos[HANDKIND_ONE]) return HANDKIND_ONE;
    return HANDKIND_HI;
}

int int_cmp(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return ib - ia;
}

int card_cmp(const void *a, const void *b)
{
    char ia = *(const int *)a;
    char ib = *(const int *)b;
    int va = card_2_hex(ia);
    int vb = card_2_hex(ib);
    return va - vb;
}

struct hand parse_hand(char **s)
{
    struct hand h;

    assert(strlen(s[0]) == 5);

    for (int i = 0; i < 5; i++)
        h.cards[i] = s[0][i];
    qsort(h.cards, 5, sizeof(char), card_cmp);
    for (int i = 0; i < 5; i++)
        h.hand_vals[i] = card_2_hex(s[0][i]);
    h.bet = atoi(s[1]);
    h.kind = hand_kind(&h);
    return h;
}

int hand_cmp(const void *a, const void *b)
{
    struct hand *ha = (struct hand *)a;
    struct hand *hb = (struct hand *)b;

    // sort by hand kind first
    if (ha->kind != hb->kind) {
        return hb->kind - ha->kind;
    }

    for (int i = 0; i < 5; i++) {
        if (ha->hand_vals[i] != hb->hand_vals[i]) {
            return hb->hand_vals[i] - ha->hand_vals[i];
        }
    }
    return 0;
}

void p1()
{
    int ans = 0;
    char buf[1024];
    struct hand *hands = NULL;

    // For this, we translate the cards to hex digits, sort the hands such that they are "reverse"
    // sorted, then score each hand for the betting parts.

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char **strs = find_all_strs(buf);

        struct hand curr = parse_hand(strs);
        arrput(hands, curr);

        arrfree(strs);
    }

    qsort(hands, arrlen(hands), sizeof(hands[0]), hand_cmp);

    for (int i = 0; i < arrlen(hands); i++) {
        fprintf(stderr, "\t%.*s - %d - %d\n", 5, hands[i].cards, hands[i].kind, hands[i].bet);
        ans += hands[i].bet * (arrlen(hands) - i);
    }

    printf("p1: %d\n", ans);

    arrfree(hands);
}

void p2()
{
    int ans = 0;

    printf("p2: %d\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
