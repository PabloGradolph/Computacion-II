#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

// Función que calcula la derivada NUMÉRICA por el método de las diferencias centrales.
double DiferenciasCentrales(double h, double siguiente, double anterior){
    // Calculamos la derivada numérica.
    double der_num = NULL;
    der_num = (siguiente - anterior)/(2*h);

    return der_num;
}

// Función que calcula la derivada NUMÉRICA por el método de diferencia hacia adelante.
double DiferenciaAlante(double h, double siguiente, double numero){
    // Calculamos la derivada numérica.
    double der_num = NULL;
    der_num = (siguiente - numero)/h;

    return der_num;
}

// Función que calcula la derivada NUMÉRICA por el método de diferencia hacia detrás.
double DiferenciaAtras(double h, double numero, double anterior){
    // Calculamos la derivada numérica.
    double der_num = NULL;
    der_num = (numero - anterior)/h;

    return der_num;
}

// Función que calcula la derivada Analítica por el método de diferencias centrales.

// Función principal del programa.
int main(){

    string infile = "posicion.txt";
    ifstream ff(infile);
    if (ff.is_open()){
        // Leemos el encabezado.
        string header;
        getline(ff,header);

        // Leemos el resto de líneas
        // Guardamos el número de líneas (útiles) del fichero en la variable nlen.
        double t = 0.0, x = 0.0;
        int nlen = 0;
        while (ff>>t>>x){
            ++nlen;
        }

        // Definimos los vectores tiempo y posición de forma dinámica.
        double* ts = new double[nlen];
        double* xm = new double[nlen];

        // Cerramos el fichero.
        ff.close(); ff.clear();

        // Volvemos a abrirlo.
        ff.open(infile);

        // No contamos el encabezado.
        getline(ff,header);

        // Guardamos los valores que hay en el fichero en los vectores.
        int i = 0;
        while (ff>>t>>x){
            ts[i] = t; xm[i] = x;
            ++i;
        }

        // Calculamos h.
        double hanterior = ts[1] - ts[0], hactual = 0.0, h = 0.0;
        double tol = 0.001;
        for (int i=0; i<nlen-1; i++){
            hactual = ts[i+1] - ts[i];
            if (hactual - hanterior > fabs(tol)){
                cout<<"Hay una variación de h en la posición "<<i+2<<" del fichero."<<endl;
            }
            hanterior = hactual;
        }

        h = hactual;

        // Calculamos la derivada numérica de las posiciones.
        double der_num[nlen];
        for (int i=0; i<nlen; i++){
            if (i==0){
                der_num[i] = DiferenciaAlante(h, xm[i+1], xm[i]);
            } else if (i==(nlen-1)){
                der_num[i] = DiferenciaAtras(h, xm[i], xm[i-1]);
            } else {
                der_num[i] = DiferenciasCentrales(h, xm[i+1], xm[i-1]);
            }
        }

        for (int i=0; i<nlen; i++){
            cout<<der_num[i]<<endl;
        }


    }


    return 0;
}