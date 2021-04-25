/**
 * Projet tutoré SquareAttack
 **/

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <cstdint>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <memory.h>
#include <iostream>
#include <iomanip>


typedef std::vector<uint8_t> key;

typedef std::vector<uint8_t> column;

typedef std::vector<column> tableau2D;


struct HexCharStruct
{
	uint8_t c;
	HexCharStruct(uint8_t _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::setw(2) << std::setfill('0') << std::hex << (int)hs.c);
}

inline HexCharStruct hex(uint8_t _c)
{
	return HexCharStruct(_c);
}

void printTableau(tableau2D tab);

void printVector(std::vector<uint8_t> vec);
#endif