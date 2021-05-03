/**
 * Projet tutoré SquareAttack
 **/

#include "squareAttack.h"
#include "AES.h"

lambdaSet setup(key cypherKey, int nbOfRound) {
	lambdaSet set;

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

key reverseState(lambdaSet cypher, uint8_t guess, size_t pos) {
	key res;
	for (size_t i = 0; i < cypher.size(); i++) {
		cypher[i][pos / 4][pos % 4] ^= guess;
		printf("%i ", cypher[i][pos / 4][pos % 4]);
		cypher[i] = SubBytes(ShiftRow(cypher[i], true), true);
		res.push_back(cypher[i][pos / 4][pos % 4]);
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