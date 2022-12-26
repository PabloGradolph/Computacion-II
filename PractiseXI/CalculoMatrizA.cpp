#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función que calcula la matriz Kr.
matrix<double> matrizKr(matrix<double> M, matrix<double> K){
    // Definimos el tamaño de Kr a partir del tamaño de M.
    int Krcols = 0, Krrows = 0;
    Krrows = M.rowno();
    Krcols = M.rowno();

    // Definimos la matriz Kr.
    matrix<double> Kr(Krrows, Krcols); Kr.null();
    Kr = !M * K;

    return Kr;
}

int main(){
    // Abrimos los ficheros de dónde leemos los datos de las matrices.
    // Los datos los hemos guardado a mano tras realizar los cálculos.
    string ainfile = "matrizM.txt";
    string finfile = "matrizK.txt";
    ifstream ffile(ainfile);
    ifstream ff(finfile);
    if (ffile.is_open()){
        if(ff.is_open()){

            // Filas y columnas de las matrices.
            int mrows = 0, mcols = 0, krows = 0, kcols = 0;

            // Definimos la matriz M.
            ffile >> mrows >> mcols;
            matrix<double> M(mrows, mcols);
            ffile >> M;
            
            // Definimos la matriz K.
            ff >> krows >> kcols;
            matrix<double> K(krows, kcols);
            ff >> K;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            // Definimos la que será nuestra matriz A (A = Kr en nuestro caso).
            //para hacer el método de diagonalización de una matriz simétrica de Jacobi.
            matrix<double> A(mrows, mcols); 
            A = matrizKr(M, K);
            
            // Guardamos la matriz A = Kr en un fichero.
            string infile = "matrizA.txt";
            ofstream ff(infile);
            if (ff.is_open()){
                int arows = 0, acols = 0;
                arows = A.rowno(); acols = A.colno();
                ff << arows << " " << acols << endl;
                for (int i=0; i<arows; i++){
                    for (int j=0; j<acols; j++){
                        if (j!=acols-1){
                            ff << A(i,j) << " ";
                        } else {
                            ff << A(i,j) << endl;
                        }
                    }
                }
            }

        }
    }
}