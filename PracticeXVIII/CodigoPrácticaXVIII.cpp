// Código Práctica XVIII
// Resolución de ecuaciones diferenciales ordinarias.
// Autor: Pablo Gradolph Oliva
// Fecha: 13/12/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Genera ficheros de forma automática en base a dos parámetros.
string fname(double a, double b){
    ostringstream oss; 
    oss << setprecision(3) << a;
    string fend = "_t"+oss.str(); 

    oss.str(string());
    oss << setprecision(3) << b;
    fend = fend+"_"+oss.str()+".txt";
    return fend;

    // Nombre del fichero de salida
    // string outf = "rk4"+filend;
    // ofstream ff(outf);
}

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
        if (fabs(sumatorio)>fila_anterior){
            maximo = sumatorio;
        }
    }

    return maximo;
}

matrix<double> SistemaYPrima(double x, matrix<double> Y){
    // Creamos la matriz YPrima a partir del tamaño de la matriz pasada como argumento
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();

    // Definimos las variables que usaremos en el sistema de ecuaciones.
    double w, k, phi;
    w = 7.29e-5; k = 9.8/20.; phi = M_PI/4.;

    // Definimos los valores de la matriz YPrima
    YPrima(0,0) = Y(2,0);
    YPrima(1,0) = Y(3,0);
    YPrima(2,0) = 2.*(w)*sin(phi)*Y(3,0) - (k*k)*Y(0,0);
    YPrima(3,0) = -2.*(w)*sin(phi)*Y(2,0) - (k*k)*Y(1,0);
    return YPrima;
}

matrix<double> RK4Sistemas(int n, double h, double xmin, double xmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, x = xmin;
    npasos = (xmax - xmin)/h;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    matrix<double> k2(n,1); k2.null();
    matrix<double> k3(n,1); k3.null();
    matrix<double> k4(n,1); k4.null();
    k1 = SistemaYPrima(x, Y);
    k2 = SistemaYPrima(x + 0.5*h, Y + 0.5*h*k1);
    k3 = SistemaYPrima(x + 0.5*h, Y + 0.5*h*k2);
    k4 = SistemaYPrima(x + h, Y + h*k3);

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string file = "Pt18_RK4.txt";
    ofstream ff(file);
    if (ff.is_open()){
        ff << setprecision(5);
        ff << "#DATOS PARA h=" << h << endl;
        ff << "t\t\tx\t\ty\t\tx'\t\ty'" << endl;
        ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << "\t" << Y(2,0) << "\t" << Y(3,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + 1/6. * (k1 + 2.*k2 + 2.*k3 + k4) * h;
            x = x + h;
            k1 = SistemaYPrima(x, Y);
            k2 = SistemaYPrima(x + 0.5*h, Y + 0.5*h*k1);
            k3 = SistemaYPrima(x + 0.5*h, Y + 0.5*h*k2);
            k4 = SistemaYPrima(x + h, Y + h*k3);
            ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << "\t" << Y(2,0) << "\t" << Y(3,0) << endl; 
        }
    }
    
    return Y;
}

int main(){

    // Definimos las variables necesarias.
    double tol = 10e-6;
    double h = 1., xmin = 0.0, xmax = 300.0;
    int n = 4;
    
    // Definimos la matriz de condiciones iniciales
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 5.0;
    y0(1,0) = 0.0;
    y0(2,0) = 0.0;
    y0(3,0) = 0.0;

    // Definimos las que serán las matrices de soluciones a comparar.
    matrix<double> sol1(n,1); sol1.null();
    matrix<double> sol2(n,1); sol2.null();

    // Calculamos sol1
    sol1 = RK4Sistemas(n, h, xmin, xmax, y0);
    double diference = 0.0;

    // Creamos el bucle para que se repita el proceso hasta una cierta tolerancia.
    do{
        h = h*0.5;
        sol2 = RK4Sistemas(n, h, xmin, xmax, y0);
        diference = NormaMaximaMatriz(sol2-sol1);
        sol1 = sol2;
    }while(diference>tol);

    // Retornamos la matriz solución final con el h utilizado y la tolerancia.
    cout<<"El paso de tiempo h para el que la precisión de la solución es mejor que una tolerancia = "<<tol<<" es:"<<endl;
    cout<<"h = "<<h<<endl;
    cout<<"La solución para cada tiempo la encuentras en el fichero: 'Pt18_RK4.txt'."<<endl;

    return 0;
}