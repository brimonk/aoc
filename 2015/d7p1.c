// Brian Chrzanowski
// 2022-12-01 20:52:54
//
// This was really the first one that made me think a bit.
//
// To get around the problem of not really creating the graph correctly, we'll just continually loop
// over the input, processing lines as we go, until we run out of input to process.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

struct wire_t {
	struct wire_t *next;
	char *name;
	unsigned short signal;
};

struct line_t {
	struct line_t *next, *prev;
	char *text;
};

int isnum(char *s)
{
	while (*s)
		if (!isdigit(*s++))
			return 0;
	return 1;
}

struct wire_t *mkwire(char *name, unsigned short sig)
{
	struct wire_t *wire = calloc(1, sizeof(*wire));
	wire->name = strdup(name);
	wire->signal = sig;
	return wire;
}

struct wire_t *lookup(struct wire_t *head, char *name)
{
	if (head == NULL)
		return NULL;
	if (strcmp(head->name, name) == 0)
		return head;
	return lookup(head->next, name);
}

void prepend(struct wire_t **head, struct wire_t **curr)
{
	(*curr)->next = *head;
	*head = *curr;
}

struct line_t *addline(struct line_t *head, char *s)
{
	struct line_t *curr = calloc(1, sizeof(*curr));
	curr->text = s;

	if (head == NULL) {
		curr->next = curr->prev = curr;
		return curr;
	} else {
		struct line_t *last = head->prev;
		last->next = curr;
		curr->next = head;
		curr->prev = last;
		head->prev = curr;
		return head;
	}
}

// i need to write more linked list code
struct line_t *rmline(struct line_t *elem)
{
	free(elem->text);
	if (elem->prev == elem->next && elem->next == elem) {
		free(elem);
		return NULL;
	} else {
		struct line_t *z = elem->next;
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		free(elem);
		return z;
	}
}

void printlist_(struct line_t *head, struct line_t *curr, int idx)
{
	if (head == NULL || curr == NULL)
		return;
	if (head == curr && idx != 0)
		return;
	printf("%d %s\n", idx, curr->text);
	printlist_(head, curr->next, ++idx);
}

void printlist(struct line_t *ll)
{
	printlist_(ll, ll, 0);
}

int countlist_(struct line_t *head, struct line_t *curr, int idx)
{
	if (head == NULL || curr == NULL)
		return 0;
	if (head == curr && idx != 0)
		return 0;
	return countlist_(head, curr->next, idx + 1) + 1;
}

int countlist(struct line_t *ll)
{
	return countlist_(ll, ll, 0);
}

int main(int argc, char **argv)
{
	char buf[512] = {0};
	char *tokens[8];
	char *s;
	int i;
	int success;
	struct wire_t *head = NULL;
	struct wire_t *curr = NULL;
	struct line_t *lhead = NULL;
	struct line_t *lcurr = NULL;

	// read in all lines of text
	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;
		char *s = strdup(buf);
		assert(strlen(s) > 0);
		lhead = addline(lhead, s);
	}

	for (lcurr = lhead; lcurr; ) {
		memset(tokens, 0, sizeof tokens);

		s = strdup(lcurr->text);

		for (s = strtok(s, " "), i = 0; s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		success = 0;

#define CONDSKIP(C) if (C) { success = 0; break; } else { success = 1; }
		do {
			if (isnum(tokens[0])) { // setting a value
				curr = mkwire(tokens[2], (unsigned short)atoi(tokens[0]));
				success = 1;
				prepend(&head, &curr);
			} else if (strcmp(tokens[1], "AND") == 0) {
				struct wire_t *left = lookup(head, tokens[0]);
				struct wire_t *right = lookup(head, tokens[2]);
				CONDSKIP(left == NULL || right == NULL)
				unsigned short v = left->signal & right->signal;
				curr = mkwire(tokens[4], v);
				prepend(&head, &curr);
			} else if (strcmp(tokens[1], "OR") == 0) {
				struct wire_t *left = lookup(head, tokens[0]);
				struct wire_t *right = lookup(head, tokens[2]);
				CONDSKIP(left == NULL || right == NULL)
				unsigned short v = left->signal | right->signal;
				curr = mkwire(tokens[4], v);
				prepend(&head, &curr);
			} else if (strcmp(tokens[1], "LSHIFT") == 0) {
				struct wire_t *left = lookup(head, tokens[0]);
				CONDSKIP(left == NULL)
				int shift = atoi(tokens[2]);
				unsigned short v = left->signal << shift;
				curr = mkwire(tokens[4], v);
				prepend(&head, &curr);
			} else if (strcmp(tokens[1], "RSHIFT") == 0) {
				struct wire_t *left = lookup(head, tokens[0]);
				CONDSKIP(left == NULL)
				int shift = atoi(tokens[2]);
				unsigned short v = left->signal >> shift;
				curr = mkwire(tokens[4], v);
				prepend(&head, &curr);
			} else if (strcmp(tokens[0], "NOT") == 0) {
				struct wire_t *source = lookup(head, tokens[1]);
				CONDSKIP(source == NULL)
				unsigned short v = ~source->signal;
				curr = mkwire(tokens[3], v);
				prepend(&head, &curr);
			} else if (strcmp(tokens[1], "->") == 0 && i == 3) {
				struct wire_t *new = lookup(head, tokens[0]);
				CONDSKIP(new == NULL)
				unsigned short v = new->signal;
				curr = mkwire(tokens[2], v);
				prepend(&head, &curr);
			} else {
				fprintf(stderr, "UNKNOWN TOKEN SET!!!!\n");
				for (i = 0; tokens[i]; i++)
					printf("%d %s\n", i, tokens[i]);
				exit(1);
			}
		} while (0);
#undef CONDSKIP

		if (success)
			lcurr = rmline(lcurr);
		else
			lcurr = lcurr->next;

		printf("lines remaining %d\n", countlist(lcurr));

		free(s);
	}

#if 0
	char *wires[] = {
		"d", "e", "f", "g", "h", "i", "x", "y"
	};
#else
	char *wires[] = {
		"a"
	};
#endif

	for (i = 0; i < (sizeof(wires)/sizeof(wires[0])); i++) {
		curr = lookup(head, wires[i]);
		printf("signal %s %d\n", wires[i], curr->signal);
	}

	return 0;
}
