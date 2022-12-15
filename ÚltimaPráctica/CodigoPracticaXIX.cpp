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

matrix<double> EcuacionCalor(double k, double &incrementoX, double &incrementoT, double Xfinal, double Tfinal){
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
    for (int i=0; i<=Xfinal; i=i+incrementoX){
        if (x>=0 && x<50){
            u0(i,0) = 0;
        } else {
            u0(i,0) = 10;
        } x = x + incrementoX;
    }

    // Iteramos para todos los valores del tiempo.
    matrix<double> u(nx,1); u.null();
    for (double t=0; t<=Tfinal; t=t+incrementoT){
        for (int i=0; i<=Xfinal; i=x+incrementoX){
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
    double L = 100.0, Tfinal = 300.0;

    // Para el caso del material plata utilizaremos las siguientes variables:
    double k = 1.71, incrementoX = 1, incrementoT = 0.25;

    matrix<double> u; u.null();
    u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
    
    // Guardamos el resultado en un fichero y añadimos el valor en la frontera para x = 100cm.
    string file = "Pt19_Plata_r0.4274.txt";
    ofstream ff(file);
    if (ff.is_open()){
        double r = (k*incrementoT)/(incrementoX*incrementoX);
        ff << "Datos Ecuación Calor para la Plata: k = "<<k<<endl;
        ff << "Estamos usando incremento x = "<<incrementoX<<" y incremento t = "<<incrementoT<<endl;
        ff << "r = "<<r<<endl<<endl;
        ff << "x\tu(x,t) con t=300"<<endl;
        int nx = L/incrementoX;
        for (int i=0; i<=nx; i++){
            ff << i << "\t" << u(i,0) << endl;
        }

        ff.close();
    }

    // Cambiamos los incrementos
    incrementoX = 0.5, incrementoT = 0.1;
    u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);
    cout<<"La solución para r = 0.684 no converge."<<endl;

    // Cambiamos los incrementos.
    incrementoX = 0.5, incrementoT = 0.05;
    u = EcuacionCalor(k, incrementoX, incrementoT, L, Tfinal);

    // Guardamos el resultado en un fichero y añadimos el valor en la frontera para x = 100cm.
    file = "Pt19_Plata_r0.684.txt";
    ofstream f(file);
    if (f.is_open()){
        double r = (k*incrementoT)/(incrementoX*incrementoX);
        f << "Datos Ecuación Calor para la Plata: k = "<<k<<endl;
        f << "Estamos usando incremento x = "<<incrementoX<<" y incremento t = "<<incrementoT<<endl;
        f << "r = "<<r<<endl<<endl;
        f << "x\tu(x,t) con t=300"<<endl;
        int nx = L/incrementoX;
        for (int i=0; i<=nx; i++){
            f << i << "\t" << u(i,0) << endl;
        }

        f.close();
    }

    return 0;
}