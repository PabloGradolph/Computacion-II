// Código Práctica XVI 
// Resolución de ecuaciones diferenciales de segundo orden con condiciones de contorno
// Autor: Pablo Gradolph Oliva
// Fecha: 05/12/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

double uReal(double r){
    double u1 = 110.0, R1 = 5.0, R2 = 10.0;
    double u = 0.0;
    u = ((u1*R1)/r) * ((R2-r)/(R2-R1));
    return u;
}

matrix<double> SistemaYPrima(double r, matrix<double> Y){
    // Creamos la matriz YPrima a partir del tamaño de la matriz pasada como argumento
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();

    // Definimos los valores de la matriz YPrima
    YPrima(0,0) = Y(1,0);
    YPrima(1,0) = (-2/r)*Y(1,0); 
    return YPrima;
}

matrix<double> RK4Sistemas(int n, double h, double rmin, double rmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, r = rmin;
    npasos = (rmax - rmin)/h;
    double error = 0.0;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    matrix<double> k2(n,1); k2.null();
    matrix<double> k3(n,1); k3.null();
    matrix<double> k4(n,1); k4.null();
    k1 = SistemaYPrima(r, Y);
    k2 = SistemaYPrima(r + 0.5*h, Y + 0.5*h*k1);
    k3 = SistemaYPrima(r + 0.5*h, Y + 0.5*h*k2);
    k4 = SistemaYPrima(r + h, Y + h*k3);
    error = fabs(Y(0,0) - uReal(r));

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string file = "Pt16_RK4_1.txt";
    ofstream ff(file);
    if (ff.is_open()){
        ff << setprecision(5);
        ff << "#DATOS PARA h=" << h << endl;
        ff << "r\t\tu\t\terror" << endl;
        ff << r << "    " << Y(0,0) << "    " << error << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + 1/6. * h*(k1 + 2.*k2 + 2.*k3 + k4);
            r = r + h;
            error = (Y(0,0) - uReal(r));
            k1 = SistemaYPrima(r, Y);
            k2 = SistemaYPrima(r + 0.5*h, Y + 0.5*h*k1);
            k3 = SistemaYPrima(r + 0.5*h, Y + 0.5*h*k2);
            k4 = SistemaYPrima(r + h, Y + h*k3);
            ff << r << "    " << Y(0,0) << "    " << error << endl; 
        }
    }
    
    return Y;
}

int main(){
    // Definimos las variables que utilizaremos en la función.
    double h = 0.05;
    int n = 2;
    double rmin = 5.0, rmax = 10.0;
    double tol = 10e-8;

    // Definimos la matriz inicial
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 110.0;
    y0(1,0) = 22.0;
    double dua1 = y0(1,0);

    // Definimos la matriz solución
    matrix<double> Y(n, 1); Y.null();

    // Llamamos a la función que resuelve por el método RK4
    Y = RK4Sistemas(n, h, rmin, rmax, y0);
    double ub1 = Y(0,0);
    
    // Obtenemos un u1(b) = 165 > 0 = ub
    // Entonces suponemos un u'1(a) más pequeño (multiplicamos por 0.5)
    y0(0,0) = 110.0;
    y0(1,0) = 11.0;
    double dua2 = y0(1,0);

    // Llamamos a la función que resuelve por el método RK4
    Y = RK4Sistemas(n, h, rmin, rmax, y0);
    double ub2 = Y(0,0);

    // Ahora hacemos el proceso de interpolación hasta que el resultado esté por debajo de 
    // la tolerancia
    do{
        y0(0,0) = 110.0;
        y0(1,0) = dua2 - ((ub2 - uReal(10.0)) * (dua2-dua1) / (ub2-ub1));

        Y = RK4Sistemas(n, h, rmin, rmax, y0);
        ub1 = ub2; ub2 = Y(0,0);
        dua1 = dua2; dua2 = y0(1,0);
        
    }while(fabs(ub2 - uReal(10.0)) > tol);

    return 0;
}