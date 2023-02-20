#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

// Función que calcula los radianes en función de los grados pasado como argumento.
double Radianes(double grados){
    double rad = 0.0;
    rad = grados * (M_PI/180.);
    return rad;
}

// Función que devuelve el valor de la función que usamos en nuestro caso.
double Funcion(double valorTH, double valorFi){
    // Definimos K (necesario en nuestro caso)
    double k = 0.0;
    k = sin(valorTH/2.);

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
    k = sin(valorTH/2.);

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

    // Control de errores en la entrada de n
    if (n%2!=0){
        cout<<"El valor n no es par: n = "<<n<<endl;
        cout<<"No se puede seguir el método Simpson 1/3"<<endl;
        return n;
    }

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
            sumatorio = sumatorio + (2*Funcion(TH, Fi));
        } else if (i%2!=0){
            sumatorio = sumatorio + (4*Funcion(TH, Fi));
        } Fi = Fi + h;
    }

    // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
    double I = 0.0;
    I = (h/3) * sumatorio;

    return I;
}

// Función que calcula la integeral por la regla de Simpson 3/8 (cuando n es múltiplo de 3).
double Simpson38(int n, double a, double b, double TH){

    // Control de errores en la entrada de n
    if (n%3!=0){
        cout<<"El valor n introducido no es múltiplo de 3: n = "<<n<<endl;
        cout<<"No se puede seguir el método Simpson 3/8"<<endl;
        return n;
    }

    // Calculamos h
    double h = 0.0;
    h = (b - a)/n;

    // Calculamos la parte f(x0) + 3f(x1) + 3f(x2) + 2f(x3) + 3f(x4) + 3f(x5) + 2f(x6) + ... + f(xn).
    double Fi = 0.0, sumatorio = 0.0;
    for (int i=0; i<=n; i++){
        if (i==0){
            sumatorio = sumatorio + Funcion(TH, Fi);
        } else if (i==n){
            sumatorio = sumatorio + Funcion(TH, Fi);
        } else if (i%3==0){
            sumatorio = sumatorio + (2*Funcion(TH, Fi));
        } else if (i%3!=0){
            sumatorio = sumatorio + (3*Funcion(TH, Fi));
        } Fi = Fi + h;
    }

    // Calculamos la integral de la función con la regla de Simpson 3/8 compuesta.
    double I = 0.0;
    I = (3*h/8) * sumatorio;

    return I;
}

double CuadraturaGaussiana(int n, double a, double b, double TH){
    
    // Control de errores en la entrada de n
    if (n<1 || n>5){
        cout<<"Error en la entrada de n: n = "<<n<<endl;
        cout<<"No se puede seguir el método de la cuadratura gaussiana"<<endl;
        return n;
    }

    // Calculamos la integral para los 5 posibles casos (hasta 5 puntos)
    double I = 0.0;
    double wi = 0.0;
    double xi = 0.0;

    if (n == 1){

        xi = 0.0;
        wi = 2.0;
        I = wi*FuncionCG(b, a, TH, xi);

    } else if (n == 2){

        double x1 = 1/sqrt(3), x2 = -1/sqrt(3);
        wi = 1.0;
        I = wi*FuncionCG(b, a, TH, x1);
        I = I + wi*FuncionCG(b, a, TH, x2);

    } else if (n==3){

        xi = 0.0;
        wi = 8/9.0;
        I = wi * FuncionCG(b, a, TH, xi);

        xi = -0.774597;
        wi = 5/9.0;
        I = I + wi * FuncionCG(b, a, TH, xi);
        I = I + wi * FuncionCG(b, a, TH, -xi);

    } else if (n==4){

        xi = -0.339981;
        wi = 0.652145;
        I = wi * FuncionCG(b, a, TH, xi);
        I = I + wi * FuncionCG(b, a, TH, -xi);

        xi = -0.861136;
        wi = 0.347855;
        I = I + wi * FuncionCG(b, a, TH, xi);
        I = I + wi * FuncionCG(b, a, TH, -xi);

    } else if (n==5){

        xi = 0.0;
        wi = 0.568889;
        I = wi * FuncionCG(b, a, TH, xi);

        xi = -0.538469;
        wi = 0.478629;
        I = I + wi * FuncionCG(b, a, TH, xi);
        I = I + wi * FuncionCG(b, a, TH, -xi);

        xi = -0.90618;
        wi = 0.236927;
        I = I + wi * FuncionCG(b, a, TH, xi);
        I = I + wi * FuncionCG(b, a, TH, -xi);
    }
    
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
    
    // Guardamos todos los resultados en un mismo fichero (Trapecio, Simpson, CuadraturaGaussiana para 4 y 20 intervalos y para 2 y 5 puntos (enunciado)).
    // Vamos guardando los resultados en un fichero.
    string gfile = "Resultados.txt";
    ofstream ffile(gfile);
    if (ffile.is_open()){
        // Encabezados del fichero.
        ffile << "                ---  INTEGRACIÓN NUMÉRICA  ---"<<endl;
        ffile << "Se muestran todas las integrales variando el valor de Theta de 0 a 100º de 5 en 5º:"<<endl;
        ffile << "Theta    Trapecio(4)    Trapecio(20)    Simpson(4)    Simpson(20)    Cuadratura(2)    Cuadratura(5)" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        ffile << setprecision(6);
        double theta = 0.0, I1 = 0.0, I2 = 0.0, I3 = 0.0, I4 = 0.0, I5 = 0.0, I6 = 0.0;
        for (int TH=0; TH<=100; TH=TH+5){
            theta = Radianes(TH);
            I1 = Trapezoidal(4, 0, M_PI/2, theta);
            I2 = Trapezoidal(20, 0, M_PI/2, theta);
            I3 = Simpson(4, 0, M_PI/2, theta);
            I4 = Simpson(20, 0, M_PI/2, theta);
            I5 = CuadraturaGaussiana(2, 0, M_PI/2, theta);
            I6 = CuadraturaGaussiana(5, 0, M_PI/2, theta);
            ffile << TH << "\t\t ";
            ffile << I1 << "\t\t\t";
            ffile << I2 << "\t\t\t";
            ffile << I3 << "\t\t\t";
            ffile << I4 << "\t\t\t";
            ffile << I5 << "\t\t\t";
            ffile << I6 << "\t\t\t";
            ffile << endl;
        }

        ffile.close();
    }

    return 0;
}
