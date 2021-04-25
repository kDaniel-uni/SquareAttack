/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"
#include "tools.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	column test = { 0x01, 0x2d, 0xc2, 0x9e };

	printVector(test);

	test = RotWord(test);

	printVector(test);

	test = SubWord(test);
	
	printVector(test);

	printf("\n\n");

	key testKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	for (size_t index = 0; index < testKey.size(); index++) {
		printf("%02x", testKey[index]);
	}
	printf("\n");
	key result = KeyExpension(testKey);

	for (size_t index = 0; index < result.size(); index++) {
		printf("%02x", result[index]);
		if (((index + 1) % 16) == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}