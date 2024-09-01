#include "common.h"

#define STB_C_LEXER_IMPLEMENTATION
#include "stb_c_lexer.h"

typedef struct {
	int x, m, a, s;
} Part;

typedef struct {
	int rating;
	int op; // '>' or '<'
	int value;
	char destination[16];
} Rule;

typedef struct {
	char name[16];
	Rule *rules;
} Workflow;

typedef struct {
	char *ptr;
	int len;
	long kind;
} Token;

Workflow *GetWorkflowByName(Workflow *workflows, char *name)
{
	Workflow *w = NULL;
	for (size_t i = 0; i < arrlen(workflows); i++) {
		if (streq(workflows[i].name, name)) {
			w = &workflows[i];
		}
	}
	return w;
}

Rule ParseRule(Token *tokens, size_t *curr)
{
	Rule r = {0};

	assert(arrlen(tokens) > ((*curr) + 1));
	assert(tokens[(*curr) + 0].kind != CLEX_id);

	if (tokens[(*curr) + 1].kind == '}') {
		r.rating = -1;
		r.op = -1;
		r.value = -1;
		strncpy(r.destination, tokens[(*curr) + 0].ptr, MIN(tokens[(*curr) + 0].len, sizeof(r.destination)));
		*curr += 2;
	} else {
		r.rating = tokens[(*curr) + 0].ptr[0];
		r.op = tokens[(*curr) + 1].kind;
		r.value = atoi(tokens[(*curr) + 2].ptr);
		*curr += 6; // skip past ','
	}

	return r;
}

Workflow ParseWorkflow(Token *tokens)
{
	assert(tokens[0].kind == CLEX_id);
	Workflow w = {0};

	strncpy(w.name, tokens[0].ptr, MIN(tokens[0].len, sizeof(w.name)));

	size_t curr = 1;

	assert(tokens[curr].kind == '{');

	while (arrlen(tokens) > curr) {
		Rule r = ParseRule(tokens, &curr);
		arrput(w.rules, r);
	}

	return w;
}

void p1()
{
    i64 ans = 0;

	autofreelines char **lines = read_all_lines();

	Workflow *workflows = NULL;

	// This is overkill, but we lex every statement, and have a small parser
	// for the rules.

	size_t i;
	for (i = 0; i < arrlen(lines); i++) {
		if (strlen(lines[i]) == 0)
			break;

		stb_lexer lex = {0};
		autofree char *strspace = calloc(1, 1024);
		stb_c_lexer_init(&lex, lines[i], lines[i] + strlen(lines[i]), strspace, 1024);

		Token *tokens = NULL;

		while (stb_c_lexer_get_token(&lex)) {
			assert(lex.token != CLEX_parse_error);
			Token t = {
				.ptr = lex.string,
				.len = lex.string_len,
				.kind = lex.token
			};
			arrput(tokens, t);
		}

		Workflow parsed = ParseWorkflow(tokens);
		arrput(workflows, parsed);

		arrfree(tokens);
	}

	for (i++; i < arrlen(lines); i++) {
	}

    printf("p1: %ld\n", ans);

	arrfree(workflows);
}

void p2()
{
    i64 ans = 0;

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
