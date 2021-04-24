/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	U8 test[4] = { 0x01, 0x2d, 0xc2, 0x9e };
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);
	RotWord(test);
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);

	SubWord(test);
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);

	printf("\n\n");

	U8 key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	for (int index = 0; index < strnlen(key, 16); index++) {
		printf("%02x", key[index]);
	}
	printf("\n");
	U8* result = KeyExpension(key);

	for (int index = 0; index < strnlen(result, 500); index++) {
		printf("%02x", result[index]);
		if (((index + 1) % 16) == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}