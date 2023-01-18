// Ejercicio 1 del examen final de prácticas de 2022. 
// Hecho para prácticar previo al examen.
// Autor: Pablo Gradolph Oliva.
// Fecha: 15/01/2023

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

// Función que devuelve el valor real de f(x)
double FuncionReal(double x){
    double funcion;
    funcion = log(x);
    return funcion;
}

// Función que queremos integrar por la regla Simpson 1/3
double Funcion(double x){
    double funcion;
    funcion = 1/x;
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
    double x = a,  sumatorio = 0.0;
    for (int i=0; i<=n; i++){
        if (i==0){
            sumatorio = sumatorio + Funcion(x);
        } else if (i==n){
            sumatorio = sumatorio + Funcion(x);
        } else if (i%2==0){
            sumatorio = sumatorio + (2*Funcion(x));
        } else if (i%2!=0){
            sumatorio = sumatorio + (4*Funcion(x));
        } x = x + h;
    }

    // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
    double I = 0.0;
    I = (h/3) * sumatorio;

    return I;
}

int main(){

    // Variables iniciales.
    double xmin = 1.0, h = 0.1, xmax = 9.0, tol = 10e-10;

    // Guardamos los resultados en un fichero de salida.
    string gfile = "ResultadosPractica1.txt";
    ofstream ffile(gfile);
    if (ffile.is_open()){
        // Encabezados del fichero.
        ffile << "                ---  LOGARITMO NEPERIANO POR INTEGRAL  ---"<<endl;
        ffile << "Se muestran todas las integrales variando el límite superior de 1 a 9:"<<endl;
        ffile << "INTERVALO \t INTEGRAL(Simpson 1/3) \t VALOR REAL \t ITERACIONES" << endl;
        ffile << setprecision(10);

        // Definimos la integral
        double I = 0.0;

        // Recorremos el intervalo [-4,4] con pasos de 0.1
        for (int x = xmin; x<=xmax; x++){
            // x será el límite superior de la integral en cada iteración.
            // Variamos el número de intervalos hasta que se alcance la tolerancia para cada límite superior.
            // Calculamos también el número de iteraciones que son necesarias para cada valor de x.
            int n = 2, iteraciones = 0;
            do {
                I = Simpson(n, xmin, x);
                n = n + 2;
                iteraciones++;
            }while (fabs(I-FuncionReal(x))>tol);

            // Cuando se alcance la precisión lo escribimos en el fichero.
            ffile << "[1,"<<x<<"] \t\t" << I << "\t\t" << FuncionReal(x) << "\t\t" << iteraciones << endl;
        }

        cout<<"Puedes encontrar los resultados de las integrales para los distintos intervalos en el fichero:"<<endl;
        cout<<gfile<<endl<<endl;

        //
        // Para valores más grandes del límite superior de la integral, se necesitan más iteraciones para aproximar la solución,
        // es decir, un valor de intervalos n mayor. Esto supone que si el límite superior de la integral es muy grande, costará más llegar a una 
        // buena aproximación. Sin embargo, el sistema es útil para aproximar el logaritmo neperiano.
        // 

        //
        // El ejercicio 2 se corresponde con la práctica XVIII.
        //
        
        ffile.close();
    }

    return 0;
}