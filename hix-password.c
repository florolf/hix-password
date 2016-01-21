#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void crypt(uint8_t *mac, char *out)
{
	char chars[] = "XEvy7cOnW1tr40AYIKm8qsTSLoz3DaCPGkBQUl5gMhw2jdFRpubNZfH9VxiJe6x";
	uint32_t factors[] = { 0x7, 0xb, 0xd, 0x11, 0x17, 0x1d, 0x1f, 0x25 };

	uint32_t buf[10], scratch[10];
	buf[0] = (uint8_t)(~mac[3]);
	buf[7] = (uint8_t)((mac[1] >> 3) | (mac[5] << 3));
	buf[8] = (uint8_t)((mac[4] >> 1) ^ (mac[3] << 2));
	buf[9] = (uint8_t)((mac[3] >> 1) & (~mac[0]));

	for(int i = 0; i < 6; i++)
		buf[1 + i] = mac[5 - i];

	memcpy(scratch, buf, sizeof(buf));

	uint32_t mask = 1;
	for(int factor = 0; factor < 8; factor++) {
		for(int i = 0; i < 10; i++) {
			if((buf[i] & mask) == 0)
				continue;

			int add = factors[factor] * (i + 1);

			for(int i = 0; i < 10; i++)
				scratch[i] += add;
		}

		mask <<= 1;
	}

	for(int i = 0; i < 10; i++)
		out[i] = chars[scratch[i] % 63];

	out[10] = 0;
}

int main(int argc, char **argv)
{
	uint8_t mac[6];
	char pwd[11];

	if(argc < 2) {
		fprintf(stderr, "usage: %s mac\n\n", argv[0]);
		fprintf(stderr, "where mac is something like 'de:ad:be:ef:12:34'\n");

		return EXIT_FAILURE;
	}

	for(int i = 0; i < 6; i++)
		mac[i] = strtoul(argv[1] + i * 3, NULL, 16);

	printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
			mac[0], mac[1], mac[2],
			mac[3], mac[4], mac[5]);

	crypt(mac, pwd);
	printf("Password: %s\n", pwd);

	return EXIT_SUCCESS;
}
