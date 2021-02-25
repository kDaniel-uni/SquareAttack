/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	unsigned char test[4] = { 0x01, 0x2d, 0xc2, 0x9e };
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);
	RotWord(test);
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);

	SubWord(test);
	printf("%hhX %hhX %hhX %hhX\n", test[0], test[1], test[2], test[3]);

	return 0;
}