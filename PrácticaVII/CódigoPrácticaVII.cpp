#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;


matrix<double> MetodoLU(matrix<double> A, matrix<double> B){
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                L(i,j) = 1;
            }else if (i>j){
                U(i,j) = 0;
            }else{
                L(i,j) = 0;
            }
        }
    
    }
}

int main(){
    string ainfile = "matrizA.txt";
    string binfile = "matrizB.txt";
    ifstream ffile(ainfile);
    ifstream ff(binfile);
    if (ffile.is_open()){
        if (ff.is_open()){
            // Filas y columnas de ambas matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;
            
            // Definimos la matriz A.
            ffile >> arows >> acols;
            matrix<double> A(arows, acols);
            ffile >> A;
            
            // Definimos la matriz B.
            ff >> brows >> bcols;
            matrix<double> B(brows, bcols);
            ff >> B;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            cout<<A;
            cout<<B;

            // Definimos la que será la matriz solución por el método LU
            matrix<double> X; X.null();
            X = MetodoLU(A, B);

        }else {
            cout<<"No se ha podido abrir el fichero "<<binfile<<endl;
        }

    }else{
        cout<<"No se ha podido abrir el fichero "<<ainfile<<endl;
    }

    return 0;

}