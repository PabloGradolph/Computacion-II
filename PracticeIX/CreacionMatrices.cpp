#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Creación de la matriz de coeficientes A y F del método LU para matrices tridiagonales. 
// En este caso la diagonal a = 4 y las diagonales b y c = -1.
// En este caso la matriz F, si i=1 o i=n, Fi = 100, sino Fi = 200.
void Matrices(int n){
    // Definimos ambas matrices.
    matrix<double> A(n, n); A.null();
    matrix<double> F(n, 1); F.null();

    // Le damos los valores a la matriz A.
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j){
                A(i,j) = 4;
            } else if (i - j == 1 || i - j == -1){
                A(i,j) = -1;
            }
        }
    }

    // Le damos los valores a la matriz F.
    for (int i=0; i<n; i++){
        if (i==0 || i==n-1){
            F(i,0) = 100;
        } else {
            F(i,0) = 200;
        }
    }

    string file1 = "matrizA.txt";
    string file2 = "matrizF.txt";
    ofstream ff(file1);
    if (ff.is_open()){
        ff << A;
    }

    ofstream fff(file2);
    if (fff.is_open()){
        fff << F;
    }
        
}

int main(){
    int n = 0;
    cout<<"Introduce el número de filas de las matrices: "; cin >> n;

    Matrices(n);
    
}