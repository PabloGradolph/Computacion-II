// Código Práctica XIX
// Ecuaciones diferenciales ordinarias: Ecuación del calor.
// Autor: Pablo Gradolph Oliva
// Fecha: 15/12/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

matrix<double> EcuacionCalor(double k, double incrementoX, double incrementoT, double Xfinal, double Tfinal){
    // Primero calculamos el valor de r
    double r = 0.0;
    r = (k*incrementoT)/(incrementoX*incrementoX);

    // Si el valor de r no asegura convergencia, volvemos a pedir incrementos hasta que r<0.5
    // No siempre es necesario, esto lo meteremos cuando queramos asegurar la convergencia.
    /*while (r>0.5){
        cout<<"El valor de r es mayor a 0.5 por favor introduzca valores de incrementos para cumplir que r<0.5"<<endl;
        cout<<"Para ello, tenga en cuenta que r = (k*incrementoT)/(incrementoX*incrementoX) y que k = "<<k<<endl;
        cout<<"Introduce un incremento de X: "<<endl; cin>>incrementoX;
        cout<<"Introduce un incremento de t: "<<endl; cin>>incrementoT;
        r = (k*incrementoT)/(incrementoX*incrementoX);
    }*/

    // Inicializamos x y t a los valores iniciales (0).
    double x = 0.0;
    
    // Una vez tenemos un valor de r correcto, calculamos el número de pasos, tamaño vector.
    double nt = 0.0, nx = 0.0;
    nt = Tfinal/incrementoT; nt = int(nt);
    nx = Xfinal/incrementoX; nx = int(nx);
    
    // Definimos el vector u con el valor inicial.
    matrix<double> u0(nx,1); u0.null();
    for (int i=0; i<=nx; i++){
        if (x>=0 && x<50){
            u0(i,0) = 0;
        } else {
            u0(i,0) = 10;
        } x = x + incrementoX;
    }

    
    // Iteramos para todos los valores del tiempo.
    matrix<double> u(nx,1); u.null();
    for (double t=0; t<=Tfinal; t=t+incrementoT){
        for (int i=0; i<=nx; i++){
            if (i==0){
                u(i,0) = 0;
            } else if (i==nx){
                u(i,0) = 10;
            } else {
                u(i,0) = (1-2*r)*u0(i,0) + r*(u0(i-1,0) + u0(i+1,0));
            }
        } u0 = u;
    }

    return u;
}

