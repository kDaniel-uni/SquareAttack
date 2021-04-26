/**
 * Projet tutoré SquareAttack
 **/

#include "squareAttack.h"

int test_setup() {

	key cypherKey = { 0xaa, 0x00, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };

	deltaSet set = setup(cypherKey);

	//printDeltaSet(set);

	std::vector<key> keySet;
	for (size_t setindex = 0; setindex < set.size(); setindex++) {
		keySet.push_back(ParseTableau(set[setindex]));
	}

	for (size_t posIndex = 0; posIndex < 16; posIndex++) {
		uint8_t xorBuffer = 0x00;
		for (size_t setindex = 0; setindex < keySet.size(); setindex++) {
			xorBuffer ^= keySet[setindex][posIndex];
		}
		if (xorBuffer == 0x00) {
			std::cout << "All bytes xored from encrypted deltaSet on pos " << posIndex + 1 << " is equal to 0x00" << std::endl;
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("setup", argv[1]) == 0) {
		return test_setup();
	}

	return 0;
}