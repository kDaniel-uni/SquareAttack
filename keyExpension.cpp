/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber) {

    tableau2D columns;

    column buffer = previousKey[3];

    buffer = RotWord(buffer);

    buffer = SubWord(buffer);

    column xorBuffer;
    xorBuffer = ArrayXor(buffer, previousKey[0]);

    columns.push_back(ArrayXor( Rcon(roundNumber), xorBuffer));

    for (size_t index = 1; index < 4; index++) {
        columns.push_back(ArrayXor(columns[index - 1], previousKey[index]));
    }

    return columns;
}

key KeyExpension(key originKey) {

    assert(originKey.size() == 16);

    key finalKey = originKey;

    tableau2D previousRoundKey = ParseKey(originKey);

    for (int roundIndex = 1; roundIndex < 11; roundIndex++) {
        printf("Entered loop nb : %i\n", roundIndex);
        previousRoundKey = NextRoundKey(previousRoundKey, roundIndex);

        key parsed = ParseTableau(previousRoundKey);

        finalKey = concat(finalKey, parsed);
    }

    return finalKey;

    
}
