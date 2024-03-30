#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

typedef int8_t     i8;
typedef int16_t    i16;
typedef int32_t    i32;
typedef int64_t    i64;
typedef uint8_t    u8;
typedef uint16_t   u16;
typedef uint32_t   u32;
typedef uint64_t   u64;
typedef float      f32;
typedef double     f64;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

char *bfgets(char *s, size_t n, FILE *fp)
{
    char *t = fgets(s, n, fp);
    if (t != NULL) {
        s[strlen(s) - 1] = 0;
    }
    return t;
}

#define ARRSIZE(x) (sizeof((x))/sizeof((x)[0]))
#define SWAP(a, b) do { typeof((a)) z_ = (b); (b) = (a); (a) = z_; } while (0);

#define streq(a, b) (strcmp((a), (b)) == 0 && strlen((a)) == strlen((b)))

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    for (char *e = s + strlen(s) - 1; isspace(*e); e--)
        *e = 0;
    return s;
}

char *trim(char *s)
{
    return ltrim(rtrim(s));
}

i32 *find_all_i32s(char *s)
{
    i32 v = 0;
    size_t len = 0, tlen = 0;
    i32 *arr = NULL;

    while (sscanf(s + len, " %d%ln", &v, &tlen) == 1) {
        arrput(arr, v);
        len += tlen;
    }

    return arr;
}

i64 *find_all_i64s(char *s)
{
    i64 v = 0;
    size_t len = 0, tlen = 0;
    i64 *arr = NULL;

    while (sscanf(s + len, " %ld%ln", &v, &tlen) == 1) {
        arrput(arr, v);
        len += tlen;
    }

    return arr;
}

f32 *find_all_f32s(char *s)
{
    f32 v = 0;
    size_t len = 0, tlen = 0;
    f32 *arr = NULL;

    while (sscanf(s + len, " %f%ln", &v, &tlen) == 1) {
        arrput(arr, v);
        len += tlen;
    }

    return arr;
}

f64 *find_all_f64s(char *s)
{
    f64 v = 0;
    size_t len = 0, tlen = 0;
    f64 *arr = NULL;

    while (sscanf(s + len, " %lf%ln", &v, &tlen) == 1) {
        arrput(arr, v);
        len += tlen;
    }

    return arr;
}

char **find_all_strs_sep(char *s, char *sep)
{
    char **arr = NULL;
    for (char *t = strtok(s, sep); t; t = strtok(NULL, sep)) {
        arrput(arr, t);
    }
    return arr;
}

char **find_all_strs(char *s)
{
    return find_all_strs_sep(s, " ");
}

#endif // COMMON_H_
