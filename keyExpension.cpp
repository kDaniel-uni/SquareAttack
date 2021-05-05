/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber) {

    tableau2D columns;

    column buffer = previousKey[3];

    buffer = Shift(buffer);

    buffer = SBoxCol(buffer);

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

key KeyExpensionReverse(key lastKey, int nbOfRound) {

    size_t size = lastKey.size();

    assert(size <= 16);

    if (size < 16) {
        for (int i = size; i < 16; i++) {
            lastKey.push_back(0x00);
        }
    }

    tableau2D previousRoundKey = ParseKey(lastKey);

    for (int roundIndex = nbOfRound; roundIndex > 0; roundIndex--) {
        previousRoundKey = NextRoundKeyReverse(previousRoundKey, roundIndex);
    }

    return ParseTableau(previousRoundKey);
}


tableau2D NextRoundKeyReverse(tableau2D currentKey, int roundNumber) {

    tableau2D tab;

    for (size_t index = 3; index > 0; index--) {
        tab.insert(tab.begin(), ArrayXor(currentKey[index - 1], currentKey[index]));
    }

    column beforeRcon = ArrayXor(Rcon(roundNumber), currentKey[0]);

    column buffer = tab[2];

    buffer = Shift(buffer, 1);

    buffer = SBoxCol(buffer);

    tab.insert(tab.begin(), ArrayXor(buffer, beforeRcon));

    return tab;
}