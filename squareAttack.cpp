/**
 * Projet tutoré SquareAttack
 **/

#include "squareAttack.h"
#include "AES.h"

lambdaSet setup(key cypherKey, int nbOfRound) {
	lambdaSet set;

	srand(time(NULL));
	uint8_t fill = (uint8_t)(rand()%256);

	for (uint16_t i = 0x00; i < 0x0100; i++) {

		tableau2D buffer;
		buffer.push_back({ (uint8_t)i, fill, fill, fill });

		for (int i = 0; i < 3; i++) {

			buffer.push_back({ fill, fill, fill, fill });
		}

		buffer = AES(buffer, cypherKey, false, nbOfRound);

		set.push_back(buffer);
	}
	return set;
}

lambdaSet setup(key cypherKey, int nbOfRound, uint8_t fill) {
	lambdaSet set;

	for (uint16_t i = 0x00; i < 0x0100; i++) {

		tableau2D buffer;
		buffer.push_back({ (uint8_t)i, fill, fill, fill });

		for (int i = 0; i < 3; i++) {

			buffer.push_back({ fill, fill, fill, fill });
		}

		buffer = AES(buffer, cypherKey, false, nbOfRound);

		set.push_back(buffer);
	}
	return set;
}

key reverseState(lambdaSet cypher, uint8_t guess, size_t pos) {
	key res;
	for (size_t i = 0; i < cypher.size(); i++) {
		uint8_t buffer = guess ^ cypher[i][pos / 4][pos % 4];
		//printf("%i : POS %u : colone %u : ligne %u\n", cypher[i][pos / 4][pos % 4], i, pos/4, pos%4);
		res.push_back(SBox(buffer, true));
	}
	return res;
}

bool checkKeyGuess(key reversed) {
	uint8_t xorBuffer = 0x00;
	for (size_t i = 0; i < reversed.size(); i++) {
		xorBuffer ^= reversed[i];
	}

	if (xorBuffer != 0x00) {
		return false;
	}

	return true;
}

std::vector<uint8_t> checkAllKeyGuess(lambdaSet set, size_t pos) {

	std::vector<uint8_t> guesses;

	for (size_t i = 0x00; i < 0x100; i++) {
		if (checkKeyGuess(reverseState(set, i, pos))) {
			guesses.push_back(i);
		}
	}

	return guesses;
}
