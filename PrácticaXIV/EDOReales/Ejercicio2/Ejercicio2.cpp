// Resolución de ecuaciones diferenciales.
// Por el método de Ronge-Kutta.
// La solución obtenida son tablas de valores numéricos.

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
double FuncionYPrima(double x, double y){
    double YPrima = 0.0;
    YPrima = -2*x -  y;
    return YPrima;
}

// Función que devuelve el valor de la función exacta.
double SolExacta(double x){
    double Sol = 0.0;
    Sol = -3*exp(-x) - 2*x + 2;
    return Sol;
}

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
        // QUITA EL +1 DEL BUCLE (NO DEBERÍA ESTAR PERO NO ITERA LA ÚLTIMA VEZ SINO)
        for (int i=1; i<=npasos+1; i++){
            // Ecuaciones del método de Euler.
            x = xmin + i*h;
            y = y + h*FuncionYPrima(x, y);
            ff << /*x <<*/ " " << y << endl; 
        }
    }
    
    return npasos;
}

// Función para la resolución por el sistema Ronge-Kutta (segundo orden)
// En función del valor del parámetro a2 se llama método de Heun, del punto medio o de Ralston.
void RK2(double a2, double h, double xmin, double xmax, double y0){
    // Definimos el número de pasos y las k.
    double npasos = 0.0, k1 = 0.0, k2 = 0.0;
    npasos = (xmax - xmin)/h;
    k1 = FuncionYPrima(xmin, y0);

    // Para k2 necesitamos.
    double p = 0.0, q = 0.0, a1 = 0.0;
    a1 = 1 - a2; p = 1/(2*a2); q = 1/(2*a2);
    k2 = FuncionYPrima(xmin + p*h, y0 + q*k1*h);

    // Función y y valor x.
    double y = y0, x = xmin;

    // Guardamos los resultados en un fichero.
    string filend = a2fname(a2, xmin, xmax, h);
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "X\tY" << endl;
        ff << xmin << " " << y << endl;
        for (int i=1; i<=npasos+1; i++){
            x = xmin + i*h;
            y = y + h*(a1*k1 + a2*k2);
            k1 = FuncionYPrima(x, y);
            k2 = FuncionYPrima(x + p*h, y + q*k1*h);
            ff << /*x <<*/ " " << y << endl; 
        }
    }
}

// Función para la resolución por el sistema Ronge-Kutta (cuarto orden).
void RK4(double h, double xmin, double xmax, double y0){
    // Definimos el número de pasos y las k.
    double npasos = 0.0, k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;
    npasos = (xmax - xmin)/h;

    // Calculamos las k de la primera iteración.
    k1 = FuncionYPrima(xmin, y0);
    k2 = FuncionYPrima(xmin + 0.5*h, y0 + 0.5*k1*h);
    k3 = FuncionYPrima(xmin + 0.5*h, y0 + 0.5*k2*h);
    k4 = FuncionYPrima(xmin + h, y0 + k3*h);

    // Valores x e y.
    double y = y0, x = xmin;

    // Guardamos los resultados en un fichero con un bucle para el resto de iteraciones.
    string filend = "Ronge-Kutta4orden.txt";
    ofstream ff(filend);
    if (ff.is_open()){
        ff << "#DATOS PARA h=" << h << endl;
        ff << "X\tY" << endl;
        ff << x << " " << y << endl;
        for (int i=1; i<=npasos+1; i++){
            x = xmin + i*h;
            y = y + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
            k1 = FuncionYPrima(x, y);
            k2 = FuncionYPrima(x + 0.5*h, y + 0.5*k1*h);
            k3 = FuncionYPrima(x + 0.5*h, y + 0.5*k2*h);
            k4 = FuncionYPrima(x + h, y + k3*h);
            ff << /*x <<*/ " " << y << endl; 
        }
    }
}

int main(){
    // Definimos las variables iniciales del problema.
    double a2 = 1.0, h = 0.1, xmin = 0.0, xmax = 0.6, y0 = -1.0; 

    // Llamamos a la función para Ronge-Kutta de segundo orden.
    RK2(a2, h, xmin, xmax, y0);

    // Llamamos a la función para Ronge-Kutta de cuarto orden.
    RK4(h, xmin, xmax, y0);

    // Llamamos a la función de Euler.
    Euler(h, xmin, xmax, y0);

    // Comparamos con la solución exacta. Valores muy parecidos (mirar ficheros).
    double Sol = 0.0;
    Sol = SolExacta(xmin); cout<<Sol<<endl;
    Sol = SolExacta(xmax); cout<<Sol<<endl;

    // La comparación gráfica se puede ver en la foto.

    return 0;
}