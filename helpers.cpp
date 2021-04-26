/**
 * Projet tutoré SquareAttack
 **/

#include "helpers.h"

column Shift(column srcColumn, unsigned int shiftNb, bool isReverse) {

    for (size_t i = 0; i < shiftNb; i++) {
        if (isReverse) {
            srcColumn.insert(srcColumn.begin(), srcColumn.back());
            srcColumn.erase(srcColumn.end());
        }
        else {
            srcColumn.push_back(srcColumn.front());
            srcColumn.erase(srcColumn.begin());
        }
    }

    return srcColumn;
}

column SBox(column column, bool isReverse) {

    for (size_t i = 0; i < column.size(); i++) {
        uint8_t high = column[i] >> 4;
        uint8_t low = column[i] & 0x0F;
        if (isReverse) {
            column[i] = comparison_table_reverse[high * 16 + low];
        }
        else {
            column[i] = comparison_table[high * 16 + low];
        }
    }

    return column;
}

column Rcon(unsigned int index) {

    assert(index < 256);
    column column = { rconTable[index], 0x00, 0x00, 0x00 };
    return column;
}

uint8_t LookupTable(uint8_t index, int tableIndex) {
    assert(index < 256);
    uint8_t result = 0x00;
    if (tableIndex == 1) {
        result = index;
    }
    else if (tableIndex == 2) {
        result = rcon2[(unsigned int)index];
    }
    else if (tableIndex == 3) {
        result = rcon3[(unsigned int)index];
    }
    else if (tableIndex == 9) {
        result = rcon9[(unsigned int)index];
    }
    else if (tableIndex == 11) {
        result = rcon11[(unsigned int)index];
    }
    else if (tableIndex == 13) {
        result = rcon13[(unsigned int)index];
    }
    else if (tableIndex == 14) {
        result = rcon14[(unsigned int)index];
    }

    return result;
}

tableau2D ParseKey(key srcKey) {

    tableau2D parsedKey;

    for (int index = 0; index < 4; index++) {

        column sub_key = { srcKey[4 * index], srcKey[4 * index + 1], srcKey[4 * index + 2], srcKey[4 * index + 3] };
        parsedKey.push_back(sub_key);

    }

    return parsedKey;
}

tableau2D ParseKeyRows(key srcKey) {

    tableau2D parsedKey;

    for (int index = 0; index < 4; index++) {

        column sub_key = { srcKey[index], srcKey[index + 4], srcKey[index + 8], srcKey[index + 12] };
        parsedKey.push_back(sub_key);

    }

    return parsedKey;
}

key ParseTableau(tableau2D tableau) {

    key result;

    for (int index = 0; index < 4; index++) {
        result = concat(result, tableau[index]);
    }

    return result;
}

key ParseTableauRows(tableau2D tableau) {

    key result = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    for (int index = 0; index < 4; index++) {
        result[index] = tableau[index][0];
        result[index + 4] = tableau[index][1];
        result[index + 8] = tableau[index][2];
        result[index + 12] = tableau[index][3];
    }

    return result;
}

column ArrayXor(column first, column second) {

    assert(first.size() == second.size());

    column xorResult;

    for (size_t index = 0; index < first.size(); index++) {
        xorResult.push_back((uint8_t)(first[index] ^ second[index]));
    }

    return xorResult;
}

key concat(key destination, key toConcat) {

    destination.insert(destination.end(), toConcat.begin(), toConcat.end());

    return destination;
}

void printTableau(tableau2D tab) {
    for (size_t i = 0; i < tab.front().size(); i++) {
        for (auto it = tab.begin(); it != tab.end(); it++) {
            std::cout << hex((*it)[i]) << " ";
        }
        std::cout << std::endl;
    }
}

void printVector(std::vector<uint8_t> vec) {

    for (auto it = vec.begin(); it != vec.end(); it++)
        std::cout << hex(*it) << " ";
    std::cout << std::endl;
}

tableau2D createState(std::string plainText) {
    assert(plainText.size() <= 16);

    tableau2D state;

    for (size_t columnIndex = 0; columnIndex < 4; columnIndex++) {
        column col;
        for (size_t wordIndex = 0; wordIndex < 4; wordIndex++) {
            col.push_back(plainText[4 * columnIndex + wordIndex]);
        }
        state.push_back(col);
    }

    return state;
}

column mixCol(column srcCol, bool isReverse) {
    uint8_t buffer;
    for (size_t i = 0; i < 4; i++) {
        for (size_t matrixIndex = 0; matrixIndex < 4; matrixIndex++) {
            if (isReverse) {
                buffer = LookupTable(srcCol[matrixIndex], decypherMatrix[i * 4 + matrixIndex]);
            }
            else {
                buffer = LookupTable(srcCol[matrixIndex], cypherMatrix[i * 4 + matrixIndex]);
            }
            srcCol[i] ^= buffer;
        }
    }
    return srcCol;
}

key getNextRoundKey(key* srcKey) {
    key nextKey;
    for (size_t i = 0; i < 16; i++) {
        nextKey.push_back(srcKey->front());
        srcKey->erase(srcKey->begin());
    }
    return nextKey;
}

