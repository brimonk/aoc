#include "common.h"

typedef enum {
    IN_SEEDS = 0,
    IN_SEED2SOIL,
    IN_SOIL2FERT,
    IN_FERT2WATR,
    IN_WATR2LITE,
    IN_LITE2TEMP,
    IN_TEMP2HUMD,
    IN_HUMD2LOCT,
} MAP_KIND;

typedef struct mapping {
    i64 source;
    i64 destination;
    i64 range_len;
} mapping;

typedef struct seed_range {
    i64 start;
    i64 range;
} seed_range;

void read_seeds(i64 **seeds, char *s)
{
    for (char *t = strtok(s, " "); t; t = strtok(NULL, " ")) {
        i64 z = atoll(t);
        arrput(*seeds, z);
    }
}

void read_seeds_2(seed_range **seeds, char *s)
{
    i64 lo = -1;

    for (char *t = strtok(s, " "); t; t = strtok(NULL, " ")) {
        i64 z = atoll(t);

        if (lo == -1) {
            lo = z;
        } else {
            i64 range = z;

            seed_range x = {
                .start = lo,
                .range = range,
            };

            arrput(*seeds, x);

            lo = -1;
        }

    }
}

void read_range_map(mapping **map, char *s)
{
    mapping z = { 0 };
    sscanf(s, "%ld %ld %ld", &z.destination, &z.source, &z.range_len);
    arrput(*map, z);
}

i64 lookup(mapping *map, i64 k)
{
    // Iterate through the passed in mapping for a key 'k' that fits within a 'source range'
    // (source <= k <= source + range_len). If one is found, compute the mapping, otherwise, return
    // k.

    for (size_t i = 0; i < arrlen(map); i++) {
        mapping curr = map[i];
        if (curr.source <= k && k < curr.source + curr.range_len) {
            // return curr.source + k - curr.destination;
            return curr.destination + k - curr.source;
        }
    }

    return k;
}

void p1()
{
    i64 ans = 0;
	char buf[1024];

    i64 *seeds = NULL;

    mapping *seed_2_soil = NULL;
    mapping *soil_2_fert = NULL;
    mapping *fert_2_watr = NULL;
    mapping *watr_2_lite = NULL;
    mapping *lite_2_temp = NULL;
    mapping *temp_2_humd = NULL;
    mapping *humd_2_loct = NULL;

	memset(buf, 0, sizeof buf);

    int in_kind = IN_SEEDS;

    while (buf == bfgets(buf, sizeof buf, stdin)) {

        if (strlen(buf) == 0) {
            in_kind++;
            continue;
        }
        if (in_kind != IN_SEEDS && !isdigit(buf[0])) {
            continue;
        }

        switch (in_kind) {
            case IN_SEEDS: {
                char *t = strchr(buf, ':') + 1;
                read_seeds(&seeds, t);
                break;
            }
            case IN_SEED2SOIL:
                read_range_map(&seed_2_soil, buf);
                break;
            case IN_SOIL2FERT:
                read_range_map(&soil_2_fert, buf);
                break;
            case IN_FERT2WATR:
                read_range_map(&fert_2_watr, buf);
                break;
            case IN_WATR2LITE:
                read_range_map(&watr_2_lite, buf);
                break;
            case IN_LITE2TEMP:
                read_range_map(&lite_2_temp, buf);
                break;
            case IN_TEMP2HUMD:
                read_range_map(&temp_2_humd, buf);
                break;
            case IN_HUMD2LOCT:
                read_range_map(&humd_2_loct, buf);
                break;
            default:
                assert(0);
        }
    }

    // scan each map for the LOWEST non-index number(?)
    int min = INT_MAX;

    for (size_t i = 0; i < arrlen(seeds); i++) {
        i64 v = seeds[i];
        // fprintf(stderr, "\tseed %ld is %ld\n", i, seeds[i]);

        v = lookup(seed_2_soil, v);
        // fprintf(stderr, "\tsoil mapping is %ld\n", v);

        v = lookup(soil_2_fert, v);
        // fprintf(stderr, "\tfert mapping is %ld\n", v);

        v = lookup(fert_2_watr, v);
        // fprintf(stderr, "\twatr mapping is %ld\n", v);

        v = lookup(watr_2_lite, v);
        // fprintf(stderr, "\tlite mapping is %ld\n", v);

        v = lookup(lite_2_temp, v);
        // fprintf(stderr, "\ttemp mapping is %ld\n", v);

        v = lookup(temp_2_humd, v);
        // fprintf(stderr, "\thumd mapping is %ld\n", v);

        v = lookup(humd_2_loct, v);
        // fprintf(stderr, "\tloct mapping is %ld\n", v);

        if (v < min) {
            min = v;
        }
    }

    ans = min;

    printf("p1: %ld\n", ans);

    arrfree(seeds);
    arrfree(seed_2_soil);
    arrfree(soil_2_fert);
    arrfree(fert_2_watr);
    arrfree(watr_2_lite);
    arrfree(lite_2_temp);
    arrfree(temp_2_humd);
    arrfree(humd_2_loct);

#undef SCAN_MAP
}

