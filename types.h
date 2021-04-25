/**
 * Projet tutoré SquareAttack
 **/

#ifndef __TYPES_H__
#define __TYPES_H__

#include <cstdint>
#include <vector>
#include <iomanip>

typedef std::vector<uint8_t> key;

typedef std::vector<uint8_t> column;

typedef std::vector<column> tableau2D;


struct HexCharStruct
{
	uint8_t c;
	HexCharStruct(uint8_t _c) : c(_c) { }
};


#endif