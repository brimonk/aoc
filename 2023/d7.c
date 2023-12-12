#include "common.h"

enum {
    HANDKIND_HI = 0,
    HANDKIND_ONE = 1,
    HANDKIND_TWO = 2,
    HANDKIND_THREE = 3,
    HANDKIND_FULL = 4,
    HANDKIND_FOUR = 5,
    HANDKIND_FIVE = 6,
    HANDKIND_TOTAL
};

struct hand {
    char cards[6];
    char valus[6];
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

int card_value(char c)
{
    switch (c) {
        case 'A': return 14;
        case 'K': return 13;
        case 'Q': return 12;
        case 'J': return 11;
        case 'T': return 10;
        default: return  c - '0';
    }
}

int hand_kind(struct hand *h)
{
    int slots[15] = {0};
    for (int i = 0; i < 5; i++) {
        slots[card_value(h->cards[i])]++;
    }
    int combos[HANDKIND_TOTAL] = {0};
    for (int i = 0; i < 15; i++) {
        if (slots[i] == 0)
            continue;
        switch (slots[i]) {
            case 0: combos[HANDKIND_HI]++; break;
            case 2: combos[HANDKIND_TWO]++; break;
            case 3: combos[HANDKIND_THREE]++; break;
            case 4: combos[HANDKIND_FOUR]++; break;
            case 5: combos[HANDKIND_FIVE]++; break;
            default: break;
        }
    }
    if (combos[HANDKIND_FIVE])
        return HANDKIND_FIVE;
    if (combos[HANDKIND_FOUR])
        return HANDKIND_FOUR;
    if (combos[HANDKIND_THREE] && combos[HANDKIND_TWO])
        return HANDKIND_FULL;
    if (combos[HANDKIND_THREE])
        return HANDKIND_THREE;
    if (combos[HANDKIND_TWO] == 2)
        return HANDKIND_TWO;
    if (combos[HANDKIND_TWO])
        return HANDKIND_ONE;
    return HANDKIND_HI;
}

struct hand parse_hand(char **s)
{
    struct hand h;

    assert(strlen(s[0]) == 5);

    for (int i = 0; i < 5; i++)
        h.cards[i] = s[0][i];

    for (int i = 0; i < 5; i++)
        h.valus[i] = card_2_hex(h.cards[i]);

    h.bet = atoi(s[1]);
    h.kind = hand_kind(&h);

    return h;
}

int hand_cmp(const void *a, const void *b)
{
    struct hand *ha = (struct hand *)a;
    struct hand *hb = (struct hand *)b;
    if (hb->kind == ha->kind)
        return strcmp(hb->valus, ha->valus);
    return hb->kind - ha->kind;
}

void p1()
{
    i64 ans = 0;
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
        ans += hands[i].bet * (arrlen(hands) - i);
#if 0
        fprintf(stderr, "\t%.*s - %.*s - %d - %d - %ld\n",
            5, hands[i].cards, 5, hands[i].valus, hands[i].kind, hands[i].bet, ans
        );
#endif
    }

    printf("p1: %ld\n", ans);

    arrfree(hands);
}

int card_2_hex_2(char c)
{
    switch (c) {
        case 'A': return HEX[14];
        case 'K': return HEX[13];
        case 'Q': return HEX[12];
        case 'J': return '1';
        case 'T': return HEX[10];
        default: return HEX[c - '0'];
    }
}

int card_value_2(char c)
{
    switch (c) {
        case 'A': return 14;
        case 'K': return 13;
        case 'Q': return 12;
        case 'J': return 1;
        case 'T': return 10;
        default: return  c - '0';
    }
}

int hand_kind_2(struct hand *h)
{
    int slots[15] = {0};
    for (int i = 0; i < 5; i++) {
        slots[card_value_2(h->cards[i])]++;
    }

    // translate "jokers" into the highest of whatever other card there is
    if (slots[1] >= 1) {
        // find the highest
        int c = 0;
        int m = 0;
        for (int i = 2; i < 15; i++) {
            if (c <= slots[i] && m < i) {
                c = slots[i];
                m = i;
            }
        }

        int t = slots[1];
        slots[1] -= t;
        slots[m] += t;
    }

    int combos[HANDKIND_TOTAL] = {0};
    for (int i = 0; i < 15; i++) {
        if (slots[i] == 0)
            continue;
        switch (slots[i]) {
            case 0: combos[HANDKIND_HI]++; break;
            case 2: combos[HANDKIND_TWO]++; break;
            case 3: combos[HANDKIND_THREE]++; break;
            case 4: combos[HANDKIND_FOUR]++; break;
            case 5: combos[HANDKIND_FIVE]++; break;
            default: break;
        }
    }
    if (combos[HANDKIND_FIVE])
        return HANDKIND_FIVE;
    if (combos[HANDKIND_FOUR])
        return HANDKIND_FOUR;
    if (combos[HANDKIND_THREE] && combos[HANDKIND_TWO])
        return HANDKIND_FULL;
    if (combos[HANDKIND_THREE])
        return HANDKIND_THREE;
    if (combos[HANDKIND_TWO] == 2)
        return HANDKIND_TWO;
    if (combos[HANDKIND_TWO])
        return HANDKIND_ONE;
    return HANDKIND_HI;
}

struct hand parse_hand_2(char **s)
{
    struct hand h;

    assert(strlen(s[0]) == 5);

    for (int i = 0; i < 5; i++)
        h.cards[i] = s[0][i];

    for (int i = 0; i < 5; i++)
        h.valus[i] = card_2_hex_2(h.cards[i]);

    h.bet = atoi(s[1]);
    h.kind = hand_kind_2(&h);

    return h;
}

void p2()
{
    i64 ans = 0;
    char buf[1024];
    struct hand *hands = NULL;

    // For this, we translate the cards to hex digits, sort the hands such that they are "reverse"
    // sorted, then score each hand for the betting parts.

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char **strs = find_all_strs(buf);

        struct hand curr = parse_hand_2(strs);
        arrput(hands, curr);

        arrfree(strs);
    }

    qsort(hands, arrlen(hands), sizeof(hands[0]), hand_cmp);

    for (int i = 0; i < arrlen(hands); i++) {
        ans += hands[i].bet * (arrlen(hands) - i);
#if 1
        fprintf(stderr, "\t%.*s - %.*s - %d - %d - %ld\n",
            5, hands[i].cards, 5, hands[i].valus, hands[i].kind, hands[i].bet, ans
        );
#endif
    }

    printf("p2: %ld\n", ans);

    arrfree(hands);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
