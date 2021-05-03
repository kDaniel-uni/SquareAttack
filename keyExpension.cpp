/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber) {

    tableau2D columns;

    column buffer = previousKey[3];

    buffer = Shift(buffer);

    buffer = SBox(buffer);

    column xorBuffer;
    xorBuffer = ArrayXor(buffer, previousKey[0]);

    columns.push_back(ArrayXor( Rcon(roundNumber), xorBuffer));

    for (size_t index = 1; index < 4; index++) {
        columns.push_back(ArrayXor(columns[index - 1], previousKey[index]));
    }

    return columns;
}

key KeyExpension(key originKey, int nbOfRound) {

    size_t size = originKey.size();

    assert(size <= 16);

    if (size < 16) {
        for (int i = size; i < 16; i++) {
            originKey.push_back(0x00);
        }
    }

    key finalKey = originKey;

    tableau2D previousRoundKey = ParseKey(originKey);

    for (int roundIndex = 1; roundIndex < nbOfRound + 1; roundIndex++) {
        previousRoundKey = NextRoundKey(previousRoundKey, roundIndex);

        key parsed = ParseTableau(previousRoundKey);

        finalKey = concat(finalKey, parsed);
    }

    return finalKey;
}
