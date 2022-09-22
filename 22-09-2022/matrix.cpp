#include <iostream> // para salida/entrada por terminal
#include <fstream>  // para salida/entrada por fichero
#include <string>   // librería específica para caracteres
using namespace std;

int main(){
  // Define una matriz 2x3
  int matrix[2][3] = {{1, 2, 3}, {3, 4, 3}};
  
  // Definimos el fichero de salida y lo abrimos
  string infile = "matrix.txt";
  ofstream ff(infile);
  if (ff.is_open()){
    ff << "# Matriz" << endl;

    // Escribimos los elementos de las filas separados por un espacio
    // y cada fila en una nueva línea
    for (int i=0; i<2; i++){
        for (int j=0; j<3; j++){
            if (i==1 && j==0){
                ff<<endl;
            }
            ff << matrix[i][j] << "\t";
        }
    }
    
    // Cerramos el fichero
    cout << "Generated file: " << infile << endl;
    ff.close();
  } else cout << "The file can not be open: " << infile << endl;

  return 0;
}