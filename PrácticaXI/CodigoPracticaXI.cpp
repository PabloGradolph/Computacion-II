#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función que calcula el máximo valor de los elementos por encima de la diagonal de una matriz.
double MaxEncimaDiagonal(matrix<double> A){
    // Guardamos el tamaño de la matriz A para trabajar con ella.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.rowno();

    // Calculamos el máximo
    double maximo = 0.0;
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (j>i){
                if (fabs(A(i,j)) > fabs(maximo)){
                    maximo = A(i,j);
                }
            }
        }
    }
    return maximo;
}

void JacobiDiagonal(matrix<double> A, matrix<double>& Diagonalizada, matrix<double>& U, int &iteraciones, double tol){
    // Tamaño de A.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.rowno();

    // Definimos el máximo y creamos el bucle para que se ejecute el método hasta que
    // el máximo de la matriz esté por debajo de la tolerancia.
    double maximo = MaxEncimaDiagonal(A);
    
    while (fabs(maximo)>tol){

        // Vemos la posición en la que se encuentra ese máximo.
        int ii=NULL, jj=NULL;
        if (maximo == A(0,1)){
            ii = 0; jj = 1;
        } else {
            for (int i=0; i<arows; i++){
                if (ii!=NULL && jj!=NULL){
                    break;
                }
                for (int j=0; j<acols; j++){
                    if (j>i){
                        if (A(i,j)==maximo){
                            ii = i; jj = j;
                            break;
                        }
                    } 
                }
            }
        }
            
        // Ya tenemos que la posición del máximo está en ii, jj.
        // Calculamos ahora theta.
        double theta = 0.0;
        if (A(ii,ii)!=A(jj,jj)){
            theta = 0.5 * atan(2*A(ii,jj)/(A(ii,ii)-A(jj,jj)));
        } else {
            theta = M_PI/4.0;
        }

        // Calculamos ahora la matriz R.
        matrix<double> R(arows, acols); R.null();
        for (int i=0; i<arows; i++){
            for (int j=0; j<acols; j++){
                if (i==j){
                    R(i,j) = 1;
                } else {
                    R(i,j) = 0;
                }
            }
        }
        R(ii,ii) = cos(theta); R(jj,jj) = cos(theta);
        R(ii,jj) = -sin(theta); R(jj,ii) = sin(theta);

        // Nueva matriz A.
    }
    
}
    

int main(){
    // Leemos la matriz A creada a partir del código 'CalculoMatrizA.cpp'
    string ainfile = "matrizA.txt";
    ifstream ff(ainfile);
    if (ff.is_open()){
        int arows = 0, acols = 0;
        
        // Definimos la matriz A.
        ff >> arows >> acols;
        matrix<double> A(arows, acols);
        ff >> A;
        
        // Definimos las matrices y variables que queremos que la función de Jacobi nos devuelva.
        // Habrá que pasarle todo esto como argumento a la función para que lo transforme.
        matrix<double> Diagonalizada(arows, acols); Diagonalizada.null();
        matrix<double> U(arows, acols); U.null();
        int iteraciones = 0;
        double tol = 0.00001;

        // Llamamos ahora a la función del método de Jacobi para diagonalizar matrices simétricas.
        JacobiDiagonal(A, Diagonalizada, U, iteraciones, tol);

    }
}