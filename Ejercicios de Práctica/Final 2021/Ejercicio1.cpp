// Ejercicio 1 del examen final de prácticas de 2021. 
// Hecho para prácticar previo al examen.
// Autor: Pablo Gradolph Oliva.
// Fecha: 13/01/2023

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

// Función que devuelve el valor real de f(x)
double FuncionGaussiana(double x){
    double funcion;
    funcion = (exp(-(x*x)/2))/(sqrt(2*M_PI)) ;
    return funcion;
}

// Función que calcula la integral por la regla de Simpson 1/3 n es par.
double Simpson(int n, double a, double b){

    // Control de errores en la entrada de n
    if (n%2!=0){
        cout<<"El valor n introducido es impar: n = "<<n<<endl;
        cout<<"No se puede seguir el método Simpson 1/3"<<endl;
        return n;
    }

    // Calculamos h
    double h = 0.0;
    h = (b - a)/n;

    // Calculamos la parte f(x0) + 4f(x1) + 2f(x2) + ... + 4f(xn-1) + f(xn).
    double x = -4.0,  sumatorio = 0.0;
    for (int i=0; i<=n; i++){
        if (i==0){
            sumatorio = sumatorio + FuncionGaussiana(x);
        } else if (i==n){
            sumatorio = sumatorio + FuncionGaussiana(x);
        } else if (i%2==0){
            sumatorio = sumatorio + (2*FuncionGaussiana(x));
        } else if (i%2!=0){
            sumatorio = sumatorio + (4*FuncionGaussiana(x));
        } x = x + h;
    }

    // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
    double I = 0.0;
    I = (h/3) * sumatorio;

    return I;
}

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

int main(){

    //
    // APARTADO A
    //

    // Variables iniciales.
    double xmin = -4.0, h = 0.1, xmax = 4;
    int n = 100;

    // Vectores que servirán para el cálculo del apartado b.
    int nlen = (xmax - xmin)/h, i = 0;
    double vecx[nlen], vecI[nlen];

    // Guardamos los resultados en un fichero de salida.
    string gfile = "ResultadosIntegral.txt";
    ofstream ffile(gfile);
    if (ffile.is_open()){
        // Encabezados del fichero.
        ffile << "                ---  INTEGRAL DE LA FUNCIÓN GAUSSIANA  ---"<<endl;
        ffile << "Se muestran todas las integrales variando el límite superior de hasta donde se calcula la integral:"<<endl;
        ffile << "INTERVALO \t INTEGRAL(Simpson 1/3)" << endl;
        ffile << setprecision(10);

        // Definimos la integral
        double I = 0.0;

        // Recorremos el intervalo [-4,4] con pasos de 0.1
        for (double x = xmin; x<=xmax+h; x=x+h){
            // x será el límite superior de la integral en cada iteración.
            I = Simpson(n, xmin, x);
            ffile << "[-4,"<<x<<"] \t" << I <<endl;
            vecx[i] = x; vecI[i] = I;
            i++;
        }

        cout<<"Puedes encontrar los resultados de las integrales para los distintos intervalos en el fichero:"<<endl;
        cout<<gfile<<endl<<endl;

        ffile.close();
    }

    //
    // APARTADO B
    //

    // Ya tenemos guardados los valores de x y los de las integrales correspondientes en vectores.
    
    // Calculamos la derivada numérica de las integrales anteriores.
    double der[nlen];
    for (int i=0; i<nlen; i++){
        if (i==0){
            der[i] = DiferenciaAlante(h, vecI[i+1], vecI[i]);
        } else if (i==(nlen-1)){
            der[i] = DiferenciaAtras(h, vecI[i], vecI[i-1]);
        } else {
            der[i] = DiferenciasCentrales(h, vecI[i+1], vecI[i-1]);
        }
    }
    
    // Calculamos la derivada analítica que se corresponde con la función gaussiana:
    double der2[nlen];
    for (int i=0; i<nlen; i++){
        der2[i] = FuncionGaussiana(vecx[i]);
    }

    // Error (APARTADO C)
    double err[nlen];
    for (int i=0; i<nlen; i++){
        err[i] = der[i] - der2[i];
    }

    // Guardamos los resultados en un fichero de salida.
    string file = "ResultadosDerivadas.txt";
    ofstream ff(file);
    if (ff.is_open()){
        // Encabezados del fichero.
        ff << "                ---  DERIVADA NUMÉRICA DE LAS INTEGRALES  ---"<<endl;
        ff << "Se muestran todas las derivadas numéricas de las integrales del fichero ResultadosIntegrales.txt:"<<endl;
        ff << "Se ha utlizado el método de las diferencias centrales. También se muestra la solución analítica."<<endl;
        ff << "INTERVALO \t DERIVADA NUMÉRICA \t SOLUCIÓN ANALÍTICA \t ERROR RELATIVO" << endl;
        ff << setprecision(10);

        // Recorremos el intervalo [-4,4] con pasos de 0.1
        i = 0;
        for (double x = xmin; x<=xmax+h; x=x+h){
            
            ff << "[-4,"<<x<<"] \t" << der[i] << "\t" << der2[i] << "\t" << err[i] <<endl;
            i++;
        }

        cout<<"Puedes encontrar los resultados de las derivadas en el fichero:"<<endl;
        cout<<file<<endl<<endl;

        ff.close();
    }

    //
    // Habría que repetir el proceso para otros valores de h.
    //

    return 0;
}
