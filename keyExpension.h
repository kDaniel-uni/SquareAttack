/**
 * Projet tutoré SquareAttack
 **/

#ifndef __KEYEXPENSION_H__
#define __KEYEXPENSION_H__

#include "helpers.h"

key KeyExpension(key key);

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber);


#endif