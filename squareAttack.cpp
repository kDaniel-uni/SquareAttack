/**
 * Projet tutoré SquareAttack
 **/

#include "squareAttack.h"
#include "AES.h"

uint8_t fill = 0xf2;

deltaSet setup(key cypherKey) {
	deltaSet set;
	for (uint16_t i = 0x00; i < 0x0100; i++) {

		tableau2D buffer;
		buffer.push_back({ (uint8_t)i, fill, fill, fill });

		for (int i = 0; i < 3; i++) {

			buffer.push_back({ fill, fill, fill, fill });
		}

		buffer = AES(buffer, cypherKey, false, 3);

		set.push_back(buffer);
	}
	return set;
}