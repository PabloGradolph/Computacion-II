// Resolución de sistemas de ecuaciones diferenciales
// Por el método de Ronge-Kutta.

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

// Función que devuelve el valor de dy/dx para un cierto valor de x y de y.
matrix<double> SistemaYPrima(double x, matrix<double> Y){
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();
    YPrima(0,0) = -0.5*Y(0,0);
    YPrima(1,0) = 4 - (0.3*Y(1,0)) - (0.1*Y(0,0));
    return YPrima;
}

// Resolución de sistemas de ecuaciones diferenciales por el método de Ronge-Kutta(segundo orden).
matrix<double> RK2Sistemas(int n, double a2, double h, double xmin, double xmax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, x = xmin;
    npasos = (xmax - xmin)/h;

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
        ff << "X\tY1\tY2" << endl;
        ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + (((a1*k1) + (a2*k2))*h);
            x = x + h;
            k1 = SistemaYPrima(x, Y);
            k2 = SistemaYPrima(x+p*h, Y+q*h*k1);
            ff << x << "\t" << Y(0,0) << "\t" << Y(1,0) << endl; 
        }
    }

    return Y;
}

int main(){
    // Definimos h y el tamaño de la matriz.
    double h = 0.5, a2 = 0.0;
    int n = 2;
    double xmin = 0.0, xmax = 2.0;

    // Definimos la matriz inicial
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 4;
    y0(1,0) = 6;

    
    y0 = RK2Sistemas(a2, n, h, xmin, xmax, y0);
    
    cout<<"Matriz solución al final del proceso RK2 con a2 = 1: "<<endl;
    cout<<y0;

    return 0;
}