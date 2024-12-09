#include "common.h"

// Wouldn't it be insane if we just created the defrag algo on the input as it appeared in the
// problem?

i32 idx_of_free(i32 *disk)
{
	for (i32 i = 0; i < arrlen(disk); i++)
		if (disk[i] == -1)
			return i;
	return -1;
}

void swap(i32 *a, i32 *b)
{
	i32 t = *b;
	*b = *a;
	*a = t;
}

void p1()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr i32 *disk = NULL;
	for (i32 i = 0; i < strlen(lines[0]); i++) {
		for (i32 j = 0; j < lines[0][i] - '0'; j++) {
			i32 id = i % 2 == 0 ? i / 2 : -1;
			arrput(disk, id);
		}
	}

	for (i32 i = arrlen(disk) - 1; i >= 0; i--) {
		if (disk[i] != -1) {
			i32 free_idx = idx_of_free(disk);
			assert(free_idx >= 0);

			if (free_idx < i)
				swap(&disk[i], &disk[free_idx]);
		}
	}

	for (i32 i = 0; i < arrlen(disk) && disk[i] != -1; i++) {
		// printf("%d - %d\n", i, disk[i]);
		ans += i * disk[i];
	}

    printf("p1: %ld\n", ans);
}

i32 start_idx_of_file(i32 *disk, i32 file)
{
	for (i32 i = 0; i < arrlen(disk); i++)
		if (disk[i] == file)
			return i;
	return -1;
}

i32 len_of_run(i32 *disk, i32 idx)
{
	i32 len = 0;
	for (i32 i = idx; i < arrlen(disk) && disk[i] == disk[idx]; i++)
		len++;
	return len;
}

void p2()
{
    i64 ans = 0;
	autofreelines char **lines = read_all_lines();

	autofreearr i32 *disk = NULL;
	for (i32 i = 0; i < strlen(lines[0]); i++) {
		for (i32 j = 0; j < lines[0][i] - '0'; j++) {
			i32 id = i % 2 == 0 ? i / 2 : -1;
			arrput(disk, id);
		}
	}

	for (i32 i = arrlen(disk) - 1; i >= 0; i--) {
		if (disk[i] != -1) {
			i32 start = start_idx_of_file(disk, disk[i]);
			i32 file_len = len_of_run(disk, start);

			for (i32 j = 0; j < arrlen(disk) && j < i; j++) {
				if (disk[j] == -1 && len_of_run(disk, j) >= file_len) {
					memmove(&disk[j], &disk[start], sizeof(disk[start]) * file_len);
					memset(&disk[start], 0xff, sizeof(disk[start]) * file_len); // -1 -> all on in 2s complement
					break;
				}
			}
		}
	}

	for (i32 i = 0; i < arrlen(disk); i++) {
		// printf("%d - %d\n", i, disk[i]);
		if (disk[i] != -1)
			ans += i * disk[i];
	}

    printf("p2: %ld\n", ans);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