void p2()
{
    i64 ans = 0;
	char buf[1024];

    seed_range *seeds = NULL;

    mapping *seed_2_soil = NULL;
    mapping *soil_2_fert = NULL;
    mapping *fert_2_watr = NULL;
    mapping *watr_2_lite = NULL;
    mapping *lite_2_temp = NULL;
    mapping *temp_2_humd = NULL;
    mapping *humd_2_loct = NULL;

	memset(buf, 0, sizeof buf);

    int in_kind = IN_SEEDS;

    while (buf == bfgets(buf, sizeof buf, stdin)) {

        if (strlen(buf) == 0) {
            in_kind++;
            continue;
        }
        if (in_kind != IN_SEEDS && !isdigit(buf[0])) {
            continue;
        }

        switch (in_kind) {
            case IN_SEEDS: {
                char *t = strchr(buf, ':') + 1;
                read_seeds_2(&seeds, t);
                break;
            }
            case IN_SEED2SOIL:
                read_range_map(&seed_2_soil, buf);
                break;
            case IN_SOIL2FERT:
                read_range_map(&soil_2_fert, buf);
                break;
            case IN_FERT2WATR:
                read_range_map(&fert_2_watr, buf);
                break;
            case IN_WATR2LITE:
                read_range_map(&watr_2_lite, buf);
                break;
            case IN_LITE2TEMP:
                read_range_map(&lite_2_temp, buf);
                break;
            case IN_TEMP2HUMD:
                read_range_map(&temp_2_humd, buf);
                break;
            case IN_HUMD2LOCT:
                read_range_map(&humd_2_loct, buf);
                break;
            default:
                assert(0);
        }
    }

    // scan each map for the LOWEST non-index number(?)
    i64 min = LONG_MAX;

    for (size_t i = 0; i < arrlen(seeds); i++) {
        for (size_t j = seeds[i].start; j < seeds[i].start + seeds[i].range; j++) {
            // fprintf(stderr, "\tseed %ld is %ld\n", (i + 1) * j, j);

            i64 v = lookup(seed_2_soil, j);
            // fprintf(stderr, "\tsoil mapping is %ld\n", v);

            v = lookup(soil_2_fert, v);
            // fprintf(stderr, "\tfert mapping is %ld\n", v);

            v = lookup(fert_2_watr, v);
            // fprintf(stderr, "\twatr mapping is %ld\n", v);

            v = lookup(watr_2_lite, v);
            // fprintf(stderr, "\tlite mapping is %ld\n", v);

            v = lookup(lite_2_temp, v);
            // fprintf(stderr, "\ttemp mapping is %ld\n", v);

            v = lookup(temp_2_humd, v);
            // fprintf(stderr, "\thumd mapping is %ld\n", v);

            v = lookup(humd_2_loct, v);
            // fprintf(stderr, "\tloct mapping is %ld\n", v);

            if (v < min) {
                min = v;
            }
        }
    }

    ans = min;

    printf("p2: %ld\n", ans);

    arrfree(seeds);
    arrfree(seed_2_soil);
    arrfree(soil_2_fert);
    arrfree(fert_2_watr);
    arrfree(watr_2_lite);
    arrfree(lite_2_temp);
    arrfree(temp_2_humd);
    arrfree(humd_2_loct);

#undef SCAN_MAP
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
