#include <stdio.h>
#include <string.h>

typedef unsigned char U8 ;
typedef U8 tableau2D[4][4] ;

static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
// get the value of the pseudo matrix
U8 getSBoxValue(U8 num)
{
  return sbox[num];
}

/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise XOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
void AddRoundKey(tableau2D *state,tableau2D* RoundKey){
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
U8 bitmelange(U8 bit)
{
  return ((bit<<3) ^ (bit>>2)) ;
}

// MixColumns function mixes the columns of the state matrix
void MixColumn(tableau2D *state){
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
void SubBytes(tableau2D *state)
{
  U8 i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getSBoxValue(*state)[j][i]);
    }
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void InvSubBytes(tableau2D *state)
{
  U8 i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      //(*state)[j][i] = ... ; // not finish
    }
  }
}

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
void InvMixColumns(tableau2D *state)
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
void Round(tableau2D *State, U8 *RoundKey)  {
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


void AES (tableau2D* State,U8* CipherKey,U8* ExpandedKey)  {
  int Nb = 4;
  int Nr = 10;
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
