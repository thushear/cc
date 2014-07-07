#include <stdio.h>
int main(){
  fprintf(stdout,"[%s:%d] Hello world!",__FILE__,__LINE__);
  return 0;

}

