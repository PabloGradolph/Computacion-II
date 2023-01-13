// Ejercicio 2 del examen final de prácticas de 2021. 
// Hecho para prácticar previo al examen.
// Autor: Pablo Gradolph Oliva.
// Fecha: 13/01/2023

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Solución exacta para comparar resultados al final.
double LaplaceReal(double ro){
    double a = 5.0, b = 10.0;
    double sol = 0.0;
    sol = (-50.0*log(ro/b))/(log(b/a));
    return sol;
}

matrix<double> SistemaYPrima(double ro, matrix<double> Y){
    // Creamos la matriz YPrima a partir del tamaño de la matriz pasada como argumento
    int row = 0, col = 0;
    row = Y.rowno(); col = Y.colno();
    matrix<double> YPrima(row, col); YPrima.null();

    // Definimos los valores de la matriz YPrima
    YPrima(0,0) = Y(1,0);
    YPrima(1,0) = (-1/(ro-(ro*ro)))*Y(1,0); 
    return YPrima;
}

matrix<double> RK4Sistemas(int n, double h, double romin, double romax, matrix<double> y0){
    // Definimos el número de pasos e inicializamos x.
    double npasos = 0.0, ro = romin;
    npasos = (romax - romin)/h;
    double error = 0.0;

    // Inicializamos la matriz Y.
    matrix<double> Y(n,1); Y.null();
    Y = y0;

    // Definimos las matrices K.
    matrix<double> k1(n,1); k1.null();
    matrix<double> k2(n,1); k2.null();
    matrix<double> k3(n,1); k3.null();
    matrix<double> k4(n,1); k4.null();
    k1 = SistemaYPrima(ro, Y);
    k2 = SistemaYPrima(ro + 0.5*h, Y + 0.5*h*k1);
    k3 = SistemaYPrima(ro + 0.5*h, Y + 0.5*h*k2);
    k4 = SistemaYPrima(ro + h, Y + h*k3);

    // Guardamos los valores en un fichero (calculando el resto de iteraciones).
    string file = "Ejercicio2_RK4.txt";
    ofstream ff(file);
    if (ff.is_open()){
        ff << setprecision(5);
        ff << "#DATOS PARA h=" << h << endl;
        ff << "ro\t\tFunción\t\tFunciónReal\t\tError" << endl;
        error = fabs(Y(0,0) - LaplaceReal(ro));
        ff << ro << "    " << Y(0,0) << "    " << LaplaceReal(ro) << "    " << error << endl;
        for (int i=1; i<=npasos; i++){
            Y = Y + 1/6. * (k1 + 2.*k2 + 2.*k3 + k4) * h;
            ro = ro + h;
            k1 = SistemaYPrima(ro, Y);
            k2 = SistemaYPrima(ro + 0.5*h, Y + 0.5*h*k1);
            k3 = SistemaYPrima(ro + 0.5*h, Y + 0.5*h*k2);
            k4 = SistemaYPrima(ro + h, Y + h*k3);
            error = fabs(Y(0,0) - LaplaceReal(ro));
            ff << ro << "    " << Y(0,0) << "    " << LaplaceReal(ro) << "    " << error << endl; 
        }
    }
    
    return Y;
}

int main(){
    // Definimos las variables que utilizaremos en la función.
    double h = 0.005;
    int n = 2;
    double romin = 5.0, romax = 10.0;
    double tol = 10e-6, errormax = 0.0;

    // Definimos la matriz inicial tras la primera suposición.
    matrix<double> y0(n, 1); y0.null();
    y0(0,0) = 50.0;
    y0(1,0) = 10.0;
    double dua1 = y0(1,0);

    // Definimos la matriz solución
    matrix<double> Y(n, 1); Y.null();

    // Llamamos a la función que resuelve por el método RK4
    Y = RK4Sistemas(n, h, romin, romax, y0);
    double ub1 = Y(0,0);
    
    // Obtenemos un u1(b) = 163.836 > 0 = ub
    // Entonces suponemos un u'1(a) más pequeño (multiplicamos por 0.5)
    
    y0(0,0) = 50.0;
    y0(1,0) = 5.0;
    double dua2 = y0(1,0);

    // Llamamos a la función que resuelve por el método RK4
    Y = RK4Sistemas(n, h, romin, romax, y0);
    double ub2 = Y(0,0);
    
    // Ahora hacemos el proceso de interpolación hasta que el resultado esté por debajo de 
    // la tolerancia
    int iteraciones = 0;

    do{
        y0(0,0) = 50.0;
        y0(1,0) = dua2 - ((ub2 - LaplaceReal(10.0)) * (dua2-dua1) / (ub2-ub1));

        Y = RK4Sistemas(n, h, romin, romax, y0);
        ub1 = ub2; ub2 = Y(0,0);
        dua1 = dua2; dua2 = y0(1,0);
        iteraciones++;
        
    }while(fabs(ub2 - LaplaceReal(10.0)) > tol);

    cout<<"Tras " << iteraciones << " iteraciones en el proceso de interpolación, se alcanza la tolerancia."<<endl;
    cout<<"El valor u(b) obtenido es: " << ub2 << endl;
    cout<<"En el fichero 'Pt16_RK4_1.txt' se encuentran el resto de resultados."<<endl;
    
    return 0;
}