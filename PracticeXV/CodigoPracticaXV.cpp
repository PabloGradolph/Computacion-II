// Código Práctica XV: 
// Resolución de ecuaciones diferenciales de orden n con condiciones iniciales
// Autor: Pablo Gradolph Oliva
// Fecha: 04/12/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

matrix<double> SistemaYPrima(double x, matrix<double> Y){
    // Creamos la matriz YPrima a partir del tamaño de la matriz pasada como argumento
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();

    // Valores de las constantes que van dentro de la matriz YPrima
    double m1 = 2.0, m2 = 3.5, k1 = 2.5, k2 = 3.5;

    // Definimos los valores de la matriz YPrima
    YPrima(0,0) = Y(2,0);
    YPrima(1,0) = Y(3,0);
    YPrima(2,0) = (-k1/m1)*Y(0,0) - (k2/m1)*(Y(0,0)-Y(1,0));
    YPrima(3,0) = (k2/m2)*(Y(0,0)-Y(1,0)); 
    return YPrima;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Ronge-Kutta(cuarto orden).
matrix<double> RK4Sistemas(int n, double h, double tmin, double tmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, t = tmin;
    npasos = (tmax - tmin)/h;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    matrix<double> k2(n,1); k2.null();
    matrix<double> k3(n,1); k3.null();
    matrix<double> k4(n,1); k4.null();
    k1 = SistemaYPrima(t, Y);
    k2 = SistemaYPrima(t + 0.5*h, Y + 0.5*h*k1);
    k3 = SistemaYPrima(t + 0.5*h, Y + 0.5*h*k2);
    k4 = SistemaYPrima(t + h, Y + h*k3);

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string file = "Pt15_RK4.txt";
    ofstream ff(file);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "t\t\tY1\t\tY2\t\tV1\t\tV2" << endl;
        ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + 1/6. * h*(k1 + 2.*k2 + 2.*k3 + k4);
            t = t + h;
            k1 = SistemaYPrima(t, Y);
            k2 = SistemaYPrima(t + 0.5*h, Y + 0.5*h*k1);
            k3 = SistemaYPrima(t + 0.5*h, Y + 0.5*h*k2);
            k4 = SistemaYPrima(t + h, Y + h*k3);
            ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl; 
        }
    }
    
    return Y;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Euler.
matrix<double> EulerSistemas(int n, double h, double tmin, double tmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, t = tmin;
    npasos = (tmax - tmin)/h;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Guardamos los resultados de las siguientes iteraciones en un fichero.
    string filend = "Pt15_Euler.txt";
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "t\t\tY1\t\tY2\t\tV1\t\tV2" << endl;
        ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + h*SistemaYPrima(t, Y);
            t = t + h;
            ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl; 
        }
    }
    
    return Y;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Ronge-Kutta(segundo orden).
matrix<double> RK2Sistemas(int n, double a2, double h, double tmin, double tmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, t = tmin;
    npasos = (tmax - tmin)/h;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    k1 = SistemaYPrima(t, Y);
    
    // Para k2 necesitamos.
    double p = 0.0, q = 0.0, a1 = 0.0, y1 = 0.0, y2 = 0.0;
    a1 = 1 - a2; p = 1/(2*a2); q = 1/(2*a2);
    matrix<double> k2(n,1); k2.null();
    k2 = SistemaYPrima((p*h) + t, Y + (q*h)*k1);

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string filend = "Pt15_RK2.txt";
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "t\t\tY1\t\tY2\t\tV1\t\tV2" << endl;
        ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + (((a1*k1) + (a2*k2))*h);
            t = t + h;
            k1 = SistemaYPrima(t, Y);
            k2 = SistemaYPrima(t+p*h, Y+q*h*k1);
            ff << t << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << Y(2,0) << "\t\t" << Y(3,0) << endl; 
        }
    }

    return Y;
}

int main(){
    // Definimos las variables que utilizaremos en la función.
    double h = 0.1, a2 = 1.0;
    int n = 4;
    double tmin = 0.0, tmax = 100.0;

    // Definimos la matriz inicial
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 3.0;
    y0(1,0) = 4.0;
    y0(2,0) = 0.0;
    y0(3,0) = 0.0;

    // Definimos la matriz solución
    matrix<double> Y(n, 1); Y.null();

    // Llamamos a la función que resuelve por el método RK4
    Y = RK4Sistemas(n, h, tmin, tmax, y0);
    cout<<"Matriz solución al final del proceso RK4: "<<endl;
    cout<<Y;

    // Llamamos a la función que resuelve por el método de Euler
    Y = RK2Sistemas(n, a2, h, tmin, tmax, y0);
    cout<<"Matriz solución al final del proceso RK2: "<<endl;
    cout<<Y;

    // Llamamos a la función que resuelve por el método de Euler
    Y = EulerSistemas(n, h, tmin, tmax, y0);
    cout<<"Matriz solución al final del proceso Euler: "<<endl;
    cout<<Y;

    return 0;
}