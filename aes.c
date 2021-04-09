typedef unsigned char U8 ;
typedef U8 tableau2D[4][4] ;

// get the value of the pseudo matrix
static U8 getSBoxValue(U8 num)
{
  return sbox[num];
}

/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise XOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
void AddRoundKey(tableau2D *state,tableau2D* RoundKey){
  int Nb = 4; //peut etre egal à 4 6 ou 8
  int i,j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= (*RoundKey)[i][j];
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

// melange d'un bit
static U8 bitmelange(U8 bit)
{
  return ((bit<<3) ^ (bit>>2)) ;
}

// MixColumns function mixes the columns of the state matrix
void MixColumn(tableau2D* state){
  {
  U8 ligne;
  U8 tmp1, tmp2;
  for (ligne = 0; ligne < 4; ligne ++)
  {
    tmp1 = (*state)[ligne][0] ^ (*state)[ligne][1] ^ (*state)[ligne][2] ^ (*state)[ligne][3] ;
    tmp2  = (*state)[ligne][0] ^ (*state)[ligne][1] ;
    tmp2 = bitmelange(tmp2);
    (*state)[ligne][0] ^= tmp2 ^ tmp1 ;
    tmp2  = (*state)[ligne][1] ^ (*state)[ligne][2] ;
    tmp2 = bitmelange(tmp2);
    (*state)[ligne][1] ^= tmp2 ^ tmp1 ;
    tmp2 = (*state)[ligne][2] ^ (*state)[ligne][3] ;
    tmp2= bitmelange(tmp2);
    (*state)[ligne][2] ^= tmp2 ^ tmp1 ;
    tmp2 = (*state)[ligne][3] ^ (*state)[ligne][0];
    tmp2= bitmelange(tmp2);
    (*state)[ligne][3] ^= tmp2^ tmp1 ;
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void SubBytes(tableau2D* state)
{
  U8 i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getValue((*state)[j][i]);
    }
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void InvSubBytes(tableau2D* state)
{
  U8 i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = ... ; // not finish
    }
  }
}

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
static void InvMixColumns(tableau2D* state)
{
  int i;
  U8 a, b, c, d;
  for (i = 0; i < 4; ++i)
  {
    a = (*state)[i][0];
    b = (*state)[i][1];
    c = (*state)[i][2];
    d = (*state)[i][3];

    (*state)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
    (*state)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
    (*state)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
    (*state)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
  }
}

// The round transformation is composed of four different transformations
void Round(tableau2D* State, U8* RoundKey)  {
   ByteSub(State); // The  ByteSub  Transformation  is  a  non-linear  byte  substitution,  operating  on  each  of  the  State  bytes  independently.
   ShiftRow(State); // In  ShiftRow,  the  rows  of  the  State  are  cyclically  shifted  over  different  offsets.
   MixColumn(State); // In  MixColumn,  the  columns  of  the  State  are  considered  as  polynomials  over  GF(28)  and  multiplied modulo x4 + 1 with a fixed polynomial c(x), given by c(x) = ‘03’ x3 + ‘01’ x2 + ‘01’ x+ ‘02’ .
   AddRoundKey(State,RoundKey);
}


// The final round of the cipher is slightly different
void FinalRound(tableau2D* State, U8* RoundKey)  {
  ByteSub(State) ;
  ShiftRow(State) ;
  AddRoundKey(State,RoundKey);
}


void AES (tableau2D* State,U8* CipherKey)  {
  KeyExpansion(CipherKey,ExpandedKey) ;
  AddRoundKey(State,ExpandedKey);
  for(int  i=1 ; i<Nr ; i++ ){
    Round(State,ExpandedKey + Nb*i) ;
  }
  FinalRound(State,ExpandedKey + Nb*Nr);
}


/* void AddRoundKey(tableau2D *state,U8* RoundKey){
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
} */
