#include "common.h"

struct node {
    char *key;
    struct {
        char *left;
        char *right;
    } value;
    i64 length_to_z;
};

struct node *lookup(struct node *nodes, char *key)
{
    for (size_t i = 0; i < arrlen(nodes); i++) {
        if (strcmp(key, nodes[i].key) == 0) {
            return nodes + i;
        }
    }
    return NULL;
}

void p1()
{
    i64 ans = 0;

    char buf[1024] = {0};
    bfgets(buf, sizeof buf, stdin);

    char *instructions = strdup(buf);

    struct node *map = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = buf;
        if (strlen(s) == 0)
            continue;

        struct node curr = {0};
        char key[4] = {0};
        char left[4] = {0};
        char right[4] = {0};

        int rc = sscanf(s, "%3s = (%3s, %3s)", key, left, right);
        assert(rc == 3);

        // fprintf(stderr, "\t%s, %s, %s\n", key, left, right);

        curr.key = strdup(key);
        curr.value.left = strdup(left);
        curr.value.right = strdup(right);

        arrput(map, curr);
    }

    struct node *curr = lookup(map, "AAA");
    assert(curr);

    for (size_t i = 0; strcmp(curr->key, "ZZZ") != 0; i++, ans++) {
        int instruction = instructions[i % strlen(instructions)];

        switch (instruction) {
            case 'R': {
                curr = lookup(map, curr->value.right);
                break;
            }
            case 'L': {
                curr = lookup(map, curr->value.left);
                break;
            }
            default:
                assert(0);
        }

        // fprintf(stderr, "\tvisiting %s\n", curr->key);

        assert(curr);
    }

    printf("p1: %ld\n", ans);

    free(instructions);

    for (size_t i = 0; i < arrlen(map); i++) {
        free(map[i].key);
        free(map[i].value.left);
        free(map[i].value.right);
    }

    arrfree(map);
}

i64 find_length_to_z(struct node *list, struct node *curr, char *instructions)
{
    i64 i;
    for (i = 0; curr->key[2] != 'Z'; i++) {
        int instruction = instructions[i % strlen(instructions)];

        switch (instruction) {
            case 'R': {
                curr = lookup(list, curr->value.right);
                break;
            }
            case 'L': {
                curr = lookup(list, curr->value.left);
                break;
            }
            default:
                assert(0);
        }

        // fprintf(stderr, "\tvisiting %s\n", curr->key);

        assert(curr);
    }
    return i;
}

i64 gcd(i64 a, i64 b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

i64 find_lcm(i64 *arr)
{
    i64 ans = arr[0];
    for (size_t i = 1; i < arrlen(arr); i++) {
        ans = (arr[i] * ans) / gcd(arr[i], ans);
    }
    return ans;
}

void p2()
{
    i64 ans = 0;

    char buf[1024] = {0};
    bfgets(buf, sizeof buf, stdin);

    char *instructions = strdup(buf);

    struct node *map = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *s = buf;
        if (strlen(s) == 0)
            continue;

        struct node curr = {0};
        char key[4] = {0};
        char left[4] = {0};
        char right[4] = {0};

        int rc = sscanf(s, "%3s = (%3s, %3s)", key, left, right);
        assert(rc == 3);

        // fprintf(stderr, "\t%s, %s, %s\n", key, left, right);

        curr.key = strdup(key);
        curr.value.left = strdup(left);
        curr.value.right = strdup(right);

        arrput(map, curr);
    }

    struct node **currlist = NULL;

    for (size_t i = 0; i < arrlen(map); i++) {
        if (map[i].key[2] == 'A') {
            // fprintf(stderr, "\tfound %s\n", map[i].key);
            arrput(currlist, &map[i]);
        }
    }

    // fprintf(stderr, "\tlen %ld\n", arrlen(currlist));

    i64 *steps = NULL;
    for (size_t i = 0; i < arrlen(currlist); i++) {
        i64 z = find_length_to_z(map, currlist[i], instructions);
        arrput(steps, z);
    }

    ans = find_lcm(steps);

    printf("p2: %ld\n", ans);

    arrfree(steps);
    arrfree(currlist);
    free(instructions);

    for (size_t i = 0; i < arrlen(map); i++) {
        free(map[i].key);
        free(map[i].value.left);
        free(map[i].value.right);
    }

    arrfree(map);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
