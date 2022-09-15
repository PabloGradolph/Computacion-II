#include <iostream>
using namespace std;

int main(){
  // Pide que se escriba un número en la terminal
  cout << "Escribe un entero: ";

  // Declaración de variable para almacenar el entero
  int innum;

  // Gurada el número dado
  cin >> innum;

  // Escribe la división entre 2
  cout << innum << "/2=" << innum/2 << endl;

  return 0;
}