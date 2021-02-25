void ExpandedKey(K[],W[]){
int NK = 8 ;
for (j= 0;j < Nk;j+ +){
  for (i= 0;i <4;i+ +){
    W[i, j] =K[i, j];
  }
}
for (j=Nk;j <4(nr+ 1);j++){
  if (j%Nk== 0){
    W[0, j] = W[0, j−Nk]^SubByte(W[1, j−1])⊕RC[j/Nk];
    for (i= 1;i <4;i+ +){
      W[i, j] =W[i, j−Nk]^SubByte(W[i+ 1 % 4, j−1]);
    }
  else if ( ( j % Nk) == 4 ){
    for (i= 0;i <4;i+ +){
      W[i, j] =W[i, j−Nk]^SubByte(W[i, j−1]);
    }
  }
  else
    for (i= 0;i <4;i+ +){
      W[i, j] =W[i, j−Nk]^W[i, j−1];
    }
  }
}

void SubByte () ;


/* In  this  operation,  a  Round  Key  is  applied  to  the  State  by  a  simple  bitwise  EXOR.
The  Round  Key is derived from the Cipher Key by means of the key schedule.
The Round Key length is equal to the block length Nb.
*/
void AddRoundKey(unsigned int *state,unsigned int* RoundKey){
  int Nb = 4; //peut etre egal à 4 6 ou 8
  int round = 4;
  int i,j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
    }
  }
}





Round(State,RoundKey)  {
   ByteSub(State);
   ShiftRow(State);
   MixColumn(State);
   AddRoundKey(State,RoundKey);
}

FinalRound(State,RoundKey)  {
  ByteSub(State) ;
  ShiftRow(State) ;
  AddRoundKey(State,RoundKey);
}

AES (State,CipherKey)  {
  KeyExpansion(CipherKey,ExpandedKey) ;
  AddRoundKey(State,ExpandedKey);
  For( i=1 ; i<Nr ; i++ ){
    Round(State,ExpandedKey + Nb*i) ;
  }
  FinalRound(State,ExpandedKey + Nb*Nr);
}
