#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

#include <chrono>
using namespace chrono;

// Función que calcula la nomra máxima de una matriz. Pasando como parámetro una matriz.
// Usaremos esta función para ver si nuestro resultado es correcto dentro de una tolerancia.
double NormaMaximaMatriz(matrix<double> A){
    // Tamaño de la matriz pasada como argumento.
    int arows = 0, acols = 0;
    arows = A.rowno();
    acols = A.colno();

    double sumatorio = 0.0, fila_anterior = 0.0, maximo = 0.0;
    for (int i=0; i<arows; i++){
        fila_anterior = sumatorio;
        sumatorio = 0.0;
        for (int j=0; j<acols; j++){
            sumatorio = sumatorio + fabs(A(i,j));
        }
        if (sumatorio>fila_anterior){
            maximo = sumatorio;
        }
    }

    return maximo;
}

// Función para el cálculo de la solución de un sistema de ecuaciones lineal por el método de factorización LU.
matrix<double> MetodoLU(matrix<double> A, matrix<double> B){
    // Guardamos el tamaño de las matrices pasadas como argumento. (A*X=B) siendo X la solución que buscamos.
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    // Definimos las matrices L y U que utilizaremos más adelante.
    matrix<double> L(arows, acols); L.null();
    matrix<double> U(arows, acols); U.null();

    // Establecemos los números por defecto que tienen L y U (ceros y unos).
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i==j){
                // Los elementos de la diagonal en L son unos.
                L(i,j) = 1;
            }else if (i>j){
                // Por debajo de la diagonal los elementos de U son ceros.
                U(i,j) = 0;
            }else{
                // Por encima de la diagonal los elementos de L son ceros.
                L(i,j) = 0;
            }
        }
    }

    // Establecemos la primera fila de la matriz U que es igual a la de coeficientes A.
    for(int i=0; i<acols; i++){
        U(0,i) = A(0, i);
    }

    // Calculamos la columna[0] de la matriz L.
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i>j && j==0){
                L(i,j) = (1/U(0,0))*A(i,j);
            }
        }
    }

    // Calculamos el resto de números de las matrices
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            // Si i = j, calculamos el valor de U(i,j). Son los elementos de la diagonal, en L son los unos anteriores.
            if (i==j){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<i; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    U(i,j) = A(i,j) - SUM(i,j);
                }
            // Si i>j y no estamos en la primera columna (ya calculada) calculamos el valor de L(i,j)
            } else if(i>j && j!=0){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<j; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    L(i,j) = (A(i,j)/U(j,j)) - (SUM(i,j)/U(j,j));
                }
            // Si j>i calculamos el valor de U(i,j)
            } else if(j>i){
                matrix<double> SUM(arows, acols); SUM.null();
                for (int k=0; k<i; k++){
                    SUM(i,j) = SUM(i,j) + (L(i,k)*U(k,j));
                    U(i,j) = A(i,j) - SUM(i,j);
                  }
            }
        }
    }

    // Resolvemos ahora L*z = b. Sacamos el valor de z.
    matrix<double> z(brows, bcols); z.null();
    // Necesitamos el primer valor de z para calcular los siguientes. Gracias a la forma de L z(0,0) = B(0,0).
    z(0,0) = B(0,0);
    for (int i=0; i<arows; i++){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + L(i,j)*z(j,0);
        }
        if (i!=0){
            // El valor donde i = 0 es el primero que hemos calculado.
            z(i,0) = B(i,0) - sum;
        }
    }

    // Resolvemos ahora U*x=z.
    matrix<double> x(brows, bcols); x.null();
    for (int i=arows-1; i>=0; i--){
        double sum=0.0;
        for (int j=0; j<acols; j++){
            sum = sum + U(i,j)*x(j,0);
        }
        x(i,0) = (z(i,0) - sum)/U(i,i);
    }
    return x;

    // Las fórmulas para los cálculos anteriores están en la teoría. Página 3 del pdf "SistemaslinealesMétodosdirectos".
}

int main(){
    // Nombres de los archivos donde están las matrices y los abrimos en modo lectura.
    string ainfile = "matrizA2.txt";
    string binfile = "matrizB2.txt";
    ifstream ffile(ainfile);
    ifstream ff(binfile);
    if (ffile.is_open()){
        if (ff.is_open()){
            // Filas y columnas de ambas matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;
            
            // Definimos la matriz A.
            ffile >> arows >> acols;
            matrix<double> A(arows, acols);
            ffile >> A;

            // Para el caso del ejercicio 2 hay 6 valores que tenemos que modificar.
            // Para el ejercicio 1 hay que borrar/comentar este bucle y cambiar el nombre del archivo.
            for (int i=0; i<arows; i++){
                for (int j=1; j<acols; j++){
                    if (j==1){
                        A(i,j)=pow(A(i,j),-2);
                    } else if (j==2){
                        A(i,j)=pow(A(i,j),-4);
                    }
                }
            }
            
            // Definimos la matriz B.
            ff >> brows >> bcols;
            matrix<double> B(brows, bcols);
            ff >> B;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            // Medimos cuanto tarda el proceso de cálculo de X a partir de A y F
            time_point<system_clock> start, end;
            duration<double> elapsed_seconds;
            start = system_clock::now();

            // Definimos la que será la matriz solución por el método LU
            matrix<double> X; X.null();
            X = MetodoLU(A, B);
            cout<<"La matriz de soluciones es:"<<endl; cout<<X;

            // Aquí se termina de medir el tiempo y se imprime por pantalla.
            end = system_clock::now();
            elapsed_seconds = end - start;
            cout<<"* Tiempo LU (s) = "<<elapsed_seconds.count()<<endl;

            // Comprobamos que nuestro resultado es correcto para una cierta tolerancia.
            double tol = 0.001, max = 0.0;
            matrix<double> Sol; Sol.null();
            Sol = A*X-B; max = NormaMaximaMatriz(Sol);
            if (max > tol){
                cout<<endl;
                cout<<"Tras la comprobación A*X-B = 0, hay algún valor de la matriz que no está por debajo de la tolerancia."<<endl;
            }

            // Calculamos el error obtenido en las constantes A, B y C del ejercicio 2.
            // Esta parte del código también debe ser borrada/comentada si solo queremos calcular X por el método LU.
            string file = "RefraccionYLongitudesOnda.txt";
            ifstream f(file);
            if (f.is_open()){
                // Leemos del archivo los valores de los diferentes índices de refracción (segunda columna).
                int nrows = 0, ncols = 0;
                f >> nrows >> ncols;
                matrix<double> N(nrows, ncols);
                f >> N;

                cout<<endl;
                cout<<"Mostrando los errores cometidos para cada valor de n:"<<endl;

                double error = 0.0;
                for (int i=0; i<nrows; i++){
                    // X(0,0) = A; X(1,0) = B; X(2,0) = C.
                    // Seguimos la ecuación n = A + B/(lambda)^2 + C/(lambda)^4
                    error = N(i,1) - (X(0,0) + X(1,0)/pow(N(i,0), 2) + X(2,0)/pow(N(i,0), 4));
                    cout<<error<<endl;
                }

            } else {
                cout<<"No se ha podido abrir el fichero "<<file<<endl;
            }

        }else {
            cout<<"No se ha podido abrir el fichero "<<binfile<<endl;
        }

    }else{
        cout<<"No se ha podido abrir el fichero "<<ainfile<<endl;
    }

    return 0;
}