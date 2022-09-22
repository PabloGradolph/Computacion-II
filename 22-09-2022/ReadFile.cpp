#include <iostream> // para salida/entrada por terminal
#include <fstream>  // para salida/entrada por fichero
#include <string>   // librería específica para caracteres
using namespace std;

int main(){
  // Definimos el nombre del fichero a leer
  string infile = "matrix.txt";
  ifstream ffin(infile);
  if (ffin.is_open()){
    // Leemos la línea de encabezado
    string header;
    getline(ffin,header);
    cout << "Encabezado: " << header << endl;

    // Leemos los enteros
    int ii=1;
    string row;
    while (getline(ffin, row)){
      ++ii;
      cout << "Números en línea " << ii << " = " << row << endl;
    }

    ffin.close();
  } else cout << "No se ha podido abrir el fichero " << infile << endl;

  return 0;
}