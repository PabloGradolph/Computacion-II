// Velocidad límite cuando a = 0 --> Sacamos Gamma.
// t0 = 0
// while (fabs(v-vlim)>eps){}
// x en Ejercicio1 --> Ahora es t
// y en Ejercicio1 --> Ahora es v

// Gamma = 49/16245

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Definimos gamma global
double g = 9.8, vlim = 57.0;
double gamma = g/(vlim*vlim);

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
double FuncionYPrima(double t, double v){
    double YPrima = 0.0;
    YPrima = g - gamma*v*v;
    return YPrima;
}

// Función para la resolución de una ecuación diferencial por el método de Euler.
double Euler(double h, double xmin, double xmax, double y0){
    // Definimos el número de pasos e inicializamos x e y.
    double npasos = 0.0, x = 0.0, y = y0;
    npasos = (xmax - xmin)/h;

    // Generamos un fichero donde guardar el resultado con la función anterior.
    string filend = fname(xmin,xmax,h);
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "X\tY" << endl;
        ff << xmin << " " << y0 << endl;
        for (int i=1; i<=npasos; i++){
            // Ecuaciones del método de Euler.
            x = xmin + i*h;
            y = y + h*FuncionYPrima(x, y);
            ff << x << " " << y << endl; 
        }
    }
    
    return npasos;
}

int main(){
    
    // Definimos los datos para nuestro problema en particular.
    int hlen = 3;
    double h[hlen] = {0.5, 0.1, 0.05};
    double tmin = 0.0, tmax = 30.0, y0 = 0.0;

    // Llamamos a la función 3 veces, una por cada h.
    for (int i=0; i<hlen; i++){
        Euler(h[i], tmin, tmax, y0);
    }

    return 0;
}