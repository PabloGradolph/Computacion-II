#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función x(t) simplificada.
double Funcion(double t){
    double resultado;
    resultado = ((245*(1-exp(-2*t/5.)))/4.) - (49*t/2.) + (2286/25.);
    return resultado;
}

// Función derivada de x(t)
double FuncionDerivada(double t){
    double resultado;
    resultado = (49*exp(-2*t/5.)/2.0) - 49/2.;
    return resultado;
}

// Función para obtener el resultado por el método de la Bisección imprimiendo por pantalla el resultado.
int Biseccion(double PuntoX1, double PuntoX2, double tol, int n){
    double PuntoX3, FuncionX3;
    
    PuntoX3 = (PuntoX1 + PuntoX2)/2.; // Definimos el nuevo punto
    FuncionX3 = Funcion(PuntoX3); // Valor de la función en ese punto.

    // Calculamos el error tras la iteración
    double error = 0.0;
    error = fabs(FuncionX3);
    if (n>0){
        cout<<error<<endl;
    }
    

    if (FuncionX3 < tol && FuncionX3 > -tol){ // Si el valor está muy cerca de cero (en función de la tolerancia) retornamos los valores.
        cout<<"Iteración: "<<n<<" t = "<<PuntoX3<<" x(t) = "<<FuncionX3<<endl;
        return error;
    } else { // Si no se vuelve a ejecutar la misma función cambiando los valores de entrada.
        // Función recursiva.
        // En función del punto que cumpla el Teorema de Bolzano introducimos unos valores u otros.
        if (Funcion(PuntoX3) < 0 && Funcion(PuntoX2) > 0){
            n = n + 1;
            Biseccion(PuntoX3, PuntoX2, tol, n);
        } else if (Funcion(PuntoX3) > 0 && Funcion(PuntoX2) < 0){
            n = n + 1;
            Biseccion(PuntoX3, PuntoX2, tol, n);
        } else {
            n = n + 1;
            Biseccion(PuntoX3, PuntoX1, tol, n);
        }
    }
}

// Función para obtener el resultado por el método de la Secante imprimiendo por pantalla el resultado.
int Secante(double PuntoX0, double PuntoX1, double tol, int n){
    double PuntoX2, FuncionX2;

    PuntoX2 = PuntoX1 - (Funcion(PuntoX1)*((PuntoX0 - PuntoX1)/(Funcion(PuntoX0) - Funcion(PuntoX1))));
    FuncionX2 = Funcion(PuntoX2); // Calculamos el punto y el valor de la función en dicho punto.
    
    // Calculamos el error tras la iteración
    double error = 0.0;
    error = fabs(FuncionX2);
    cout<<error<<endl;

    if (FuncionX2 < tol && FuncionX2 > -tol){
        // Si estamos muy cerca de cero (en función de la tolerancia) imprimimos los resultados.
        n = n + 1;
        cout<<"Iteración: "<<n<<" t = "<<PuntoX2<<" x(t) = "<<FuncionX2<<endl;
        return n;
    } else { // Sino, seguimos el proceso llamando de nuevo a la función pero con los nuevos puntos.
        n = n + 1;
        Secante(PuntoX1, PuntoX2, tol, n);
    }
}

// Función para obtener el resultado por el método de Newton imprimiendo por pantalla el resultado.
double Newton(double PuntoX0, double tol, int n){
    // Definimos las variables que vamos a usar.
    double PuntoX1, FuncionX1, DerivadaX1;

    PuntoX1 = PuntoX0 - (Funcion(PuntoX0)/FuncionDerivada(PuntoX0));
    FuncionX1 = Funcion(PuntoX1); // Definimos el punto que necesitamos y el valor de la función en ese punto.
    
    // Calculamos el error tras la iteración
    double error = 0.0;
    error = fabs(FuncionX1);
    cout<<error<<endl;

    if (FuncionX1 < tol && FuncionX1 > -tol){
        // Si estamos muy cerca de cero (en función de la tolerancia) imprimimos los resultados.
        n = n + 1;
        cout<< "Iteración: "<<n<<" t = "<<PuntoX1<<" x(t) = "<<FuncionX1<<endl;
        return PuntoX1;
    } else { // Sino, seguimos el proceso llamando de nuevo a la función pero con los nuevos puntos.
        n = n + 1;
        Newton(PuntoX1, tol, n);
    }
}

int main(){
    // Definimos los puntos que vamos a usar para las distintas funciones.
    double t1 = 5.5, t2 = 6.5, tol = 0.000001;
    double S0 = 5.0, S1 = 5.5, N1 = 5.5;
    int n = 0;

    // Iteraciones por método
    int nb, ns, nn;

    // Llamamos a la función bisección que es la que imprime por pantalla.
    cout<<"MÉTODO BISECCIÓN:"<<endl;
    cout<<"Errores:"<<endl;
    nb = Biseccion(t1, t2, tol, 0);

    // Llamamos a la función secante que es la que imprime por pantalla.
    cout<<endl;
    cout<<"MÉTODO SECANTE:"<<endl;
    cout<<"Errores:"<<endl;
    ns = Secante(S0, S1, tol, 0);

    // Llamamos a la función Newton que es la que imprime por pantalla.
    // Para el punto inicial converge a otra raíz.
    // Por esta razón elegiremos otro punto inicial t0 = 3.8
    cout<<endl;
    cout<<"MÉTODO NEWTON:"<<endl;
    cout<<"Errores:"<<endl;
    nn = Newton(N1, tol, 0);

    return 0;
}