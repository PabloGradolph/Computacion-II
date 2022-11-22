#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función que retorna True o False en función de si la matriz pasada como parámetro es Diagonal Dominante o no.
bool DominanteDiagonal(matrix<double> A){
    // Inicializamos las variables y calculamos el tamaño de la matriz pasada como argumento.
    bool dominante = false;
    int arows = 0, acols = 0;
    arows = A.rowno(); acols = A.colno();
    int vectorbool[arows] = {0}; 
    
    // Se calcula la suma por fila de los elementos que no están en la diagonal.
    // Se compara con el elemento de la diagonal y guardamos en el vectorbool un 1 o un 0 en función de si es mayor o no.
    double sum = 0.0;
    for (int i=0; i<arows; i++){
        sum = 0.0;
        for (int j=0; j<acols; j++){
            if (i!=j){
                sum = sum + fabs(A(i, j));
            } 
        }
        if (fabs(A(i,i)) > sum){
            vectorbool[i] = 1;
        }
    }

    // Si hay algún cero en el vector, la variable dominante es false y se retorna.
    for (int i=0; i<arows; i++){
        if (vectorbool[i] == 0){
            dominante = 0;
            break;
        }
    }

    return dominante;
}

// Función que calcula la norma máxima de un vector. Pasando como parámetro un vector.
double NormaMaximaVector(double vector[], int len){
    double maximo = 0.0;
    for (int i=0; i<len; i++){
        if (fabs(vector[i])>maximo){
            maximo = fabs(vector[i]);
        }
    }

    return maximo;
}