int main(){
    // Definimos las que serán constantes:
    double L = 100.0, Tfinal = 300.0, incrementoX = 1.0;

    // Para el caso del material plata utilizaremos las siguientes variables:
    double k = 1.71;
    
    // Vamos a guardar los datos para diferentes incrementos de t, siempre con el mismo incremento de X para que a la hora de representar los resultados,
    // las gráficas queden de la misma manera. Cambiar los incrementos de t, cambiará la r.

    string file = "Pt19_Plata.txt";
    ofstream ff(file);
    if (ff.is_open()){
        ff << "Datos Ecuación Calor para la Plata: k = "<<k<<endl;
        ff << "Estamos usando incremento x = "<<incrementoX<<endl;
        ff << "Se muestran los resultados para distintos valores de r a tiempo = 300s."<<endl;

        // Variables que vamos a utilizar.
        double r = 0.0, x = 0.0;
        int nx = L/incrementoX;

        // Matriz solución
        matrix<double> u; u.null();
        
        // Bucle cambiando el incremento del tiempo para tener así diferentes valores de r.
        for (double incrementoT=0.05; incrementoT<=0.35; incrementoT=incrementoT+0.05){
            // Calculamos el valor de r
            r = (k*incrementoT)/(incrementoX*incrementoX);
            
            // Calculamos el resultado.
            u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
            ff<<"-------------------------------------------------------------"<<endl;
            ff<<endl;
            
            // Guardamos el resultado en un fichero.
            ff << "r = "<<r<<endl;
            ff << "x\tu(x,t)"<<endl;
            x = 0.0;
            for (int i=0; i<=nx; i++){
                ff << x << "\t" << u(i,0) << endl;
                x = x + incrementoX;
            }
        }

        ff.close();
    }

    // Repetimos el mismo proceso para otro material.
    // Probemos con el oro.
    k = 1.27;

    // Abrimos el fichero para el oro.
    file = "Pt19_Oro.txt";
    ofstream f(file);
    if (f.is_open()){
        f << "Datos Ecuación Calor para el Oro: k = "<<k<<endl;
        f << "Estamos usando incremento x = "<<incrementoX<<endl;
        f << "Se muestran los resultados para distintos valores de r a tiempo = 300s."<<endl;

        // Variables que vamos a utilizar.
        double r = 0.0, x = 0.0;
        int nx = L/incrementoX;

        // Matriz solución
        matrix<double> u; u.null();
        
        // Bucle cambiando el incremento del tiempo para tener así diferentes valores de r.
        for (double incrementoT=0.1; incrementoT<=0.45; incrementoT=incrementoT+0.05){
            // Calculamos el valor de r
            r = (k*incrementoT)/(incrementoX*incrementoX);
            
            // Calculamos el resultado.
            u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
            f<<"-------------------------------------------------------------"<<endl;
            f<<endl;
            
            // Guardamos el resultado en un fichero.
            f << "r = "<<r<<endl;
            f << "x\tu(x,t)"<<endl;
            x = 0.0;
            for (int i=0; i<=nx; i++){
                f << x << "\t" << u(i,0) << endl;
                x = x + incrementoX;
            }
        }

        f.close();
    }

    // Repetimos el mismo proceso para otro material.
    // Probemos con el aluminio.
    k = 0.86;

    // Abrimos el fichero para el oro.
    file = "Pt19_Aluminio.txt";
    ofstream fff(file);
    if (fff.is_open()){
        fff << "Datos Ecuación Calor para el Aluminio: k = "<<k<<endl;
        fff << "Estamos usando incremento x = "<<incrementoX<<endl;
        fff << "Se muestran los resultados para distintos valores de r a tiempo = 300s."<<endl;

        // Variables que vamos a utilizar.
        double r = 0.0, x = 0.0;
        int nx = L/incrementoX;

        // Matriz solución
        matrix<double> u; u.null();
        
        // Bucle cambiando el incremento del tiempo para tener así diferentes valores de r.
        for (double incrementoT=0.1; incrementoT<=0.6; incrementoT=incrementoT+0.1){
            // Calculamos el valor de r
            r = (k*incrementoT)/(incrementoX*incrementoX);
            
            // Calculamos el resultado.
            u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
            fff<<"-------------------------------------------------------------"<<endl;
            fff<<endl;
            
            // Guardamos el resultado en un fichero.
            fff << "r = "<<r<<endl;
            fff << "x\tu(x,t)"<<endl;
            x = 0.0;
            for (int i=0; i<=nx; i++){
                fff << x << "\t" << u(i,0) << endl;
                x = x + incrementoX;
            }
        }

        fff.close();
    }

    // Repetimos el mismo proceso para otro material.
    // Probemos con el Hierro fundido.
    k = 0.12;

    // Abrimos el fichero para el oro.
    file = "Pt19_HierroFundido.txt";
    ofstream ffff(file);
    if (ffff.is_open()){
        ffff << "Datos Ecuación Calor para el Hierro fundido: k = "<<k<<endl;
        ffff << "Estamos usando incremento x = "<<incrementoX<<endl;
        ffff << "Se muestran los resultados para distintos valores de r a tiempo = 300s."<<endl;

        // Variables que vamos a utilizar.
        double r = 0.0, x = 0.0;
        int nx = L/incrementoX;

        // Matriz solución
        matrix<double> u; u.null();
        
        // Bucle cambiando el incremento del tiempo para tener así diferentes valores de r.
        for (double incrementoT=0.1; incrementoT<=4.5; incrementoT=incrementoT+0.5){
            // Calculamos el valor de r
            r = (k*incrementoT)/(incrementoX*incrementoX);
            
            // Calculamos el resultado.
            u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
            ffff<<"-------------------------------------------------------------"<<endl;
            ffff<<endl;
            
            // Guardamos el resultado en un fichero.
            ffff << "r = "<<r<<endl;
            ffff << "x\tu(x,t)"<<endl;
            x = 0.0;
            for (int i=0; i<=nx; i++){
                ffff << x << "\t" << u(i,0) << endl;
                x = x + incrementoX;
            }
        }

        ffff.close();
    }

    return 0;
}