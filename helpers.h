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


column Shift(column column, int shiftNb = 1, bool isReverse = false);

column SBox(column column, bool isReverse = false);

column Rcon(unsigned int index);

tableau2D ParseKey(key key);

key ParseTableau(tableau2D tableau);

column ArrayXor(column first, column second);

key concat(key destination, key toConcat);

void printTableau(tableau2D tab);

void printVector(std::vector<uint8_t> vec);

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::setw(2) << std::setfill('0') << std::hex << (int)hs.c);
}

inline HexCharStruct hex(uint8_t _c)
{
	return HexCharStruct(_c);
}

tableau2D createState(std::string plainText);

#endif