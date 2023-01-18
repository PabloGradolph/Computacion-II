// Ejercicio 1 del examen final de prácticas.
// Autor: Pablo Gradolph Oliva.
// Fecha: 16/01/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;
// Función que devuelve el valor de la función que usamos en nuestro caso.
double Funcion(double lambda){

    double T = 213.0;

    // Definimos la función
    double funcion = 0.0;
    funcion = (2.39*pow(10,-11)) / (pow(lambda, 5) * (exp(-1.432/(T*lambda)) -1));

    return funcion;
}

// Función que devuelve la función con cambio de variable que necesitamos para calcular la 
// Cuadratura Gaussiana.
double FuncionCG(double b, double a, double lambda){

    double T = 213.0;

    // Definimos la función
    double funcion = 0.0;
    funcion = ((b-a)/2) * (2.39*pow(10,-11)) / (pow(((b-a)/2 * lambda) + (a+b)/2, 5) * (exp(-1.432/(T*(((b-a)/2 * lambda) + (a+b)/2))) -1));

    return funcion;
}

// Función que calcula la integral por la regla de Simpson 1/3 n es par.
double Simpson(double a, double b, double tol){

    // Guardamos los resultados en un fichero de salida.
    string gfile = "ResultadosSimpson.txt";
    ofstream ffile(gfile);
    if (ffile.is_open()){
        // Encabezados del fichero.
        ffile << "                ---  RESULTADOS DE LA INTEGRAL POR SIMPSON  ---"<<endl;
        ffile << "Se muestran todas las integrales variando el valor de lambda:"<<endl;
        ffile << "LAMBDA \t\t INTEGRAL(Simpson 1/3)" << endl;
        ffile << setprecision(10);

        // Definimos la integral
        double I = 0.0, I2 = 0.0;

        int n = 2;

        double lambda = a, sumatorio = 0.0;

        do {
            
            // Calculamos h
            double h = 0.0;
            h = (b - a)/n;

            I2 = I;

            // Calculamos la parte f(x0) + 4f(x1) + 2f(x2) + ... + 4f(xn-1) + f(xn).
            for (int i=0; i<=n; i++){
                if (i==0){
                    sumatorio = sumatorio + Funcion(lambda);
                } else if (i==n){
                    sumatorio = sumatorio + Funcion(lambda);
                } else if (i%2==0){
                    sumatorio = sumatorio + (4*Funcion(lambda));
                } else if (i%2!=0){
                    sumatorio = sumatorio + (2*Funcion(lambda));
                }
            } 

            // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
            I = (h/3) * sumatorio;

            lambda = lambda + h;
            n = n + 2;

        }while (fabs(I-I2>tol));

        // Ya tenemos el número de intervalos.
        // Calculamos h
        double h = 0.0;
        h = (b - a)/n;

        for (double lambda = a; lambda>=b; lambda = lambda + h){
            // Calculamos la parte f(x0) + 4f(x1) + 2f(x2) + ... + 4f(xn-1) + f(xn).
            double lambda2 = a;
            for (int i=0; i<=n; i++){
                if (i==0){
                    sumatorio = sumatorio + Funcion(lambda2);
                } else if (i==n){
                    sumatorio = sumatorio + Funcion(lambda2);
                } else if (i%2==0){
                    sumatorio = sumatorio + (2*Funcion(lambda2));
                } else if (i%2!=0){
                    sumatorio = sumatorio + (4*Funcion(lambda2));
                }lambda2 = lambda2 + h;
            } 

            // Calculamos la integral de la función con la regla de Simpson 1/3 compuesta.
            I = (h/3) * sumatorio;

            ffile << lambda << "\t\t" << I << endl;
        }
        cout<<"Puedes encontrar los resultados de las integrales por Simson para n = "<< n <<" intervalos en:"<<endl;
        cout<<gfile<<endl<<endl;

        return I;
    }
}

double CuadraturaGaussiana(int n, double a, double b, double lambda){
    
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
        I = wi*FuncionCG(b, a, lambda);

    } else if (n == 2){

        double x1 = 1/sqrt(3), x2 = -1/sqrt(3);
        wi = 1.0;
        I = wi*FuncionCG(b, a, lambda);
        I = I + wi*FuncionCG(b, a, lambda);

    } else if (n==3){

        xi = 0.0;
        wi = 8/9.0;
        I = wi * FuncionCG(b, a, lambda);

        xi = -0.774597;
        wi = 5/9.0;
        I = I + wi * FuncionCG(b, a, lambda);
        I = I + wi * FuncionCG(b, a, lambda);

    } else if (n==4){

        xi = -0.339981;
        wi = 0.652145;
        I = wi * FuncionCG(b, a, lambda);
        I = I + wi * FuncionCG(b, a, lambda);

        xi = -0.861136;
        wi = 0.347855;
        I = I + wi * FuncionCG(b, a, lambda);
        I = I + wi * FuncionCG(b, a, lambda);

    } else if (n==5){

        xi = 0.0;
        wi = 0.568889;
        I = wi * FuncionCG(b, a, lambda);

        xi = -0.538469;
        wi = 0.478629;
        I = I + wi * FuncionCG(b, a, lambda);
        I = I + wi * FuncionCG(b, a, lambda);

        xi = -0.90618;
        wi = 0.236927;
        I = I + wi * FuncionCG(b, a, lambda);
        I = I + wi * FuncionCG(b, a, lambda);
    }
    
    return I;
}

int main(){
    // Variables iniciales.
    double a = 0.003, b = 0.0014, tol = 0.01, I = 0.0;

    I = Simpson(a, b, tol);

    string gfile = "ResultadosCuadratura.txt";
    ofstream ffile(gfile);
    if (ffile.is_open()){
        // Encabezados del fichero.
        ffile << "                ---  CUADRATURA DE GAUSS  ---"<<endl;
        ffile << "Se muestran todas las integrales variando el valor de lambda:"<<endl;
        ffile << "lambda \t Cuadratura n=2" << endl;
        
        // Definimos, calculamos e insertamos los datos en el fichero.
        ffile << setprecision(6);
        double h = -3.07692e-05, I = 0.0;

        // Encontramos h y 52 intervalos en simpson, apliamos el mismo h para la cuadratura
        // Es decir, el mismo paso entre un valor de lambda y el siguiente.
        for (double lambda = a; lambda>=b; lambda = lambda + h){
            I = CuadraturaGaussiana(2, a, b, lambda);
            ffile << lambda << "\t\t" << I << endl;
        }
        cout<<"Puedes encontrar los resultados de las integrales por Cuadratura para n = 2"<<endl;
        cout<<gfile<<endl<<endl;
    }
    
    return 0;
}