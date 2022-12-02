#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

// time to do some dfs (or something)

struct list_t {
	struct list_t *next;
};

struct city_t {
	struct list_t list;
	char *name;
	int isvisited;
	// struct city_t *neighbor;
};

struct linkage_t {
	struct list_t list;
	struct city_t *from;
	struct city_t *to;
	int cost;
};

struct city_t *cities = NULL;
struct linkage_t *linkages = NULL;

int linkagecmp(const void *a, const void *b)
{
	struct linkage_t *la = (struct linkage_t *)a;
	struct linkage_t *lb = (struct linkage_t *)b;
	if (la != NULL && lb == NULL)
		return -1;
	if (la == NULL && lb == NULL)
		return 0;
	if (la == NULL && lb != NULL)
		return 1;
	return strcmp(la->from->name, lb->from->name);
}

struct list_t *prepend(struct list_t *head, struct list_t *elem)
{
	if (head == NULL) {
		return elem;
	} else {
		elem->next = head;
		return elem;
	}
}

int listlen(struct list_t *curr)
{
	return curr == NULL ? 0 : 1 + listlen(curr->next);
}

void addcity(char *name)
{
	struct city_t *city = calloc(1, sizeof(*city));
	city->name = strdup(name);
	cities = (void *)prepend((struct list_t *)cities, (struct list_t *)city);
}

struct city_t *clookup(struct city_t *curr, char *name)
{
	if (curr == NULL)
		return NULL;
	if (strcmp(curr->name, name) == 0)
		return curr;
	return clookup((struct city_t *)curr->list.next, name);
}

void addlinkage(char *s1, char *s2, int cost)
{
	struct city_t *c1 = clookup(cities, s1);
	if (c1 == NULL) {
		addcity(s1);
		c1 = clookup(cities, s1);
	}
	struct city_t *c2 = clookup(cities, s2);
	if (c2 == NULL) {
		addcity(s2);
		c2 = clookup(cities, s2);
	}
	struct linkage_t *new = calloc(1, sizeof(*new));
	new->from = c1;
	new->to = c2;
	new->cost = cost;
	linkages = (void *)prepend((struct list_t *)linkages, (struct list_t *)new);
}

void lsort(struct list_t **head, int(*cmp)(const void *a, const void *b))
{
	struct list_t *t;
	if (head == NULL || (*head) == NULL || (*head)->next == NULL)
		return;
	int cv = cmp((*head), (*head)->next);
	if (0 < cv) {
		t = *head;
		*head = (*head)->next;
		(*head)->next = t;
	}
	lsort(&((*head)->next), cmp);
}

// returns the nearest neighbor for the given city
struct linkage_t *nearest_neighbor(struct city_t *city)
{
	struct linkage_t *curr;
	struct linkage_t *nearest = NULL;
	int dist = INT_MAX;
	printf("finding nearest for %s\n", city->name);
	for (curr = linkages; curr; curr = (void *)curr->list.next) {
		if (curr->from == city)
			break;
		printf("L %s -> %s\n", curr->from->name, curr->to->name);
	}
	assert(curr != NULL);
	for (; curr && curr->from == city; curr = (void *)curr->list.next) {
		if (curr->cost < dist) {
			dist = curr->cost;
			nearest = curr;
		}
	}
	assert(nearest != NULL);
	assert(curr->from != city);
	return nearest;
}

int has_unvisited(struct city_t *cities)
{
	if (cities == NULL)
		return 0;
	else if (cities->isvisited)
		return has_unvisited((struct city_t *)cities->list.next);
	else
		return 1;
}

int main(int argc, char **argv)
{
	char buf[512];
	char *tokens[8];
	char *s;
	int i;

	while (buf == fgets(buf, sizeof buf, stdin)) {
		buf[strlen(buf) - 1] = 0;

		for (i = 0, s = strtok(buf, " "); s; i++, s = strtok(NULL, " "))
			tokens[i] = s;
		tokens[i] = s;

		addlinkage(tokens[0], tokens[2], atoi(tokens[4]));
		addlinkage(tokens[2], tokens[0], atoi(tokens[4]));
	}

	printf("cities len %d\n", listlen((void *)cities));
	printf("linkages len %d\n", listlen((void *)linkages));

	lsort((struct list_t **)&linkages, linkagecmp);

	struct city_t *curr = cities;
	struct linkage_t *nearest_link = NULL;
	int distance = 0;

	while (has_unvisited(cities)) {
		nearest_link = nearest_neighbor(curr);
		printf("from %s to %s, cost %d\n", curr->name, nearest_link->to->name, nearest_link->cost);
		distance += nearest_link->cost;
		curr->isvisited = 1;
		curr = nearest_link->to;
	}

	printf("shortest distance %d\n", distance);

	return 0;
}
