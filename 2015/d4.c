#include "common.h"

#include <openssl/md5.h>

void p1()
{
	u64 i, j;
	char istr[1024];
	char hstr[1024];
	char ostr[1024];
    char input[128];

	assert(sizeof(hstr) >= MD5_DIGEST_LENGTH);

    bfgets(input, sizeof input, stdin);

	for (i = 0; ; i++) {
		memset(istr, 0, sizeof istr);
		memset(hstr, 0, sizeof hstr);
		memset(ostr, 0, sizeof ostr);

		snprintf(istr, sizeof istr, "%s%ld", input, i);

		MD5((const unsigned char *)istr, strlen(istr), (unsigned char *)hstr);

		for (j = 0; j < 16; j++)
			snprintf(ostr + (j * 2), sizeof(ostr) - (j * 2), "%02x", (unsigned int)hstr[j]);

		if (strncmp(ostr, "00000", 5) == 0)
			break;
	}

	printf("p1: %ld\n", i);
}

void p2()
{
	u64 i, j;
	char istr[1024];
	char hstr[1024];
	char ostr[1024];
    char input[128];

	assert(sizeof(hstr) >= MD5_DIGEST_LENGTH);

    bfgets(input, sizeof input, stdin);

	for (i = 0; ; i++) {
		memset(istr, 0, sizeof istr);
		memset(hstr, 0, sizeof hstr);
		memset(ostr, 0, sizeof ostr);

		snprintf(istr, sizeof istr, "%s%ld", input, i);

		MD5((const unsigned char *)istr, strlen(istr), (unsigned char *)hstr);

		for (j = 0; j < 16; j++)
			snprintf(ostr + (j * 2), sizeof(ostr) - (j * 2), "%02x", (unsigned int)hstr[j]);

		if (strncmp(ostr, "000000", 6) == 0)
			break;
	}

	printf("p2: %ld\n", i);
}

int main(int argc, char **argv)
{
    p1();
    rewind(stdin);
    p2();
    return 0;
}
