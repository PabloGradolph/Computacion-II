#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

#include <cmatrix>
using namespace techsoft;

// Función para calcular la NormaMáxima que utilizaremos para las comprobaciones.
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

// Función que calcula el máximo valor de los elementos por encima de la diagonal de una matriz.
double MaxEncimaDiagonal(matrix<double> A){
    // Guardamos el tamaño de la matriz A para trabajar con ella.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.colno();

    // Calculamos el máximo
    double maximo = 0.0;
    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (j>i){
                if (fabs(A(i,j)) > fabs(maximo)){
                    maximo = A(i,j);
                }
            }
        }
    }
    return maximo;
}

bool CuadradaSimetrica(matrix<double> A, double tol){
    // Tamaño de A.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.colno();

    // Bool que permite saber si la matriz es cuadrada y simétrica
    bool cuadradasimetrica = false;

    if (arows == acols){
        cuadradasimetrica = true;
    } else {
        cout<<"La matriz no es cuadrada"<<endl;
        return cuadradasimetrica;
    }

    for (int i=0; i<arows; i++){
        for (int j=0; j<acols; j++){
            if (i!=j){
                if(A(i,j)-A(j,i)>tol){
                    cout<<"La matriz no es simétrica"<<endl;
                    cuadradasimetrica = false;
                    return cuadradasimetrica;
                }
            }
        }
    }

    return cuadradasimetrica;
}

// Función que calcula la traza de una matriz pasada como argumento.
double TrazaMatriz(matrix<double> A){
    // Tamaño de A.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.colno();

    // Variable traza
    double traza = 0.0;

    // Calculamos su valor
    for (int i=0; i<arows; i++){
        traza = traza + A(i,i);
    }

    return traza;
}

// Función principal del método de Jacobi para diagonalizar matrices.
void JacobiDiagonal(matrix<double> A, matrix<double>& Diagonalizada, matrix<double>& U, int &iteraciones, double tol){
    // Tamaño de A.
    int acols = 0, arows = 0;
    arows = A.rowno();
    acols = A.colno();

    // Matrices que utilizaremos en el bucle.
    matrix<double> nueva_U(arows, acols); nueva_U.null();
    matrix<double> R(arows, acols); R.null();

    // Comprobación de si la matriz es cuadrada y simetrica. Y que la traza es invariante.
    bool cuadradasimetrica = false;
    double traza = TrazaMatriz(A);
    double nueva_traza = 0.0;

    // Definimos el máximo y creamos el bucle para que se ejecute el método hasta que
    // el máximo de la matriz esté por debajo de la tolerancia.
    double maximo = MaxEncimaDiagonal(A);
    
    while (fabs(maximo)>tol){
        
        // Comprobamos que la matriz sea cuadrada y simétrica.
        cuadradasimetrica = CuadradaSimetrica(A, 0.0001);
        if (cuadradasimetrica==false){
            break;
        }

        // Comprobamos que la traza sea invariante en cada rotación.
        nueva_traza = TrazaMatriz(A);
        if (nueva_traza - traza > 0.0001){
            cout<<"La traza de la matriz varía en la iteración "<<iteraciones<<endl;
            break;
        }
        traza = nueva_traza;

        // El máximo para cada iteración.
        maximo = MaxEncimaDiagonal(A);

        // Vemos la posición en la que se encuentra ese máximo.
        int ii=NULL, jj=NULL;
        if (maximo == A(0,1)){
            ii = 0; jj = 1;
        } else {
            for (int i=0; i<arows; i++){
                if (ii!=NULL && jj!=NULL){
                    break;
                }
                for (int j=0; j<acols; j++){
                    if (j>i){
                        if (A(i,j)==maximo){
                            ii = i; jj = j;
                            break;
                        }
                    } 
                }
            }
        }
        
        // Ya tenemos que la posición del máximo está en ii, jj.
        // Calculamos ahora theta.
        double theta = 0.0;
        if (A(ii,ii)!=A(jj,jj)){
            theta = 0.5 * atan(2*A(ii,jj)/(A(ii,ii)-A(jj,jj)));
        } else {
            theta = M_PI/4.0;
        }

        // Calculamos ahora la matriz R.
        for (int i=0; i<arows; i++){
            for (int j=0; j<acols; j++){
                if (i==j){
                    R(i,j) = 1;
                } else { 
                    R(i,j) = 0;
                }
            }
        }
        R(ii,ii) = cos(theta); R(jj,jj) = cos(theta);
        R(ii,jj) = -sin(theta); R(jj,ii) = sin(theta);
        
        // Nueva matriz A.
        A = ~R*A*R;
        
        // Nueva matriz U.
        if (iteraciones==0){
            nueva_U = R;
        } else {
            nueva_U = nueva_U*R;
        }

        // +1 iteración
        iteraciones ++;
    }

    // Comprobaciones de la simetría y cuadratura de la matriz A.
    if (cuadradasimetrica==true && nueva_traza-traza<0.0001){
        Diagonalizada = A;
        U = nueva_U;
    } else {
        // Variable que usamos fuera y la dejamos a cero para saber que la matriz 
        // no es cuadrada o no es simétrica o la traza varía.
        iteraciones = 0;
    }
}

