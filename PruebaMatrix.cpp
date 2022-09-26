
#include <iostream>
using namespace std;

#include <string.h>   // Línea 1/3 para incluir matrix.h
#include "matrix.h"   // Línea 2/3 para incluir matrix.h
using namespace math; // Línea 3/3 para incluir matrix.h

int main(){
  // Definimos una matriz
  int nrows=2, ncols=3;
  matrix<double> A(nrows,ncols);

  cout << "Elemento (0,0) = " << A(0,0) << endl;

  return 0;
}
