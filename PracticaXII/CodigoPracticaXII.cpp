#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

// Función que calcula la norma máxima de un vector. Pasando como parámetro un vector.
double NormaMaximaVector(double vector[], int len){
    double maximo = 0.0;
    for (int i=0; i<len; i++){
        if (fabs(vector[i])>maximo){
            maximo = fabs(vector[i]);
        }
    }

    return maximo;
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

// Función que calcula la derivada Analítica de x(t) = -70 + 7t + 70e^(-t/10) respeco a t que es igual a la velocidad.
double DerivadaVelocidad(double valor){
    // Definimos la derivada de la posición para cada valor pasado y lo devolvemos.
    double velocidad = 0.0;
    velocidad = 7 - (7*exp(-valor/10));

    return velocidad;
}

// Función que calcula la derivada Analítica de v(t) (función anterior) respeco a t que es igual a la aceleración.
double DerivadaAceleracion(double valor){
    // Definimos la derivada de la velocidad para cada valor pasado y lo devolvemos.
    double aceleracion = 0.0;
    aceleracion = 0.7*(exp(-valor/10.));

    return aceleracion;
}

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

        // Calculamos h (diferencia entre un valor y el anterior).
        double hanterior = ts[1] - ts[0], hactual = 0.0, h = 0.0;
        double tol = 0.001;
        for (int i=0; i<nlen-1; i++){
            hactual = ts[i+1] - ts[i];
            if (hactual - hanterior > fabs(tol)){
                cout<<"Hay una variación de h en la posición "<<i+2<<" del fichero."<<endl;
            }
            hanterior = hactual;
        } h = hactual;

        // Calculamos la derivada numérica de las posiciones = velocidades.
        double vel[nlen];
        for (int i=0; i<nlen; i++){
            if (i==0){
                vel[i] = DiferenciaAlante(h, xm[i+1], xm[i]);
            } else if (i==(nlen-1)){
                vel[i] = DiferenciaAtras(h, xm[i], xm[i-1]);
            } else {
                vel[i] = DiferenciasCentrales(h, xm[i+1], xm[i-1]);
            }
        }

        // Calculamos la derivada analítica de las posiciones = velocidades.
        double vel2[nlen];
        for (int i=0; i<nlen; i++){
            vel2[i] = DerivadaVelocidad(ts[i]);
        }

        // Calculamos el vector de errores cometidos en las velocidades.
        double errores1[nlen], errorvelocidad = 0.0;
        for (int i=0; i<nlen; i++){
            errores1[i] = vel2[i] - vel[i];
            errores1[i] = fabs(errores1[i]); 
        } errorvelocidad = NormaMaximaVector(errores1, nlen);
        cout<<"El error máximo cometido en la velocidad es: "<<errorvelocidad<<endl;

        // Calculamos la derivada numérica de las velocidades = aceleraciones.
        double a[nlen];
        for (int i=0; i<nlen; i++){
            if (i==0){
                a[i] = DiferenciaAlante(h, vel[i+1], vel[i]);
            } else if (i==(nlen-1)){
                a[i] = DiferenciaAtras(h, vel[i], vel[i-1]);
            } else {
                a[i] = DiferenciasCentrales(h, vel[i+1], vel[i-1]);
            }
        }

        // Calculamos la derivada analítica de las velocidades = aceleraciones.
        double a2[nlen];
        for (int i=0; i<nlen; i++){
            a2[i] = DerivadaAceleracion(ts[i]);
        }

        // Calculamos el vector de errores cometidos en las aceleraciones.
        double errores2[nlen], erroraceleracion = 0.0;
        for (int i=0; i<nlen; i++){
            errores2[i] = a2[i] - a[i];
            errores2[i] = fabs(errores2[i]); 
        } erroraceleracion = NormaMaximaVector(errores2, nlen);
        cout<<"El error máximo cometido en la velocidad es: "<<erroraceleracion<<endl;

        // Guardamos los resultados numéricos en un fichero.
        string file = "ResultadosNumericos.txt";
        ofstream ff(file);
        if (ff.is_open()){
            // Encabezados del fichero.
            ff << "                ---  DERIVACIÓN NUMÉRICA  ---"<<endl;
            ff << "Se muestran las derivadas de las posiciones y posteriormente de las velocidades hechas por métodos numéricos:"<<endl;
            ff << "Tiempo  Posición  Velocidad  Aceleración" << endl;
            
            // Iteramos para ir guardando todos los vectores.
            for (int i=0; i<nlen; i++){
                if (i==0){
                    ff << ts[i] << "\t\t ";
                    ff << xm[i] << "\t\t ";
                    ff << vel[i] << "\t";
                    ff << a[i] << endl;
                } else {
                    ff << ts[i] << "\t ";
                    ff << xm[i] << "\t ";
                    ff << vel[i] << "\t ";
                    ff << a[i] << endl;
                }
            }

            ff.close();
        }

        // Guardamos los resultados analíticos en otro fichero.
        string ffile = "ResultadosAnaliticos.txt";
        ofstream f(ffile);
        if (f.is_open()){
            // Encabezados del fichero.
            f << "                ---  DERIVACIÓN ANALÍTICA  ---"<<endl;
            f << "Se muestran las derivadas de las posiciones y posteriormente de las velocidades hechas de forma analítica:"<<endl;
            f << "Tiempo  Posición  Velocidad  Aceleración" << endl;
            
            // Iteramos para ir guardando todos los vectores.
            for (int i=0; i<nlen; i++){
                if (i==0){
                    f << ts[i] << "\t\t ";
                    f << xm[i] << "\t\t ";
                    f << vel2[i] << "\t\t";
                    f << a2[i] << endl;
                } else {
                    f << ts[i] << "\t ";
                    f << xm[i] << "\t ";
                    f << vel2[i] << "\t ";
                    f << a2[i] << endl;
                }
            }

            f.close();
        }
    }

    return 0;
}