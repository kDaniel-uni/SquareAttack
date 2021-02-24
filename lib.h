void ExpandedKey(K[],W[]){
int NK = 8 ;
for (j= 0;j < Nk;j+ +){
  for (i= 0;i <4;i+ +){
    W[i, j] =K[i, j];
  }
}
for (j=Nk;j <4(nr+ 1);j++){
  if (j%Nk== 0){
    W[0, j] = W[0, j−Nk]⊕s(W[1, j−1])⊕RC[j/Nk];
    for (i= 1;i <4;i+ +){
      W[i, j] =W[i, j−Nk]⊕s(W[i+ 1 % 4, j−1]);
    }
  else if ( ( j % Nk) == 4 ){
    for (i= 0;i <4;i+ +){
      W[i, j] =W[i, j−Nk]⊕s(W[i, j−1]);
    }
  }
  else
    for (i= 0;i <4;i+ +){
      W[i, j] =W[i, j−Nk]⊕W[i, j−1];
    }
  }
}
