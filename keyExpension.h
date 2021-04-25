/**
 * Projet tutoré SquareAttack
 **/

#ifndef __KEYEXPENSION_H__
#define __KEYEXPENSION_H__

#include "tools.h"

void SBox(uint8_t word);

column RotWord(column column);

column SubWord(column column);

column Rcon(unsigned int index);

key KeyExpension(key key);

tableau2D ParseKey(key key);

key ParseTableau(tableau2D tableau);

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber);

column ArrayXor(column first, column second);

void concat(key destination, key toConcat);

#endif