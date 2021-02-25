/**
 * Projet tutoré SquareAttack
 **/

#ifndef __KEYEXPENSION_H__
#define __KEYEXPENSION_H__

void KeyExpension();

void RotWord(unsigned char word[4]);

void SubWord(unsigned char word[4]);

void Rcon();

void SBox(unsigned char word);

#endif