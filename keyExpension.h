/**
 * Projet tutoré SquareAttack
 **/

#ifndef __KEYEXPENSION_H__
#define __KEYEXPENSION_H__

typedef unsigned char U8;
typedef U8** tableau2D;

void SBox(U8 word);

void RotWord(U8 word[4]);

void SubWord(U8 word[4]);

U8* Rcon(unsigned int index);

U8* KeyExpension(U8* key);

tableau2D ParseKey(U8* key);

U8* ParseTableau(tableau2D tableau);

tableau2D NextRoundKey(tableau2D previousKey, int roundNumber);

U8* ArrayXor(U8* first, U8* second);

U8* concat(U8* str1, U8* str2);


#endif