// Función que calcula la nomra máxima de una matriz. Pasando como parámetro una matriz.
double NormaMaximaMatriz(matrix<double> A){
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

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Jacobi.
matrix<double> MetodoJacobi(matrix<double> A, matrix<double> B){
    // Inicializamos las iteraciones a 0 y calculamos el tamaño de las matrices pasadas como argumento.
    // Pasamos la matriz de coeficientes y la matriz solución del sistema.
    int iteraciones = 0;
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    // Tres matrices que iremos usando durante las iteraciones.
    matrix<double> old_x(brows, bcols); old_x.null();
    matrix<double> new_x(brows, bcols); new_x.null();
    matrix<double> new_A(arows, acols); new_A.null();

    // Calculamos las matrices de coeficientes
    for (int i=0; i<arows; i++){
        B(i,0) = B(i,0)/A(i,i);
        for(int j=0; j<acols; j++){
            if(i!=j){
                new_A(i,j) = -A(i,j)/A(i,i);
            } else {
                new_A(i,j) = 0;
            }
        }
    }

    // Definimos la matriz solución exacta.
    matrix<double> solucion(brows, bcols); solucion.null();
    solucion(0,0) = -0.2568; solucion(1,0) = -1.0236;
    solucion(2,0) = 0.4527; solucion(3,0) = 0.1014;

    // Definimos la que será la matriz convergencia (resta entre nuestra solución y la exacta)
    matrix<double> convergencia(brows, bcols); convergencia.null();

    // Definimos la tolerancia y el valor que tomará la norma máxima de la matriz convergencia.
    // Con la tolerancia más pequeña el programa tarda demasiado. Es por esto por lo que pongo 10^-4 de tolerancia.
    double tol = 0.0001, normaMaxima = 0.0;

    // Primera iteración
    old_x = B;
    iteraciones = 1;

    // Resto de iteraciones
    while (true){
        new_x = B + (new_A*old_x);
        old_x = new_x;
        iteraciones++;
        convergencia = solucion - new_x;
        normaMaxima = NormaMaximaMatriz(convergencia);
        // Si la norma máxima es menor que la tolerancia continuamos
        if (normaMaxima<=tol){
            break;
        // Sino seguimos iterando.
        } else {
            cout<<normaMaxima<<endl;
            continue;
        }
    }

    // Por el método de Jacobi se hacen estas iteraciones.
    cout<<"Método de Jacobi:"<<endl;
    cout<<"Número de iteraciones: "<<iteraciones<<endl;

    // Retornamos nuestra matriz solución.
    return new_x;
}

// Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Gauss-Seidel.
matrix<double> MetodoGauss(matrix<double> A, matrix<double> B){
    // Inicializamos las iteraciones a 0 y calculamos el tamaño de las matrices pasadas como argumento.
    // Pasamos la matriz de coeficientes y la matriz solución del sistema.
    int iteraciones = 0;
    int arows = 0, acols = 0, brows = 0, bcols = 0;
    arows = A.rowno();
    acols = A.colno();
    brows = B.rowno();
    bcols = B.colno();

    // Tres matrices que iremos usando durante las iteraciones.
    matrix<double> old_x(brows, bcols); old_x.null();
    matrix<double> new_x(brows, bcols); new_x.null();
    matrix<double> new_A(arows, acols); new_A.null();

    // Calculamos las matrices de coeficientes.
    for (int i=0; i<arows; i++){
        B(i,0) = B(i,0)/A(i,i);
        for(int j=0; j<acols; j++){
            if(i!=j){
                new_A(i,j) = -A(i,j)/A(i,i);
            } else {
                new_A(i,j) = 0;
            }
        }
    }

    // Definimos la matriz solución exacta.
    matrix<double> solucion(brows, bcols); solucion.null();
    solucion(0,0) = -0.2568; solucion(1,0) = -1.0236;
    solucion(2,0) = 0.4527; solucion(3,0) = 0.1014;

    // Definimos la que será la matriz convergencia (resta entre nuestra solución y la exacta)
    matrix<double> convergencia(brows, bcols); convergencia.null();

    // Definimos la tolerancia y el valor que tomará la norma máxima de la matriz convergencia.
    // Con la tolerancia más pequeña el programa tarda demasiado. Es por esto por lo que pongo 10^-4 de tolerancia.
    double tol = 0.0001, normaMaxima = 0.0;

    int i = 0;
    while (true){
        new_x(i,0) = B(i,0) + (new_A*old_x)(i,0);
        old_x(i,0) = new_x(i,0);
        if (i<4){
            i++;
        } else {
            i = 0;
            iteraciones++;
            convergencia = solucion - new_x;
            normaMaxima = NormaMaximaMatriz(convergencia);
            if (normaMaxima<=tol){
                break;
            } else {
                continue;
            }
        }
    }

    // Por el método de Gauss-Seidel se hacen estas iteraciones.
    cout<<"Método de Gauss-Seidel:"<<endl;
    cout<<"Número de iteraciones: "<<iteraciones<<endl;

    return new_x;
}

int main(){
    // Leemos los archivos donde se encuentran las matrices de coeficientes y solución.
    string ainfile = "matrizA.txt";
    string binfile = "matrizB.txt";
    ifstream ffile(ainfile);
    ifstream ff(binfile);
    if (ffile.is_open()){
        if(ff.is_open()){
            // Filas y columnas de las matrices.
            int arows = 0, acols = 0, brows = 0, bcols = 0;

            // Definimos la matriz A.
            ffile >> arows >> acols;
            matrix<double> A(arows, acols);
            ffile >> A;

            // Definimos la matriz B.
            ff >> brows >> bcols;
            matrix<double> B(brows, bcols);
            ff >> B;

            // Cerramos los ficheros.
            ffile.close();
            ff.close();

            // Comprobamos si la matriz pasada es diagonal dominante mediante la función.
            bool dominante;
            dominante = DominanteDiagonal(A);
            if (dominante == true){
                cout<<"La matriz A es diagonal dominante."<<endl;
            } else {
                cout<<"¡Cuidado! La matriz A no es diagonal dominante."<<endl;
            }

            cout<<endl;
            
            // Calculamos e imprimimos los resultados para el método de Jacobi.
            matrix<double> X(brows, bcols);
            X = MetodoJacobi(A, B);
            cout<<"Matriz solución tras ese número de iteraciones: "<<endl<<X;
            cout<<endl;

            // Comprobamos que nuestro resultado es correcto para una cierta tolerancia.
            double tol = 0.001, max = 0.0;
            matrix<double> Sol; Sol.null();
            Sol = A*X-B; max = NormaMaximaMatriz(Sol);
            if (max > tol){
                cout<<endl;
                cout<<"Tras la comprobación A*X-B = 0, hay algún valor de la matriz que no está por debajo de la tolerancia."<<endl;
            }

            // Lo mismo para el método de Gauss.
            X = MetodoGauss(A, B);
            cout<<"Matriz solución tras ese número de iteraciones: "<<endl<<X;
            cout<<endl;

            // Comprobamos que nuestro resultado es correcto para una cierta tolerancia.
            max = 0.0;
            Sol = A*X-B; max = NormaMaximaMatriz(Sol);
            if (max > tol){
                cout<<endl;
                cout<<"Tras la comprobación A*X-B = 0, hay algún valor de la matriz que no está por debajo de la tolerancia."<<endl;
            }
        }
    }

    return 0;
}