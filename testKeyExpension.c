/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	char test[4] = { 0x01, 0x2D, 0x9F, 0xE1 };
	printf("%02x %02x %02x %02x\n", test[0], test[1], test[2], test[3]);
	//RotWord(test);
	printf("%02x %02x %02x %02x\n", test[0], test[1], test[2], test[3]);

	SubWord(test);
	printf("%02x %02x %02x %02x\n", test[0], test[1], test[2], test[3]);

	return 0;
}