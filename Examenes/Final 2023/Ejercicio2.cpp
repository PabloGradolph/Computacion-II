// Ejercicio 2 del examen final de prácticas.
// Autor: Pablo Gradolph Oliva.
// Fecha: 16/01/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función para la creación de nombres de ficheros de forma automática.
string a2fname(double a2, double xmin, double xmax, double h){
  ostringstream oss;
  oss << setprecision(1) << a2;
  string fend = "_a"+oss.str(); 

  oss << setprecision(1) << xmin;
  fend = fend+"_xmin"+oss.str(); 

  oss.str(string());
  oss << setprecision(1) << xmax;
  fend = fend+"_xmax"+oss.str();

  oss.str(string());
  oss << setprecision(1) << h;
  fend = fend+"_h"+oss.str()+".txt";

  return fend;
}

// Funcion que devuelve la solución exacta
double SolExacta(double x){
    double sol = 0.0;
    sol = 3*exp(-2*x) - 2*exp(-3*x);
    return sol;
}

// Función que devuelve el valor de dy/dx para un cierto valor de x y de y.
matrix<double> SistemaYPrima(double x, matrix<double> Y){
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();
    YPrima(0,0) = Y(1,0);
    YPrima(1,0) = (-5*Y(1,0)) - (6*Y(0,0));
    return YPrima;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Ronge-Kutta(segundo orden).
matrix<double> RK2Sistemas(int n, double a2, double npasos, double xmin, double xmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double h = 0.0, x = xmin;
    h = (xmax - xmin)/npasos;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    k1 = SistemaYPrima(x, Y);
    
    // Para k2 necesitamos.
    double p = 0.0, q = 0.0, a1 = 0.0, y1 = 0.0, y2 = 0.0;
    a1 = 1 - a2; p = 1/(2*a2); q = 1/(2*a2);
    matrix<double> k2(n,1); k2.null();
    k2 = SistemaYPrima((p*h) + x, Y + (q*h)*k1);

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string filend = a2fname(a2, xmin, xmax, h);
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "Tiempo\tX\t\tX'\t\tSolExacta" << endl;
        ff << x << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << SolExacta(x) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + (((a1*k1) + (a2*k2))*h);
            x = x + h;
            k1 = SistemaYPrima(x, Y);
            k2 = SistemaYPrima(x+p*h, Y+q*h*k1);
            ff << x << "\t\t" << Y(0,0) << "\t\t" << Y(1,0) << "\t\t" << SolExacta(x) << endl; 
        }
    }

    return Y;
}

int main(){
    // Definimos las variables que utilizaremos en la función.
    double h = 0.5, a2 = 0.5;
    int n = 2, npasos = 20;
    double xmin = 0.0, xmax = 5.0;

    // Definimos la matriz inicial
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 1.0;
    y0(1,0) = 0.0;

    // Definimos la matriz solución
    matrix<double> Y(n, 1); Y.null();

    // Llamamos a la función que resuelve por el método RK2
    Y = RK2Sistemas(a2, n, npasos, xmin, xmax, y0);
    
    cout<<"Matriz solución al final del proceso RK2 con a2 = 0.5 y n = 20: "<<endl;
    cout<<Y<<endl<<endl;

    // Llamamos a la función que resuelve por el método RK2
    npasos = 40;
    Y = RK2Sistemas(a2, n, npasos, xmin, xmax, y0);
    cout<<"Matriz solución al final del proceso RK2 con a2 = 0.5 y n = 40: "<<endl;
    cout<<Y<<endl;

    return 0;
}