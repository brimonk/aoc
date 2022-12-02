#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <openssl/md5.h>

#define PUZZLE_INPUT "ckczppom"

int main(int argc, char **argv)
{
	long i, j;
	char istr[1024];
	char hstr[1024];
	char ostr[1024];

	assert(sizeof(hstr) >= MD5_DIGEST_LENGTH);

	for (i = 0; ; i++) {
		memset(istr, 0, sizeof istr);
		memset(hstr, 0, sizeof hstr);
		memset(ostr, 0, sizeof ostr);

		snprintf(istr, sizeof istr, PUZZLE_INPUT "%ld", i);

		MD5((const unsigned char *)istr, strlen(istr), (unsigned char *)hstr);

		for (j = 0; j < 16; j++)
			snprintf(ostr + (j * 2), sizeof(ostr) - (j * 2), "%02x", (unsigned int)hstr[j]);

		if (strncmp(ostr, "00000", 5) == 0)
			break;
	}

	printf("lowest %ld\n", i);

	return 0;
}
