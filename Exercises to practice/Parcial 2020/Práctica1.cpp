// Computación II: Primer examen parcial de prácticas.
// Se realizó el 6 de noviembre de 2020.
// Fecha actual: 23 de noviembre de 2022

// Código del primer ejercicio
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

// Función f(x) = x(x+5) - e^x + 2.
double Funcion(double PuntoX){
    double resultado;
    resultado = PuntoX*PuntoX + 5*PuntoX - exp(PuntoX) + 2;
    return resultado;
}

// Función derivada de f(x) = 2x + 5 - e^x.
double FuncionDerivada(double PuntoX){
    double resultado;
    resultado = 2*PuntoX + 5 - exp(PuntoX);
    return resultado;
}

// Función para obtener el resultado por el método de Newton imprimiendo por pantalla el resultado.
double Newton(double PuntoX0, double tol, int& n){
    // Definimos las variables que vamos a usar.
    double PuntoX1, FuncionX1, DerivadaX1;

    PuntoX1 = PuntoX0 - (Funcion(PuntoX0)/FuncionDerivada(PuntoX0));
    FuncionX1 = Funcion(PuntoX1); // Definimos el punto que necesitamos y el valor de la función en ese punto.
    if (FuncionX1 < tol && FuncionX1 > -tol){
        // Si estamos muy cerca de cero (en función de la tolerancia) imprimimos los resultados.
        cout<< "Iteración: "<<n<<" x = "<<PuntoX1<<" f(x) = "<<FuncionX1<<endl;
        return PuntoX1;
    } else { // Sino, seguimos el proceso llamando de nuevo a la función pero con los nuevos puntos.
        n = n + 1;
        Newton(PuntoX1, tol, n);
    }
}

int main(){
    // Definimos la tolerancia y las iteraciones.
    double tol = 0.0004, PuntoX1 = 0.0;
    int n = 0, contador1 = 0, contador2 = 0, contador3 = 0;

    // Vectores donde guardaremos los puntos iniciales con la misma solución:
    // vector1 = puntos iniciales con solución -4.5642 (son 40 soluciones).
    // vector2 = puntos iniciales con solución -0.25907 (son 37 soluciones).
    // vector3 = puntos iniciales con solución 3.432 (son 34 soluciones).
    double vector1[40], vector2[37], vector3[34];
    // Creamos un bucle en el que la i sume 0.1 cada vez (i hará de punto inicial)
    // Guardamos los datos en un fichero.
    string infile = "IteracionesNewton.txt";
    ofstream ff(infile);
    if (ff.is_open()){
        cout<<setprecision(5);
        ff<<setprecision(5);
        ff << "#ITERACIONES NEWTON\n";
        ff << "X0\titeraciones\tXfinal\n";
        for (float i = -6.0; i<=5; i = i + 0.1){
            cout<<"Para X0 = "<<i<<endl;
            PuntoX1 = Newton(i, tol, n);
            cout<<endl;
            ff << i << "\t\t" << n << "\t\t" << PuntoX1 <<endl;

            // Una vez hemos visto que la función tiene 3 soluciones en el intervalo dado las vamos a agrupar.
            if (fabs(PuntoX1 + 4.5642) < 0.01){
                vector1[contador1] = i;
                contador1++;
            } else if (fabs(PuntoX1 + 0.25907) < 0.01){
                vector2[contador2] = i;
                contador2++;
            } else {
                vector3[contador3] = i;
                contador3++;
            }
        }

        // Imprimimos los vectores con las mismas soluciones:
        cout<<"Puntos iniciales cuya solución es: -4.5642"<<endl;
        for (int i=0; i<40; i++){
            cout<<vector1[i]<<" | ";
        }

        cout<<endl;
        cout<<endl;
        cout<<"Puntos iniciales cuya solución es: -0.25907"<<endl;
        for (int i=0; i<37; i++){
            cout<<vector2[i]<<" | ";
        }

        cout<<endl;
        cout<<endl;
        cout<<"Puntos iniciales cuya solución es: 3.432"<<endl;
        for (int i=0; i<=34; i++){
            cout<<vector3[i]<<" | ";
        }
    }

    return 0;
}

    
