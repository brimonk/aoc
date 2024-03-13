#include "common.h"

enum {
    OP_ASSIGN,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_LSHIFT,
    OP_RSHIFT,
};

struct component {
    char id[8];
    char depends1[8];
    char depends2[8];
    u16 signal; // -1 for unknown
    int op;
    int resolved;
};

void print_operation(struct component *comp)
{
	switch (comp->op) {
    case OP_ASSIGN:
		// printf("- %s -> %s\n", comp->depends1, comp->id);
		break;
    case OP_AND:
		// printf("- %s AND %s -> %s\n", comp->depends1, comp->depends2, comp->id);
		break;
    case OP_OR:
		// printf("- %s OR %s -> %s\n", comp->depends1, comp->depends2, comp->id);
		break;
    case OP_NOT:
		// printf("- NOT %s -> %s\n", comp->depends1, comp->id);
		break;
    case OP_LSHIFT:
		// printf("- %s LSHIFT %s -> %s\n", comp->depends1, comp->depends2, comp->id);
		break;
    case OP_RSHIFT:
		// printf("- %s RSHIFT %s -> %s\n", comp->depends1, comp->depends2, comp->id);
		break;
	}
}

struct component *lookup(struct component *components, char *s)
{
    for (size_t i = 0; i < arrlen(components); i++) {
        if (streq(components[i].id, s))
            return components + i;
    }
    return NULL;
}

int level = 0;

// resolve: returns the value at the component 'component'
u16 resolve(struct component *components, char *s)
{
    // printf("resolving '%s'...\n", s);

    if (isdigit(s[0])) {
        return (u16)atoi(s);
    }

    struct component *curr = lookup(components, s);

    assert(curr);

    if (curr->resolved)
        return curr->signal;

    level += 1;

	print_operation(curr);

    switch (curr->op) {
        case OP_ASSIGN: {
			// printf("'%s' has a dependency on '%s'\n", s, curr->depends1);
            u16 s1 = resolve(components, curr->depends1);
            curr->signal = s1;
            break;
        }
        case OP_AND: {
			// printf("'%s' has a dependency on '%s' and '%s'\n", s, curr->depends1, curr->depends2);
            u16 s1 = resolve(components, curr->depends1);
            u16 s2 = resolve(components, curr->depends2);
            curr->signal = s1 & s2;
            break;
        }
        case OP_OR: {
			// printf("'%s' has a dependency on '%s' and '%s'\n", s, curr->depends1, curr->depends2);
            u16 s1 = resolve(components, curr->depends1);
            u16 s2 = resolve(components, curr->depends2);
            curr->signal = s1 | s2;
            break;
        }
        case OP_NOT: {
			// printf("'%s' has a dependency on '%s'\n", s, curr->depends1);
            u16 s1 = resolve(components, curr->depends1);
            curr->signal = ~s1;
            break;
        }
        case OP_LSHIFT: {
			// printf("'%s' has a dependency on '%s'\n", s, curr->depends1);
            u16 s1 = resolve(components, curr->depends1);
            curr->signal = s1 << atoi(curr->depends2);
            break;
        }
        case OP_RSHIFT: {
			// printf("'%s' has a dependency on '%s'\n", s, curr->depends1);
            u16 s1 = resolve(components, curr->depends1);
            curr->signal = s1 >> atoi(curr->depends2);
            break;
        }
        default:
            assert(0);
            break;
    }

    level -= 1;

    // printf("resolved '%s' to %hu\n", s, curr->signal);

    curr->resolved = true;
    return curr->signal;
}

void p1()
{
    i64 ans = 0;
    char buf[1024] = {0};
    struct component *components = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *strs[32] = {0};
        int i = 0;
        for (char *s = strtok(buf, " "); s; s = strtok(NULL, " "))
            strs[i++] = s;

        struct component comp = {0};

        if (streq(strs[1], "->")) {
            strncpy(comp.id, strs[2], sizeof comp.id);
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
        } else if (streq(strs[1], "AND")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_AND;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[1], "OR")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_OR;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[0], "NOT")) {
            strncpy(comp.id, strs[3], sizeof comp.id);
            comp.op = OP_NOT;
            strncpy(comp.depends1, strs[1], sizeof comp.depends1);
        } else if (streq(strs[1], "LSHIFT")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_LSHIFT;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[1], "RSHIFT")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_RSHIFT;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else {
            assert(0);
        }

        arrput(components, comp);
    }

    ans = resolve(components, "a");
    printf("p1: %ld\n", ans);

    arrfree(components);
}

void p2()
{
    i64 ans = 0;
    char buf[1024] = {0};
    struct component *components = NULL;

    while (buf == bfgets(buf, sizeof buf, stdin)) {
        char *strs[32] = {0};
        int i = 0;
        for (char *s = strtok(buf, " "); s; s = strtok(NULL, " "))
            strs[i++] = s;

        struct component comp = {0};

        if (streq(strs[1], "->")) {
            strncpy(comp.id, strs[2], sizeof comp.id);
            comp.op = OP_ASSIGN;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
        } else if (streq(strs[1], "AND")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_AND;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[1], "OR")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_OR;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[0], "NOT")) {
            strncpy(comp.id, strs[3], sizeof comp.id);
            comp.op = OP_NOT;
            strncpy(comp.depends1, strs[1], sizeof comp.depends1);
        } else if (streq(strs[1], "LSHIFT")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_LSHIFT;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else if (streq(strs[1], "RSHIFT")) {
            strncpy(comp.id, strs[4], sizeof comp.id);
            comp.op = OP_RSHIFT;
            strncpy(comp.depends1, strs[0], sizeof comp.depends1);
            strncpy(comp.depends2, strs[2], sizeof comp.depends2);
        } else {
            assert(0);
        }

        arrput(components, comp);
    }

	{
		u16 a_signal = resolve(components, "a");

		// reset every singal to not be resolved
		for (i64 i = 0; i < arrlen(components); i++) {
			components[i].resolved = false;
		}

		struct component *b = lookup(components, "b");
		assert(b);
		b->op = OP_ASSIGN;
		snprintf(b->depends1, sizeof b->depends1, "%hd", a_signal);
	}

	ans = resolve(components, "a");
    printf("p2: %ld\n", ans);

    arrfree(components);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
