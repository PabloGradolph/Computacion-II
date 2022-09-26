#include <iostream>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Información de la clase: https://www.techsoftpl.com/matrix/doc/manual.htm
int main(){

  // Definimos una matriz
  int nrows=2, ncols=3;
  matrix<double> A(nrows,ncols);

  cout << "Elemento (0,0) = " << A(0,0) << endl;

  return 0;
}
