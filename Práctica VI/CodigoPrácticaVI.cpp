// Función: f(x) = (1/x)^6 - exp(-x)
// Búsqueda del cero de la función en el intervalo x = [1.2, 1.4]
// Métodos que vamos a utilizar: Bisección, Secante y Newton.
// Tolerancia = 10^-6

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;




// Función f(x).
double Funcion(double PuntoX){
    double resultado;
    resultado = pow(1/PuntoX, 6) - exp(-PuntoX);
    return resultado;
}

// Función derivada de f(x).
double FuncionDerivada(double PuntoX){
    double resultado;
    resultado = -6 * (1/pow(PuntoX, 2)) + exp(-PuntoX);
    return resultado;
}

// Función para obtener el resultado por el método de la Bisección.
double Biseccion(double PuntoX1, double PuntoX2, double tol){
    double PuntoX3, FuncionX3;

    PuntoX3 = (PuntoX1 + PuntoX2)/2.;
    FuncionX3 = pow(1/PuntoX3, 6) - exp(-PuntoX3);
    if (FuncionX3 < tol && FuncionX3 > -tol){
        cout<<"Para el punto x = "<<PuntoX3<<endl;
        return FuncionX3;
    } else {
        if (Funcion(PuntoX3) < 0 && Funcion(PuntoX2) > 0){
            Biseccion(PuntoX3, PuntoX2, tol);
        } else if (Funcion(PuntoX3) > 0 && Funcion(PuntoX2) < 0){
            Biseccion(PuntoX3, PuntoX2, tol);
        } else {
            Biseccion(PuntoX3, PuntoX1, tol);
        }
    }
}

// Función para obtener el resultado por el método de la Secante.
int Secante(double PuntoX0, double PuntoX1, double tol, int n){
    double PuntoX2, FuncionX2;

    PuntoX2 = PuntoX1 - (Funcion(PuntoX1)*((PuntoX0 - PuntoX1)/(Funcion(PuntoX0) - Funcion(PuntoX1))));
    FuncionX2 = Funcion(PuntoX2);
    if (FuncionX2 < tol && FuncionX2 > -tol){
        cout<<"Iteración: "<<n<<" x = "<<PuntoX2<<" f(x) = "<<FuncionX2<<endl;
        return n;
    } else {
        cout<<"Iteración: "<<n<<" x = "<<PuntoX2<<" f(x) = "<<FuncionX2<<endl;
        n = n + 1;
        Secante(PuntoX1, PuntoX2, tol, n);
    }
}   

double Newton(double PuntoX0, double tol){
    double PuntoX1, FuncionX1, DerivadaX1;

    PuntoX1 = PuntoX0 - (Funcion(PuntoX0)/FuncionDerivada(PuntoX0));
    FuncionX1 = Funcion(PuntoX1);
    if (FuncionX1 < tol && FuncionX1 > -tol){
        cout<<"Para el punto x = "<<PuntoX1<<endl;
        return FuncionX1;
    } else {
        Newton(PuntoX1, tol);
    }
}

int main(){
    double PuntoX1 = 1.2, PuntoX2 = 1.4, tol = 0.0000004, resultado;
    int nb, ns, nn;
    cout<<setprecision(15);

    // Llamamos a la función bisección
    cout<<"MÉTODO BISECCIÓN:"<<endl;
    resultado = Biseccion(PuntoX1, PuntoX2, tol);
    cout<<"La función tiene un valor, f(x) = "<<resultado<<endl;

    double PuntoX0 = 1.3;
    PuntoX1 = 1.25;
    // Llamamos a la función secante.
    cout<<endl;
    cout<<"MÉTODO SECANTE:"<<endl;
    ns = Secante(PuntoX0, PuntoX1, tol, 1);



    // Llamamos a la función Newton.
    PuntoX0 = 1.2;
    cout<<endl;
    cout<<"MÉTODO NEWTON:"<<endl;
    resultado = Newton(PuntoX0, tol);
    cout<<"La función tiene un valor, f(x) = "<<resultado<<endl;

    // Guardamos en el fichero iteraciones.
    string infile = "iteraciones.txt";
    ofstream ff(infile);
    if (ff.is_open()){
        ff << "#ITERACIONES\n";
        ff << "\tnb\tns\tnn\n";
    }
    return 0;
}