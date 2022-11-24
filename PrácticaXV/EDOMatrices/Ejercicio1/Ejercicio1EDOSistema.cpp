// Resolución de sistemas de ecuaciones diferenciales
// Por el método de Euler.

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función para generar nombres de ficheros.
string fname(double xmin, double xmax, double h){
  ostringstream oss; 
  oss << setprecision(1) << xmin;
  string fend = "_xmin"+oss.str(); 

  oss.str(string());
  oss << setprecision(1) << xmax;
  fend = fend+"_xmax"+oss.str();

  oss.str(string());
  oss << setprecision(1) << h;
  fend = fend+"_h"+oss.str()+".txt";

  return fend;
}

// Función que devuelve el valor de dy/dx para un cierto valor de x y de y.
matrix<double> SistemaYPrima(double x, matrix<double> Y){
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();
    YPrima(0,0) = -0.5*Y(0,0);
    YPrima(1,0) = 4 - (0.3*Y(1,0)) - (0.1*Y(0,0));
    return YPrima;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Euler.
matrix<double> EulerSistemas(int n, double h, double xmin, double xmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, x = xmin;
    npasos = (xmax - xmin)/h;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Guardamos los resultados de las siguientes iteraciones en un fichero.
    string filend = fname(xmin,xmax,h);
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "X\tY1\tY2" << endl;
        ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + h*SistemaYPrima(x, Y);
            x = x + h;
            ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl; 
        }
    }
    
    return Y;
}

int main(){
    // Definimos h y el tamaño de la matriz.
    double h = 0.5;
    int n = 2;
    double xmin = 0.0, xmax = 2.0;

    // Definimos la matriz inicial
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 4;
    y0(1,0) = 6;

    y0 = EulerSistemas(n, h, xmin, xmax, y0);
    
    cout<<"Matriz solución al final del proceso: "<<endl;
    cout<<y0;

    return 0;
}