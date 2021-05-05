/**
 * Projet tutoré SquareAttack
 **/

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <memory.h>
#include <iostream>


column Shift(column column, unsigned int shiftNb = 1, bool isReverse = false);

column SBoxCol(column column, bool isReverse = false);

uint8_t SBox(uint8_t byte, bool isReverse = false);

column Rcon(unsigned int index);

uint8_t LookupTable(uint8_t index, int tableIndex);

tableau2D ParseKey(key key);

tableau2D ParseKeyRows(key key);

key ParseTableau(tableau2D tableau);

key ParseTableauRows(tableau2D tableau);

column ArrayXor(column first, column second);

key concat(key destination, key toConcat);

void printTableau(tableau2D tab);

void printVector(std::vector<uint8_t> vec);

void printDeltaSet(lambdaSet set);

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::setw(2) << std::setfill('0') << std::hex << (int)hs.c);
}

inline HexCharStruct hex(uint8_t _c)
{
	return HexCharStruct(_c);
}

tableau2D createState(std::string plainText);

std::string reverseCypher(tableau2D cypherText);

column mixCol(column toMix, bool isReverse);

key getNextRoundKey(key* srcKey);

key getNextRoundKeyReverse(key* srcKey);

#endif