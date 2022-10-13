#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

bool ResultadoCorrecto(matrix<double> A, matrix<double> B, matrix<double> X, double tol){
    // Definimos el tamaño de las matrices pasadas como argumentos.
    int brows = 0, bcols = 0;
    brows = B.rowno();
    bcols = B.colno();

    matrix<double> x;
    x = A*X - B;

    bool correcto = true;

    for (int i=0; i<brows; i++){
        if (fabs(x(i,0)) < tol){
            continue;
        } else {
            correcto = false;
            break;
        }
    }

    return correcto;
}

