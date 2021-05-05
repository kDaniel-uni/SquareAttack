/**
 * Projet tutoré SquareAttack
 **/

#ifndef __KEYEXPENSION_H__
#define __KEYEXPENSION_H__

#include "helpers.h"

key KeyExpension(key key, int nbOfRound = 10);

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber);

key KeyExpensionReverse(key lastKey, int nbOfRound);

tableau2D NextRoundKeyReverse(tableau2D currentKey, int roundNumber);

#endif