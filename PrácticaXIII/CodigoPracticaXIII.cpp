#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

// Función que calcula los radianes en función de los grados pasado como argumento.
double Radianes(double grados){
    double rad = 0.0;
    rad = grados * (M_PI/180);
    return rad;
}

// Función que devuelve el valor de la función que usamos en nuestro caso.
double Funcion(double valorTH, double valorFi){
    // Definimos K (necesario en nuestro caso)
    double k = 0.0;
    k = sin(valorTH/2);

    // Definimos la función
    double funcion = 0.0;
    funcion = (2/M_PI)*(1/(sqrt(1-pow(k,2)*(pow(sin(valorFi),2)))));

    return funcion;
}

// Función que devuelve la función con cambio de variable que necesitamos para calcular la 
// Cuadratura Gaussiana.
double FuncionCG(double b, double a, double valorTH, double valorFi){
    // Definimos K (necesario en nuestro caso)
    double k = 0.0;
    k = sin(valorTH/2);

    // Definimos la función
    double funcion = 0.0;
    funcion = (2/M_PI)*((b - a)/2.0)*(1/(sqrt(1-k*k*(pow(sin(valorFi*(b - a)/2.0+(a+b)/2.0),2)))));

    return funcion;
}

// Función que calcula la integral por la regla trapezoidal.
double Trapezoidal(int n, double a, double b, double TH){
    // Calculamos h
    double h = 0.0;
    h = (b - a)/n;

    // Calculamos el sumatorio de los f(a + hi) que tenemos que calcular para éste método.
    // Lo hacemos en función de los distintos valores de Fi.
    double Fi = 0.0, sumatorio = 0.0;
    for (int i=1; i<n-1; i++){
        Fi = Fi + h;
        sumatorio = sumatorio + Funcion(TH,Fi);
    }
    
    // Calculamos la integral de la función con la regla trapezoidal.
    double I = 0.0;
    I = (h/2.0)*(Funcion(TH,a) + 2*sumatorio + Funcion(TH,b));

    return I;
}

// Función que calcula la integral por la regla de Simpson 1/3 n es par.
double Simpson(int n, double a, double b, double TH){
    // Calculamos h
    double h = 0.0;
    h = (b - a)/n;

    // Calculamos la parte f(x0) + 4f(x1) + 2f(x2) + ... + 4f(xn-1) + f(xn).
    double Fi = 0.0, sumatorio = 0.0;
    for (int i=0; i<=n; i++){
        if (i==0){
            sumatorio = sumatorio + Funcion(TH, Fi);
        } else if (i==n){
            sumatorio = sumatorio + Funcion(TH, Fi);
        } else if (i%2==0){
            sumatorio = sumatorio + (4*Funcion(TH, Fi));
        } else if (i%2!=0){
            sumatorio = sumatorio + (2*Funcion(TH, Fi));
        } Fi = Fi + h;
    }

    // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
    double I = 0.0;
    I = (h/3) * sumatorio;

    return I;
}

double CuadraturaGaussiana(int puntos){
    
    if (puntos == 1){
        double wi = 2.0, xi = 0.0;
    } else if (puntos == 2){
        double wi = 1, x1 = 1/sqrt(3), x2 = -1/sqrt(3);
    } else if (puntos == 3){
        
    }
    
    // Calculamos la integral
    double I = 0.0;
    
    return I;
}

int main(){

    //
    // Comprobación de que la función funciona :)
    // double funcion = 0.0;
    // funcion = Funcion(0, M_PI/8);
    // cout<<funcion<<endl;
    //

    //
    // Comprobación de que la integral funciona :)
    // double I = 0.0;
    // I = Trapezoidal(4, 0, M_PI/2, 0);
    // cout<<I;
    //

    // Calculamos todas las integrales (regla trapecio 4 intervalos) variando el valor TH.
    // Vamos guardando los resultados en un fichero.
    string infile = "Trapezoidal4intervalos.txt";
    ofstream file(infile);
    if (file.is_open()){
        // Encabezados del fichero.
        file << "Método trapezoidal para 4 intervalos:"<<endl;
        file << "Se muestran todas las integrales variando el valor de Theta de 0 a 100º de 5 en 5º:"<<endl;
        file << "Theta" << "\t" << "T/T'" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        double theta = 0.0, I = 0.0;
        for (int TH=0; TH<=100; TH=TH+5){
            theta = Radianes(TH);
            I = Trapezoidal(4, 0, M_PI/2, theta);
            file << TH << "\t" << I << endl;
        }

        file.close();
    }

    // Calculamos todas las integrales (regla trapecio 20 intervalos) variando el valor TH.
    // Vamos guardando los resultados en un fichero.
    string afile = "Trapezoidal20intervalos.txt";
    ofstream f(afile);
    if (f.is_open()){
        // Encabezados del fichero.
        f << "Método trapezoidal para 20 intervalos:"<<endl;
        f << "Se muestran todas las integrales variando el valor de Theta de 0 a 100º de 5 en 5º:"<<endl;
        f << "Theta" << "\t" << "T/T'" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        double theta = 0.0, I = 0.0;
        for (int TH=0; TH<=100; TH=TH+5){
            theta = Radianes(TH);
            I = Trapezoidal(20, 0, M_PI/2, theta);
            f << TH << "\t" << I << endl;
        }

        f.close();
    }

    // Calculamos todas las integrales (regla simpson 4 intervalos) variando el valor TH.
    // Vamos guardando los resultados en un fichero.
    string bfile = "Simpson4intervalos.txt";
    ofstream ff(bfile);
    if (ff.is_open()){
        // Encabezados del fichero.
        ff << "Método Simpson 1/3 compuesto para 4 intervalos:"<<endl;
        ff << "Se muestran todas las integrales variando el valor de Theta de 0 a 100º de 5 en 5º:"<<endl;
        ff << "Theta" << "\t" << "T/T'" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        double theta = 0.0, I = 0.0;
        for (int TH=0; TH<=100; TH=TH+5){
            theta = Radianes(TH);
            I = Simpson(4, 0, M_PI/2, theta);
            ff << TH << "\t" << I << endl;
        }

        ff.close();
    }

    // Calculamos todas las integrales (regla simpson 20 intervalos) variando el valor TH.
    // Vamos guardando los resultados en un fichero.
    string cfile = "Simpson20intervalos.txt";
    ofstream ffl(cfile);
    if (ffl.is_open()){
        // Encabezados del fichero.
        ffl << "Método Simpson 1/3 compuesto para 20 intervalos:"<<endl;
        ffl << "Se muestran todas las integrales variando el valor de Theta de 0 a 100º de 5 en 5º:"<<endl;
        ffl << "Theta" << "\t" << "T/T'" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        double theta = 0.0, I = 0.0;
        for (int TH=0; TH<=100; TH=TH+5){
            theta = Radianes(TH);
            I = Simpson(20, 0, M_PI/2, theta);
            ffl << TH << "\t" << I << endl;
        }

        ff.close();
    }

    return 0;
}