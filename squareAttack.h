/**
 * Projet tutoré SquareAttack
 **/

#ifndef __SQUAREATTACK_H__
#define __SQUAREATTACK_H__

#include "helpers.h"

lambdaSet setup(key cypherKey, int nbOfRound);

key reverseState(lambdaSet cypher, uint8_t guess, size_t pos);

bool checkKeyGuess(key reversed);

std::vector<uint8_t> checkAllKeyGuess(lambdaSet set, size_t pos);
#endif
