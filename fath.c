#include <stdio.h>
int main(){
  float fath,wendu;
  int lower,upper,step;
  lower = 0;
  upper = 300;
 step = 20;
  fath = lower;
 while(fath <= upper){
  wendu = (5.0/9.0)* (fath - 32);
  printf("%3.0f %6.1f \n",fath,wendu);
  fath += step; 
}


}

