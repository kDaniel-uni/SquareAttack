/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise  EXOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
void AddRoundKey(unsigned int *state,unsigned int* RoundKey){
  int Nb = 4; //peut etre egal à 4 6 ou 8
  int Nr = 4; //nombre de round
  int i,j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
    }
  }
}

// The round transformation is composed of four different transformations
void Round(unsigned int* State, unsigned int* RoundKey)  {
   Rcon(State); // The  ByteSub  Transformation  is  a  non-linear  byte  substitution,  operating  on  each  of  the  State  bytes  independently.
   RotWord(State); // In  ShiftRow,  the  rows  of  the  State  are  cyclically  shifted  over  different  offsets.
   SubWord(State); // In  MixColumn,  the  columns  of  the  State  are  considered  as  polynomials  over  GF(28)  and  multiplied modulo x4 + 1 with a fixed polynomial c(x), given by c(x) = ‘03’ x3 + ‘01’ x2 + ‘01’ x+ ‘02’ .
   AddRoundKey(State,RoundKey);
}


// The final round of the cipher is slightly different
void FinalRound(unsigned int* State, unsigned int* RoundKey)  {
  Rcon(State) ;
  RotWord(State) ;
  AddRoundKey(State,RoundKey);
}


void AES (unsigned int* State,unsigned int* CipherKey)  {
  KeyExpansion(CipherKey,ExpandedKey) ;
  AddRoundKey(State,ExpandedKey);
  for(int  i=1 ; i<Nr ; i++ ){
    Round(State,ExpandedKey + Nb*i) ;
  }
  FinalRound(State,ExpandedKey + Nb*Nr);
}
