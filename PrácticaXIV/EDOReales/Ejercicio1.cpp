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
double FuncionYPrima(double x, double y){
    double YPrima = 0.0;
    YPrima = 2*cos(x) -  y*(1/tan(x));
    return YPrima;
}

// Función que devuelve el valor exacto de dy/dx para un cierto valor de x.
double SolExacta(double x){
    double Sol = 0.0;
    Sol = sin(x) - (sin(1/2)*sin(1/2))/sin(x);
    return Sol;
}

double Euler(double h, double xmin, double xmax, double y0){
    double npasos = 0.0, new_x = 0.0, x = 0.0, y = y0;
    npasos = (xmax - xmin)/h;

    string filend = fname(xmin,xmax,h);
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "X\tY" << endl;
        ff << xmin << " " << y0 << endl;
        for (int i=1; i<=npasos; i++){
            x = xmin + i*h;
            y = y + h*FuncionYPrima(x, y);
            ff << x << " " << y << endl; 
        }
    }
    
    return npasos;
}

int main(){
    int hlen = 3;
    double h[hlen] = {0.5, 0.1, 0.02}, Sol = 0.0;
    double xmin = 0.5, xmax = 1.0, y0 = 0.0;

    for (int i=0; i<hlen; i++){
        Euler(h[i], xmin, xmax, y0);
    }

    Sol = SolExacta(1.0);
    cout<<Sol;
    
    return 0;
}