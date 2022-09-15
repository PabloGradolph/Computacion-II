//Función con vector como parámetro
#include <iostream>
using namespace std;

void elementos(const double vect[], const int len){
    // Escribe los elementos del vector
    for (int i=0; i<len; ++i){
        cout << "Elemento " << i << " = " << vect[i] << endl;
    }
}

void caracteres(char vect2[], const int len){
    // Escribe los elementos del vector
    for (int i=0; i<len; ++i){
        cout << "Elemento " << i << " = " << vect2[i] << endl;
    }
}

int main(){
  // Declara un vector
  int len = 4;
  double vect[len] = {24.3, -56.2, 304, 0.1};
  // Char solo para un caracter. Para palabras usar la librería string
  char vect2[len] = {'a', 'n', 'P', 'J'};

  // Utiliza el vector como argumento para la función
  elementos(vect, len);
  caracteres(vect2, len);

  return 0;
}