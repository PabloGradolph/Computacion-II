
#include <iostream>
using namespace std;

#include <string.h>   // L�nea 1/3 para incluir matrix.h
#include "matrix.h"   // L�nea 2/3 para incluir matrix.h
using namespace math; // L�nea 3/3 para incluir matrix.h

int main(){
  // Definimos una matriz
  int nrows=2, ncols=3;
  matrix<double> A(nrows,ncols);

  cout << "Elemento (0,0) = " << A(0,0) << endl;

  return 0;
}
