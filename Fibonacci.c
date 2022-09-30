#include <stdio.h>



int seqfib(int n1, int n2, int i){

  if (i <= 0){

    return 0;

  }

  else if(i == 1){

    return n1;

  }

  else if(i == 2){

    return n2;

  }

  else{

    int tempn2 = n2;



    n2 = n1+n2;

    n1 = tempn2;



    i--;

    seqfib(n1, n2, i);

  }

}



int main()

{

  printf("8: %d", seqfib(1, 2, 8));



  return 0;

}
