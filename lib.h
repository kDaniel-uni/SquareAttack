typedef unsigned int uint;
typedef uint tableau2D[4][4] ;

/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise  EXOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
void AddRoundKey(tableau2D *state,uint* RoundKey){
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

void ShiftRow(tableau2D* state){
  unsigned int  decalage;

// Rotate first row 1 columns to left
  decalage           = (*state)[0][1];
  (*state)[0][1] = (*state)[1][1];
  (*state)[1][1] = (*state)[2][1];
  (*state)[2][1] = (*state)[3][1];
  (*state)[3][1] = decalage;

  // Rotate second row 2 columns to left
  decalage           = (*state)[0][2];
  (*state)[0][2] = (*state)[2][2];
  (*state)[2][2] = decalage;

  decalage           = (*state)[1][2];
  (*state)[1][2] = (*state)[3][2];
  (*state)[3][2] = decalage ;

  // Rotate third row 3 columns to left
  decalage          = (*state)[0][3];
  (*state)[0][3] = (*state)[3][3];
  (*state)[3][3] = (*state)[2][3];
  (*state)[2][3] = (*state)[1][3];
  (*state)[1][3] = decalage ;
}

void MixColumn(tableau2D* state){
  return ;
}

// The round transformation is composed of four different transformations
void Round(tableau2D* State, uint* RoundKey)  {
   ByteSub(State); // The  ByteSub  Transformation  is  a  non-linear  byte  substitution,  operating  on  each  of  the  State  bytes  independently.
   ShiftRow(State); // In  ShiftRow,  the  rows  of  the  State  are  cyclically  shifted  over  different  offsets.
   MixColumn(State); // In  MixColumn,  the  columns  of  the  State  are  considered  as  polynomials  over  GF(28)  and  multiplied modulo x4 + 1 with a fixed polynomial c(x), given by c(x) = ‘03’ x3 + ‘01’ x2 + ‘01’ x+ ‘02’ .
   AddRoundKey(State,RoundKey);
}


// The final round of the cipher is slightly different
void FinalRound(tableau2D* State, uint* RoundKey)  {
  ByteSub(State) ;
  ShiftRow(State) ;
  AddRoundKey(State,RoundKey);
}


void AES (tableau2D* State,uint* CipherKey)  {
  KeyExpansion(CipherKey,ExpandedKey) ;
  AddRoundKey(State,ExpandedKey);
  for(int  i=1 ; i<Nr ; i++ ){
    Round(State,ExpandedKey + Nb*i) ;
  }
  FinalRound(State,ExpandedKey + Nb*Nr);
}
