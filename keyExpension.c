/**
 * Projet tutoré SquareAttack
 **/

#include "keyExpension.h"

void RotWord(char word[4]) {
	char buffer = word[0];
	word[0] = word[1];
	word[1] = word[2];
	word[2] = word[3];
	word[3] = buffer;
}