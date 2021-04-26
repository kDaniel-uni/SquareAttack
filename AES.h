/**
 * Projet tutoré SquareAttack
 **/

#ifndef __AES_H__
#define __AES_H__

#include "helpers.h"

tableau2D AddRoundKey(tableau2D state, tableau2D RoundKey);

tableau2D ShiftRow(tableau2D state, bool isReverse = false);

// MixColumns function mixes the columns of the state matrix
tableau2D MixColumns(tableau2D state, bool isReverse);

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
tableau2D SubBytes(tableau2D state, bool isReverse);

// The round transformation is composed of four different transformations
tableau2D Round(tableau2D state, tableau2D roundKey, bool isReverse = false);

// The final round of the cipher is slightly different
tableau2D FinalRound(tableau2D state, tableau2D roundKey, bool isReverse = false);

tableau2D AES(tableau2D State, key cipherKey, bool isDecipher = false);

#endif
