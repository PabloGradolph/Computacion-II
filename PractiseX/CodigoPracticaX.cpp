#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función para calcular la NormaMáxima que utilizaremos en el método Newton-Raphson.
double NormaMaximaMatriz(matrix<double> A){
    int arows = 0, acols = 0;
    arows = A.rowno();
    acols = A.colno();

    double sumatorio = 0.0, fila_anterior = 0.0, maximo = 0.0;
    for (int i=0; i<arows; i++){
        fila_anterior = sumatorio;
        sumatorio = 0.0;
        for (int j=0; j<acols; j++){
            sumatorio = sumatorio + fabs(A(i,j));
        }
        if (sumatorio>fila_anterior){
            maximo = sumatorio;
        }
    }

    return maximo;
}

// Función que calcula la matriz f(x) con las 3 funciones del sistema.
matrix<double> MatrizFunciones(matrix<double> xx){
    // Definimos las variables x, y, z que vienen de la matriz xx.
    double x = xx(0,0), y = xx(1,0), z = xx(2,0);

    // Creamos la matriz f con 3 filas y 1 columna.
    // Y le damos los valores de las 3 funciones.
    matrix<double> f(3,1); f.null();
    f(0,0) = 6*x - 2*cos(y*z) - 1;
    f(1,0) = 9*y + sqrt(pow(x,2)+sin(z)+1.06) +0.9;
    f(2,0) = 60*z + 3*exp(-x*y) + 10*M_PI - 3;

    // Retornamos la función f calculada.
    return f;
}

// Función que calcula la matriz Jacobiana f'(x).
matrix<double> Jacobiana(matrix<double> xx){
    // Definimos las variables x, y, z que vienen de la matriz xx.
    double x = xx(0,0), y = xx(1,0), z = xx(2,0);

    // Creamos la matriz Jacobiana con 3 filas y 3 columnas.
    // Le damos los valores con las derivadas parciales correspondientes.
    matrix<double> Jac(3,3); Jac.null();
    Jac(0,0) = 6; Jac(0,1) = 2*z*sin(y*z); Jac(0,2) = 2*y*sin(y*z);
    Jac(1,0) = 2*x / (2*sqrt(pow(x,2) + sin(z) + 1.06)); Jac(1,1) = 9; Jac(1,2) = cos(z) / (2*sqrt(pow(x,2) + sin(z) + 1.06));
    Jac(2,0) = -3*y*exp(-x*y); Jac(2,1) = -3*x*exp(-x*y); Jac(2,2) = 60;

    // Retornamos la matriz Jacobiana.
    return Jac;
}

// Función del método Newton-Raphson.
matrix<double> NewtonRaphson(matrix<double> xx, matrix<double> Jac, double eps){
    // Comprobamos que la matriz Jacobiana calculada no es singular.
    if (abs(Jac.det())<=eps){
        cout<<"La matriz Jacobiana es singular. No podemos calcular su inversa.";
    } else {
        matrix<double> new_xx(3,1); new_xx.null();
        double norma = 0.0;
        norma = NormaMaximaMatriz(new_xx - xx);
        while (norma > eps){
            new_xx = xx - (!(Jacobiana(xx)) * MatrizFunciones(xx));
            norma = NormaMaximaMatriz(new_xx - xx);
            xx = new_xx;
        }
        return new_xx;
    }
}

int main(){
    // Definimos la matriz xx (x, y , z) con los valores iniciales (1, 1, 1).
    matrix<double> xx(3,1); xx.null();
    xx(0,0) = 1; xx(1,0) = 1; xx(2,0) = 1;

    // Calculamos la matriz Jacobiana.
    matrix<double> Jac(3,3); Jac.null();
    Jac = Jacobiana(xx);

    // Llamamos a la función del método.
    matrix<double> Sol(3,1); Sol.null();
    Sol = NewtonRaphson(xx, Jac, 0.00000001);
    cout<<"La matriz solución es:"<<endl;
    cout<<Sol;
    cout<<endl;

    // Comprobación MatrizFunciones(Sol) = 0.
    matrix <double> f(3,1); f.null();
    f = MatrizFunciones(Sol);
    cout<<"Comprobamos la solución con f(Sol) = 0"<<endl;
    cout<<f;
    cout<<endl;

    // Calculamos el error cometido para el cálculo de cada una de las variables solución.
    matrix <double> error(3,1); error.null();
    error = error - f;
    cout<<"El error cometido para cada variable (x, y, z) es:"<<endl;
    cout<<error;

    return 0;
}