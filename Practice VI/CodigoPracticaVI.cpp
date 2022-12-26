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
    resultado = pow(1/PuntoX, 6) - (exp(-PuntoX));
    return resultado;
}

// Función derivada de f(x).
double FuncionDerivada(double PuntoX){
    double resultado;
    resultado = -6 * (1/pow(PuntoX, 7)) + (exp(-PuntoX));
    return resultado;
}

// Función para obtener el resultado por el método de la Bisección imprimiendo por pantalla el resultado.
int Biseccion1(double PuntoX1, double PuntoX2, double tol,int n){
    double PuntoX3, FuncionX3;

    PuntoX3 = (PuntoX1 + PuntoX2)/2.; // Definimos el nuevo punto
    FuncionX3 = Funcion(PuntoX3); // Valor de la función en ese punto.
    if (FuncionX3 < tol && FuncionX3 > -tol){ // Si el valor está muy cerca de cero (en función de la tolerancia) retornamos los valores.
        cout<<"Iteración: "<<n<<" x = "<<PuntoX3<<" f(x) = "<<FuncionX3<<endl;
        return n;
    } else { // Si no se vuelve a ejecutar la misma función cambiando los valores de entrada.
        // Función recursiva.
        // En función del punto que cumpla el Teorema de Bolzano introducimos unos valores u otros.
        if (Funcion(PuntoX3) < 0 && Funcion(PuntoX2) > 0){
            n = n + 1;
            Biseccion1(PuntoX3, PuntoX2, tol, n);
        } else if (Funcion(PuntoX3) > 0 && Funcion(PuntoX2) < 0){
            n = n + 1;
            Biseccion1(PuntoX3, PuntoX2, tol, n);
        } else {
            n = n + 1;
            Biseccion1(PuntoX3, PuntoX1, tol, n);
        }
    }
}

// Función para obtener el resultado por el método de la Bisección sin imprimir por pantalla el resultado.
int Biseccion2(double PuntoX1, double PuntoX2, double tol,int n){
    double PuntoX3, FuncionX3;

    // Misma dinámica que en la función anterior pero sin imprimir los resultados.
    PuntoX3 = (PuntoX1 + PuntoX2)/2.;
    FuncionX3 = Funcion(PuntoX3);
    if (FuncionX3 < tol && FuncionX3 > -tol){
        return n;
    } else {
        if (Funcion(PuntoX3) < 0 && Funcion(PuntoX2) > 0){
            n = n + 1;
            Biseccion2(PuntoX3, PuntoX2, tol, n);
        } else if (Funcion(PuntoX3) > 0 && Funcion(PuntoX2) < 0){
            n = n + 1;
            Biseccion2(PuntoX3, PuntoX2, tol, n);
        } else {
            n = n + 1;
            Biseccion2(PuntoX3, PuntoX1, tol, n);
        }
    }
}

// Función para obtener el resultado por el método de la Secante imprimiendo por pantalla el resultado.
int Secante1(double PuntoX0, double PuntoX1, double tol, int n){
    double PuntoX2, FuncionX2;

    PuntoX2 = PuntoX1 - (Funcion(PuntoX1)*((PuntoX0 - PuntoX1)/(Funcion(PuntoX0) - Funcion(PuntoX1))));
    FuncionX2 = Funcion(PuntoX2); // Calculamos el punto y el valor de la función en dicho punto.
    if (FuncionX2 < tol && FuncionX2 > -tol){
        // Si estamos muy cerca de cero (en función de la tolerancia) imprimimos los resultados.
        cout<<"Iteración: "<<n<<" x = "<<PuntoX2<<" f(x) = "<<FuncionX2<<endl;
        return n;
    } else { // Sino, seguimos el proceso llamando de nuevo a la función pero con los nuevos puntos.
        n = n + 1;
        Secante1(PuntoX1, PuntoX2, tol, n);
    }
}

