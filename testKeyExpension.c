/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	char test[4] = { 0x12, 0xFF, 0xF8, 0xE1 };
	printf("%02x %02x %02x %02x\n", test[0], test[1], test[2], test[3]);
	RotWord(test);
	printf("%02x %02x %02x %02x\n", test[0], test[1], test[2], test[3]);

	return 0;
}