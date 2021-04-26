#include "AES.h"
#include "keyExpension.h"

/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise XOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
tableau2D AddRoundKey(tableau2D state, tableau2D RoundKey){
    tableau2D result ;
    for (size_t i = 0; i < 4; i++) {
      column test = ArrayXor(state[i], RoundKey[i]);
      result.push_back(test);
    }

    return result;
}

tableau2D ShiftRow(tableau2D state){

    key buffer = ParseTableau(state);

    tableau2D rowsTab = ParseKeyRows(buffer);

    for (size_t i = 0; i < 4; i++) {
        Shift(rowsTab[i], i);
    }

    buffer = ParseTableauRows(rowsTab);

    return ParseKey(buffer);
}

// MixColumns function mixes the columns of the state matrix
tableau2D MixColumns(tableau2D state, bool isReverse){

    for (size_t i = 0; i < 4; i++) {
        state[i] = mixCol(state[i], isReverse);
    }

    return state;
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
tableau2D SubBytes(tableau2D state, bool isReverse)
{
    for (size_t i = 0; i < 4; i++) {
        SBox(state[i], isReverse);
    }

    return state;
}


// The round transformation is composed of four different transformations
tableau2D Round(tableau2D state, tableau2D roundKey)  {
   state = SubBytes(state, false); // The  ByteSub  Transformation  is  a  non-linear  byte  substitution,  operating  on  each  of  the  State  bytes  independently.
   state = ShiftRow(state); // In  ShiftRow,  the  rows  of  the  State  are  cyclically  shifted  over  different  offsets.
   state = MixColumns(state, false); // In  MixColumn,  the  columns  of  the  State  are  considered  as  polynomials  over  GF(28)  and  multiplied modulo x4 + 1 with a fixed polynomial c(x), given by c(x) = ‘03’ x3 + ‘01’ x2 + ‘01’ x+ ‘02’ .
   state = AddRoundKey(state, roundKey);
   return state;
}


// The final round of the cipher is slightly different
tableau2D FinalRound(tableau2D state, tableau2D roundKey)  {
    state = SubBytes(state, false) ;
    state = ShiftRow(state) ;
    state = AddRoundKey(state, roundKey);
    return state;
}


tableau2D AES (tableau2D state, key cipherKey)   {
  int Nr = 10;
  key expandedKey = KeyExpension(cipherKey);

  state = AddRoundKey(state, ParseKey(getNextRoundKey(&expandedKey)));
  for(int  i=1 ; i<Nr ; i++ ){
    state = Round(state, ParseKey(getNextRoundKey(&expandedKey))) ;
  }
  state = FinalRound(state, ParseKey(getNextRoundKey(&expandedKey)));

  return state;
}