// Función para obtener el resultado por el método de la Secante sin imprimir por pantalla el resultado.
int Secante2(double PuntoX0, double PuntoX1, double tol, int n){
    double PuntoX2, FuncionX2;

    // Misma dinámica que en la función anterior pero sin imprimir los resultados.
    PuntoX2 = PuntoX1 - (Funcion(PuntoX1)*((PuntoX0 - PuntoX1)/(Funcion(PuntoX0) - Funcion(PuntoX1))));
    FuncionX2 = Funcion(PuntoX2);
    if (FuncionX2 < tol && FuncionX2 > -tol){
        return n;
    } else {
        n = n + 1;
        Secante2(PuntoX1, PuntoX2, tol, n);
    }
}   

// Función para obtener el resultado por el método de Newton imprimiendo por pantalla el resultado.
int Newton1(double PuntoX0, double tol, int n){
    double PuntoX1, FuncionX1, DerivadaX1;

    PuntoX1 = PuntoX0 - (Funcion(PuntoX0)/FuncionDerivada(PuntoX0));
    FuncionX1 = Funcion(PuntoX1); // Definimos el punto que necesitamos y el valor de la función en ese punto.
    if (FuncionX1 < tol && FuncionX1 > -tol){
        // Si estamos muy cerca de cero (en función de la tolerancia) imprimimos los resultados.
        cout<<"Iteración: "<<n<<" x = "<<PuntoX1<<" f(x) = "<<FuncionX1<<endl;
        return n;
    } else { // Sino, seguimos el proceso llamando de nuevo a la función pero con los nuevos puntos.
        n = n + 1;
        Newton1(PuntoX1, tol, n);
    }
}

// Función para obtener el resultado por el método de Newton sin imprimir por pantalla el resultado.
int Newton2(double PuntoX0, double tol, int n){
    double PuntoX1, FuncionX1, DerivadaX1;

    // Misma dinámica que en la función anterior pero sin imprimir los resultados.
    PuntoX1 = PuntoX0 - (Funcion(PuntoX0)/FuncionDerivada(PuntoX0));
    FuncionX1 = Funcion(PuntoX1);
    if (FuncionX1 < tol && FuncionX1 > -tol){
        return n;
    } else {
        n = n + 1;
        Newton2(PuntoX1, tol, n);
    }
}

int main(){
    // Definimos los puntos que vamos a usar para las distintas funciones.
    double PuntoX1 = 1.2, PuntoX2 = 1.4, tol = 0.001;
    double PuntoS0 = 1.3, PuntoS1 = 1.25;
    // Definimos el número de iteraciones.
    int nb, ns, nn;
    // Establecemos la precisión que queremos al imprimir los datos por pantalla.
    cout<<setprecision(15);

    // Llamamos a la función bisección1 que es la que imprime por pantalla.
    cout<<"MÉTODO BISECCIÓN:"<<endl;
    nb = Biseccion1(PuntoX1, PuntoX2, tol, 0);

    // Llamamos a la función secante1 que es la que imprime por pantalla.
    cout<<endl;
    cout<<"MÉTODO SECANTE:"<<endl;
    ns = Secante1(PuntoS0, PuntoS1, tol, 0);

    // Llamamos a la función Newton1 que es la que imprime por pantalla.
    cout<<endl;
    cout<<"MÉTODO NEWTON:"<<endl;
    nn = Newton1(PuntoX1, tol, 0);
    
    // Guardamos en el fichero iteraciones.
    // Para ello utilizamos las funciones con número 2 que no imprimen por pantalla.
    string infile = "iteraciones.txt";
    ofstream ff(infile);
    if (ff.is_open()){
        ff << "#ITERACIONES\n";
        ff << "eps\t\tnb\t\tns\t\tnn\n";
        for (int i = 3; i <= 12; i++){
            nb = Biseccion2(PuntoX1, PuntoX2, tol, 0);
            ns = Secante2(PuntoS0, PuntoS1, tol, 0);
            nn = Newton2(PuntoX1, tol, 0);
            ff << tol << "\t\t" << nb << "\t\t" << ns << "\t\t" << nn <<endl;
            tol = tol/10;
        }
    }
    
    return 0;
}
