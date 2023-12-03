#include "common.h"

#include "json.h"

#define BUFSIZE 1 << 20

int isnum(char *s)
{
	for (; *s && isdigit(*s); s++)
		;
	return *s == 0;
}

int sum_nums_in_doc(struct json_value_s *curr)
{
	int sum = 0;
	if (curr == NULL || curr->type == json_type_null)
		return 0;
	if (curr->type == json_type_true || curr->type == json_type_false)
		return 0;
	if (curr->type == json_type_object) {
		struct json_object_s *o = curr->payload;
		for (struct json_object_element_s *e = o->start; e; e = e->next) {
			sum += sum_nums_in_doc(e->value);
		}
		return sum;
	} else if (curr->type == json_type_array) { // different type, technically... ugh
		struct json_array_s *a = curr->payload;
		for (struct json_array_element_s *e = a->start; e; e = e->next) {
			sum += sum_nums_in_doc(e->value);
		}
		return sum;
	} else if (curr->type == json_type_string) {
		return 0;
	} else if (curr->type == json_type_number) {
		struct json_number_s *num = curr->payload;
		return atoi(num->number);
	} else {
		assert(0);
		return 0;
	}
}

void p1()
{
	char *gbuf = calloc(BUFSIZE, sizeof(*gbuf));
	int i, c, len;

	for (i = 0; (c = getchar()) != EOF; i++)
		gbuf[i] = c;
	len = i;

	struct json_value_s *tree = json_parse(gbuf, len);

	i = sum_nums_in_doc(tree);
	printf("p1: %d\n", i);

	free(tree);
	free(gbuf);
}

int checkred(struct json_object_s *o)
{
	for (struct json_object_element_s *e = o->start; e; e = e->next) {
		struct json_value_s *val = e->value;
		if (val->type == json_type_string) {
			if (strcmp(((struct json_string_s *)val->payload)->string, "red") == 0)
				return 1;
		}
	}
	return 0;
}

int sum_nums_in_doc_2(struct json_value_s *curr)
{
	int sum = 0;
	if (curr == NULL || curr->type == json_type_null) {
		return 0;
	} else if (curr->type == json_type_true) {
		return 0;
	} else if (curr->type == json_type_false) {
		return 0;
	} else if (curr->type == json_type_string) {
		return 0;
	} else if (curr->type == json_type_object) {
		struct json_object_s *o = curr->payload;
		if (checkred(o))
			return 0;
		for (struct json_object_element_s *e = o->start; e; e = e->next) {
			sum += sum_nums_in_doc_2(e->value);
		}
		return sum;
	} else if (curr->type == json_type_array) { // different type, technically... ugh
		struct json_array_s *a = curr->payload;
		for (struct json_array_element_s *e = a->start; e; e = e->next) {
			sum += sum_nums_in_doc_2(e->value);
		}
		return sum;
	} else if (curr->type == json_type_number) {
		struct json_number_s *num = curr->payload;
		return atoi(num->number);
	} else {
		assert(0);
		return 0;
	}
}

void p2()
{
	char *gbuf = calloc(BUFSIZE, sizeof(*gbuf));
	int i, c, len;

	for (i = 0; (c = getchar()) != EOF; i++)
		gbuf[i] = c;
	len = i;

	struct json_value_s *tree = json_parse(gbuf, len);

	i = sum_nums_in_doc_2(tree);
	printf("p2: %d\n", i);

	free(tree);
	free(gbuf);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