// Función que comprueba que los resultados obtenidos en las matrices U y Diagonalizada son correctos.
bool comprobaciones(matrix<double> A, matrix<double> U, matrix<double> Diagonalizada, double tol){
    // Leemos el tamaño de las matrices y creamos el bool que devolveremos tras finalizar las comprobaciones.
    int arows = 0, acols = 0, urows = 0, ucols = 0, drows = 0, dcols = 0;
    arows = A.rowno(); acols = A.colno();
    urows = U.rowno(); ucols = U.colno();
    drows = Diagonalizada.rowno(); dcols = Diagonalizada.colno();
    bool comprobacion = false; 
    
    double autovalor = 0.0;
    matrix<double> autovector; matrix<double> comprobaciones;
    // Recorremos la matriz U por columnas.
    // Y hacemos la operacion A*v - lambda*v = 0
    for (int j=0; j<urows; j++){
        for (int i=0; i<ucols; i++){
            autovector(i,j) = U(i,j);
            autovalor = Diagonalizada(j,j);  
        }
        comprobaciones = A*autovector - autovector*autovalor;
        if (NormaMaximaMatriz(comprobaciones)>tol){
            comprobacion = false;
            break;
        } else {
            comprobacion = true;
        }
    }
    return comprobacion;
}

int main(){
    // Leemos la matriz A creada a partir del código 'CalculoMatrizA.cpp'
    string ainfile = "matrizA.txt";
    ifstream ff(ainfile);
    if (ff.is_open()){
        int arows = 0, acols = 0;
        
        // Definimos la matriz A.
        ff >> arows >> acols;
        matrix<double> A(arows, acols);
        ff >> A;
        
        // Definimos las matrices y variables que queremos que la función de Jacobi nos devuelva.
        // Habrá que pasarle todo esto como argumento a la función para que lo transforme.
        matrix<double> Diagonalizada(arows, acols); Diagonalizada.null();
        matrix<double> U(arows, acols); U.null();
        int iteraciones = 0;
        double tol = pow(10,-10);

        // Llamamos ahora a la función del método de Jacobi para diagonalizar matrices simétricas.
        JacobiDiagonal(A, Diagonalizada, U, iteraciones, tol);

        // Comprobación de los autovalores y autovectores.
        bool comprobacion = false;
        comprobacion = comprobaciones(A, U, Diagonalizada, 0.000000001);
        if (comprobacion == false){
            cout<<"Los autovalores o los autovectores no son corrector."<<endl;
            cout<<"Revise el procedimiento"<<endl;
        } else {
            if (iteraciones != 0){
                cout<<"Los resultados son correctos."<<endl;
                cout<<"Esta es la matriz diagonalizada:"<<endl;
                cout<<Diagonalizada<<endl;
                cout<<endl;
                cout<<"Esta es la matriz de autovectores:"<<endl;
                cout<<U<<endl;
                cout<<endl;
                cout<<"El número de iteraciones que hemos utilizado es: "<<iteraciones<<endl;
            }
        }
    }

    return 0;
}